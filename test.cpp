PIDController speed_controller;     // PID速度控制器
PIDController angle_controller;     // PID舵角控制器
double last_target_speed = 999.0;   // 上一帧目标速度，初始化为999.0 米/秒
bool is_first_frame = true;         // 第一帧标志

static void userDriverSetParam(
  float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear)
{
    /* 舵角控制 */
    double targetAngleError = 0.0; //目标误差
    double currentAngleError = atan2(_midline[5][0], _midline[5][1]); //当前误差

    //第一帧初始化舵角控制参数，清空积分器和微分器，因为控制目标为恒零，所以只需要初始化一次
    if (isFirstFrame)
    {
        isFirstFrame = false;
        angleController.initial(1.0, 0.0, 0.0, targetAngleError);
    }
    
    //舵角PID控制
    *cmdSteer = constrain(-1.0, 1.0, angleController.calculate(currentAngleError));

    /*▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*\
    █    速度控制                                                                █
    \*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/
    double targetSpeed;  //目标车速
    double currentSpeed = _speed;    //当前误差
    
    //计算前方是直道还是弯道
    circle myCurve;
    float minCruve = 500.0;
    for (int fStep = 0; fStep < 50; fStep++)
    {
        myCurve = getR(_midline[fStep][0], _midline[fStep][1], _midline[fStep + 10][0], _midline[fStep + 10][1], _midline[fStep + 20][0], _midline[fStep + 20][1]);
        if (myCurve.r < minCruve)
        {
            minCruve = myCurve.r;
        }
    }
    //设定目标速度，如果前方弯道就设定低，直道就设定高
    if (minCruve > 300)
        targetSpeed = 250;
    else if (minCruve > 150)
        targetSpeed = 150;
    else if (minCruve > 100)
        targetSpeed = 80;
    else
        targetSpeed = 50;

    //每当目标速度变化时初始化PID控制器，重设参数，清空积分器和微分器
    if (targetSpeed != lastTargetSpeed)
    {
        speedController.initial(0.01, 0.0, 0.0, targetSpeed);
        lastTargetSpeed = targetSpeed;
    }

    //根据当前速度和目标速度关系，控制油门刹车以改变速度
    if (currentSpeed < targetSpeed)  //当前速度低于目标，需要加速
    {
        
        if (_speed > 100 && abs(*cmdSteer) < 0.1)
        {
            //速度较快且舵角较小时，使用PID控制
            *cmdAcc = constrain(0.0, 1.0, speedController.calculate(currentSpeed));
        }
        else if (_speed > 50 && abs(*cmdSteer) < 0.1)
        {
            //速度较慢且舵角较小时，限定油门
            *cmdAcc = 0.6;
        }
        else
        {
            //除此之外的情况进一步限定油门
            *cmdAcc = 0.3;
        }
        //加速情况下，刹车为0
        *cmdBrake = 0;
    }
    else
    {
        //减速情况下，刹车
        *cmdAcc = 0;
        *cmdBrake = 0.3;
    }
    
    //更新档位
    updateGear(cmdGear);

    //窗口可视化
    cls_visual.Fig2Y(1, 0, 300, 0, 500, 10, "Target V", targetSpeed, "Curvature", minCruve, "Current V", _speed);