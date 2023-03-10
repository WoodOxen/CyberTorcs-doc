# 基于PID的车辆控制integratedError

## PID控制器

以下是一个简易版的PID控制器的实现代码：

```cpp
class PIDController
{
  private:
    double kp, ki, kd;          // PID控制器的参数
    double targetValue;         // 目标值
    double lastError;           // 上一次误差
    double integratedError;     // 误差积分值

  public:    
    void initialize(double p, double i, double d, double target)
    {
      kp = p;
      ki = i;
      kd = d;
      targetValue = target;
      lastError = 0;
      integratedError = 0;
    }

    double calculate(double input)
    {
      double error = targetValue - input;             // 当前误差
      double derivativeError = error - lastError;     // 误差的变化率
      integratedError += error;
      lastError = error;

      return kp * error + ki * integratedError + kd * derivativeError;
    }
}
```

## 基于PID的车辆控制

在CyberTorcs中，基于PID控制车辆的简易实现如下：

```cpp
PIDController speedController;        // PID速度控制器
PIDController angleController;        // PID舵角控制器
double lastTargetSpeed = 999.0;       // 上一帧目标速度，初始化为999.0 米/秒
bool isFirstFrame = true;             // 第一帧标志

static void userDriverSetParam(
  float* cmdAcc, float* cmdBrake, float* cmdSteer, int* cmdGear)
{
  /* ----- 舵角控制 ----- */
  double targetAngleError = 0.0;
  double currentAngleError = atan2(_midline[5][0], _midline[5][1]);

  // 第一帧初始化舵角控制参数，清空积分器和微分器
  // 因为控制目标一直为零，所以只需要初始化一次
  if (isFirstFrame)
  {
      isFirstFrame = false;
      angleController.initial(1.0, 0.0, 0.0, targetAngleError);
  }
  
  // 舵角PID控制
  *cmdSteer = constrain(-1.0, 1.0, angleController.calculate(currentAngleError));

  /* ----- 速度控制 ----- */
  double targetSpeed;
  double currentSpeed = _speed;
  
  //判断前方是直道还是弯道
  circle myCurve;
  float minCruve = 500.0;
  for (int fStep = 0; fStep < 50; fStep++)
  {
    myCurve = getR(
      _midline[fStep][0], _midline[fStep][1],
      _midline[fStep + 10][0], _midline[fStep + 10][1],
      _midline[fStep + 20][0], _midline[fStep + 20][1]
    );
    if (myCurve.r < minCruve)
      minCruve = myCurve.r;
  }

  // 基于前方赛道状态设定目标速度
  if (minCruve > 300)
      targetSpeed = 250;
  else if (minCruve > 150)
      targetSpeed = 150;
  else if (minCruve > 100)
      targetSpeed = 80;
  else
      targetSpeed = 50;

  // 每当目标速度变化时初始化PID控制器，重设参数，清空积分器和微分器
  if (targetSpeed != lastTargetSpeed)
  {
      speedController.initial(0.01, 0.0, 0.0, targetSpeed);
      lastTargetSpeed = targetSpeed;
  }

  // 根据当前速度和目标速度关系，控制油门刹车以改变速度
  if (currentSpeed < targetSpeed)  // 当前速度低于目标，需要加速
  {
    if (_speed > 100 && abs(*cmdSteer) < 0.1)     // 速度较快且舵角较小时，使用PID控制
      *cmdAcc = constrain(0.0, 1.0, speedController.calculate(currentSpeed));
    else if (_speed > 50 && abs(*cmdSteer) < 0.1) // 速度较慢且舵角较小时，限定油门
      *cmdAcc = 0.6;
    else                                          // 预料之外的情况下，进一步限定油门
      *cmdAcc = 0.3;

    // 加速状态下刹车为0
    *cmdBrake = 0;
  }
  else  // 减速情况下，刹车
  {
      *cmdAcc = 0;
      *cmdBrake = 0.3;
  }
  
  // 更新档位
  updateGear(cmdGear);
}
```