# 平台结构

本文档简单介绍了CyberTorcs的文件结构，方便使用者进一步开发或定制功能。

## 平台架构示意图

## 文件夹结构说明

以下是文件夹基本结构和功能的介绍。

```sh
.
├── wtorcs.exe
│   # CyberTorcs仿真器的可执行文件
├── cars
│   # 车辆建模、贴图、音效数据
├── categories
│   # 不同环境/物理模式下的参数数据
├── config
│   # 仿真器设置数据的保存路径
├── cybercruise
│   # 存放巡线任务所需车辆控制程序文件的路径
├── cyberfollow
│   # 存放跟车任务所需车辆控制程序文件的路径
├── cyberonhand
│   # 提供手动操作车辆所需的.dll文件
├── cyberparking
│   # 存放泊车任务所需车辆控制程序文件的路径
├── data
│   # 字体、UI、背景音、材质等数据
├── drivers
│   # 提供了展示各任务实现示例的.dll文件
├── menu
│   # 菜单界面的索引文件
├── modules
│   # 仿真器的一些功能性模块
├── results
│   # 各项驾驶任务完成后，生成的评分的保存路径
├── screenshots
│   # 生成截图后的保存路径
├── telemetry
│   # 
├── tracks
│   # 赛道建模、贴图数据
└── wheels
    # 车轮建模、贴图数据
```
