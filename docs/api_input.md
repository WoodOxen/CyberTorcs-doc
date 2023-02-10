# 程序编写接口

## 输入接口

```cpp
static void userDriverGetParam(
    float midline[200][2],  //道路中先XY坐标（米）
    /*
    - 预瞄点：midline[k][2]，k<200
    - 道路起点：与车辆几何中心最近点
    - 沿道路中线k米处的XY坐标值
    */
    float yaw,              // 偏航角
    /*车辆运动方向Y与道路的夹角*/
    float yawrate,          //角速度（弧度/秒）
    float speed,            //车速（公里/小时）
    float acc,              //acc加速度（米/秒^2）
    float width,            //道路宽度（米）
    int gearbox,            //档位（-1~6）
    float rpm               //发动机转速（RPM）
);
```

## 输出接口

```cpp
static void userDriverSetParam(
    float* cmdAcc,          //油门命令[0.0, 1.0]，0表示不踩油门
    float* cmdBrake,        //刹车命令[0.0, 1.0]，0表示不踩刹车
    float* cmdSteer,        //转向命令[-1.0, 1.0]，-1表示顺时针打满
    int* cmdGear            //变速箱档位{r,1,2,3,4,5,6}
);
```
