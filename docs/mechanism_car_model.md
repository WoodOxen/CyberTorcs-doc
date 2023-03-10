# 车辆动力学模型

在低速时，车辆的运动学特性较为突出；而在高速时，车辆的动力学特性对其运动状态影响较大。由于CyberTorcs仿真的是可能处于高速状态下的赛车，因此车辆物理状态更新是基于车辆的动力学模型，其具体实现可以参考[simuv3](https://github.com/jeremybennett/torcs/tree/r1-3-1/src/modules/simu/simuv3)。

[车辆运动学模型到动力学模型推导](https://zhuanlan.zhihu.com/p/493037015)

```cpp
/* 车辆物理状态的更新顺序 */

void
SimCarUpdate(tCar *car, tSituation * /* s */)
{
    SimCarUpdateForces(car);
    CHECK(car);
    SimCarUpdateSpeed(car);
    CHECK(car);
    SimCarUpdateCornerPos(car);
    CHECK(car);
    SimCarUpdatePos(car);
    CHECK(car);
    SimCarCollideZ(car);
    CHECK(car);
    SimCarCollideXYScene(car);
    CHECK(car);
}
```