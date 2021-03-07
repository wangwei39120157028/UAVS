# IntelligentUAVPathPlanningSimulationSystemS-Drone
Drone智能无人机路径规划仿真系统是一个具有操作控制精细、平台整合性强、全方向模型建立与应用自动化特点的软件。它以A、B两国在C区开展无人机战争为背景，该系统的核心功能是通过仿真平台规划无人机航线，并进行验证输出，数据可导入真实无人机，使其按照规定路线精准抵达战场任一位置，支持多人多设备编队联合行动。<br>
#### QQ交流群：809473689
#### 加微信-进入交流群：wwy18795980897
### [视频简介](https://www.yuque.com/u12074055/kb/qqkaw9)
## 一、主要特点
![智能无人机路径规划仿真系统](https://images.gitee.com/uploads/images/2021/0125/233607_f09b2d25_2323666.jpeg "13.jpg")<br>
系统以开源无人机仿真平台SITL为支撑，通过FlightGear渲染真实战场环境，集成了动力学模型建模、二维俯视、三维模拟、脚本控制、地面站监控、数据处理等功能，此外，仿真系统支持加载多种全球地图，模拟各大重点地域的三维环境，可应用于全球各处遥感监测的场景中。
### 1. 软件界面
![软件界面](https://images.gitee.com/uploads/images/2021/0125/233744_ba69880f_2323666.png "1.png")
### 2. 软件架构（部分扩展功能的插件待实现）
![软件架构](https://images.gitee.com/uploads/images/2021/0125/233759_e596a868_2323666.png "2.png")
### 3. 代码编写
![代码编写](https://images.gitee.com/uploads/images/2021/0125/233814_c0aa0ba5_2323666.png "3.png")
### 4. 多维视图
#### 二维视图（一）
![二维视图（一）](https://images.gitee.com/uploads/images/2021/0125/233838_febcde95_2323666.png "4.png")
#### 二维视图（二）
![二维视图（二）](https://images.gitee.com/uploads/images/2021/0125/233900_9a21536c_2323666.png "5.png")
#### 三维视图
![三维视图](https://images.gitee.com/uploads/images/2021/0125/233925_c9f2e081_2323666.png "6.png")
### 5. 无人机控制
#### 控制台控制
![控制台控制](https://images.gitee.com/uploads/images/2021/0125/233942_e93cbff8_2323666.png "7.png")
#### 智能控制
![智能控制](https://images.gitee.com/uploads/images/2021/0126/181402_cd1f8329_2323666.png "改git.png")
#### 地面站控制
![地面站控制](https://images.gitee.com/uploads/images/2021/0125/234015_bc90af97_2323666.png "9.png")
### 6. 制定飞行任务
#### 飞行任务（一）
![飞行任务（一）](https://images.gitee.com/uploads/images/2021/0125/234038_f5448a7f_2323666.png "10.png")
#### 飞行任务（二）
![飞行任务（二）](https://images.gitee.com/uploads/images/2021/0125/234057_37ff1cc1_2323666.png "11.png")
#### 飞行任务（三）
![飞行任务（三）](https://images.gitee.com/uploads/images/2021/0125/234121_a8022c2e_2323666.png "12.png")
## 二、解决问题

智能无人机路径规划仿真系统解决了普通无人机无法精准规划路径的问题，且普通无人机不够托底，不便控制，难以运用于实际战争。本软件可以预先为飞行任务设计航线，使用飞行模拟器记录无人机在飞行任务中的实时状态，通过地面站模块强化无人机在体系对抗中的受控度，模拟无人机群联合行动的战术战法，然后输出航行数据供真实无人机使用，将无人机体型短小、行动迅速、资源庞大的优势尽可能的释放出来。

## 三、应用场景及效益

截止目前，全世界已有40多个国家在从事研究和生产无人机，60多个国家在使用无人机。无人机在战场发挥作用是未来战争的趋势。

使用该软件的优点是吸收国外已获得成果，将运行环境从Linux系统重新编译移植到Windows等其他操作系统，除仿真三维环境模块外均使用Python语言编写，程序易维护、易修改。通过Pyqt5编写的软件界面集成了软件各个模块，加入后台提示功能，设计智能控制脚本简化系统使用流程，联动FlightGear模拟器、MissionPlanner地面站程序进行可视化，以提高真实无人机飞行路径精准度、指定飞行计划为根本目的。

## 四、扩展<br>
windows下使用 SITL 模拟多无人机编队请参照下面文章，注意路径要在ArduCopter/下执行测试命令：
https://blog.csdn.net/jzhd2015/article/details/108987818
其他扩展插件请等待更新....

## 五、感谢<br>
**CSDN：**<br>
https://blog.csdn.net/qinguoxiaoziyangyue/article/details/77712064<br>
https://blog.csdn.net/guojunxiu/article/details/79158843<br>
https://blog.csdn.net/huihut/article/details/86587782<br>
https://blog.csdn.net/u010946448/article/details/90718264<br>
https://blog.csdn.net/jzhd2015/article/details/108987818<br>
https://blog.csdn.net/jzhd2015/article/details/108663961<br>
**Zhihu:**<br>
https://zhuanlan.zhihu.com/p/50900595
https://zhuanlan.zhihu.com/p/62017292<br>
**Freesion：**<br>
https://www.freesion.com/article/2344608320/<br>
**Gitee：**<br>
https://gitee.com/wwy2018/XTDrone<br>
**Github：**<br>
https://github.com/dhondta/dronesploit<br>

## 项目链接<br>
简书地址：https://www.jianshu.com/p/b1e6b2efb96f<br>
Github：https://github.com/wangwei39120157028/IntelligentUAVPathPlanningSimulationSystem-Drone<br>
Gitee：https://gitee.com/wwy2018/intelligent-uavpath-planning-simulation-system-S<br>
欢迎star！！！
