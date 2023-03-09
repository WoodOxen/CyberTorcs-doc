# Stanley角度控制模板代码

![stanley计算示意图](./imgs/tasks/stanley_angel_model.png)

角度误差$\delta$来源于两部分：横向误差$\delta_e$和航向误差$\theta_e$。

其中航向误差$\theta_e$为车辆方向与道路切向的夹角，通过atan计算前轮最近的道路中心线在车体坐标系的角度偏差，即对应当前时刻的航向误差$\theta_e$。

其中横向偏差$\delta_e = \frac{d(t)}{e}$， 而d(t)与车辆速度相关，用比例系数k*v(t)描述，因此得到$\delta_e = \frac{k*v(t)}{e}$。对应代码如下


```cpp
	double lfAngleError = -atan2(_midline[5][0]- _midline[4][0], _midline[5][1] - _midline[4][1]); 

	double lfDistance = _midline[0][0] < 0 ? length(_midline[0][0], _midline[0][1], 0, 0) :
		-length(_midline[0][0], _midline[0][1], 0, 0);

	double lfStanley_K;
	circle Curve4Stanley = getR(_midline[0][0], _midline[0][1],
								_midline[10][0], _midline[10][1],
								_midline[20][0], _midline[20][1]);
	
	if (Curve4Stanley.r < 50)
		lfStanley_K = 11;
	else if (Curve4Stanley.r < 100)
		lfStanley_K = 7;
	else
		lfStanley_K = 3;

	double lfDistanceError = atan(lfStanley_K * lfDistance / _speed);
	*cmdSteer = constrain(-1, 1, lfAngleError + lfDistanceError);
```