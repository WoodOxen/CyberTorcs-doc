# 安装

本页面提供了在 Windows 操作系统下安装和运行 CyberTorcs 的操作教程。

## 软硬件要求

- 硬件要求：
    - CPU 最低频率：800MHz
    - 最小内存：256MB
    - 最小显存：64MB
    - 磁盘空间：>1G
- 操作系统要求：Windows 10/XP
- 依赖库：OpenGL 1.3
- 开发环境（推荐）：

    - 集成开发环境（IDE）：
        
        - [Visual Studio](https://visualstudio.microsoft.com/)（版本：2010/2012/2013/2017/2019）
        - [CLion](https://www.jetbrains.com/clion/)

- 代码编辑器：[Visual Studio Code](https://code.visualstudio.com/)

相关资料：[什么是编辑器和编译器，什么是集成开发环境？编译原理又是什么？](https://zhuanlan.zhihu.com/p/126164350)

## 安装步骤

### 软件安装

下载课程网站提供的软件压缩包，解压至电脑即可。

## 快速开始

### 安装 Visual Studio 集成开发环境

1. 在[交大云盘](https://jbox.sjtu.edu.cn/v/list/ent/936369142)下载 VisualStudio 的安装引导文件
    ![下载 Visual Studio 的安装引导文件](imgs/install/vs_download.png)
2. 双击打开 VisualStudio 安装引导文件，选择需要安装的开发工具，这里选择 **使用 C++的桌面开发**，然后安装。
    ![安装 Visual Studio!](imgs/install/vs_install.png)

### 运行软件

打开解压缩后得到的文件夹 CyberTorcs，直接运行 `wtorcs.exe` 。具体软件界面介绍请参考[简介-设置菜单介绍](https://cybertorcs.readthedocs.io/zh_CN/latest/intro_settings/)。

### 编程步骤

以下以巡线任务为例，说明如何在CyberTorcs中使用自己编程的代码控制车辆运行。

1. 下载课程网站提供的模板代码压缩包并解压。
2. 选择工程文件`driver_cruise.sln`，右键选择通过 Visual Studio 打开；
3. 打开后确认编译方式为 **Release**，然后点击 **本地 Windows 调试器** 编译；
    ![编译](imgs/install/compile.png)
4. 成功编译时，命令行会提示 *成功1个……*。 
   弹出窗口警告提示 *无法启动程序* 是因为生成的是 dll 文件，而不是可执行文件，系统无法直接执行编译生成的结果，该警告不会影响编译结果；
    ![编译结果](imgs/install/compile_result.png)
5. 编译完成后，`./Release/`中新生成了 dll 文件；
    ![生成dll](imgs/install/generate_dll.png)
6. 将新生成的 dll 文件复制到 Torcs 文件夹下的 cybercruise 文件夹中，替换旧的 dll 文件；
    ![发布dll](imgs/install/release_dll.png)
7. 

!!! tip 初次编译失败
    初次打开项目文件编译时可能会出现编译失败，命令行中提示 *重定目标* 的报错信息，按命令行给出的操作方法处理即可。