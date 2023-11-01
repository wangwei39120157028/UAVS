# ![UAVS](https://user-images.githubusercontent.com/39434325/207494865-00861da1-0a66-4d4e-8526-603d9cc2fc52.png) ![](https://img.shields.io/badge/UAVS-Drone-red)<br>
UAVS_Drone智能无人机路径规划仿真系统是一个具有操作控制精细、平台整合性强、全方向模型建立与应用自动化特点的软件。它以A、B两国在C区开展无人机战争为背景，该系统的核心功能是通过仿真平台规划无人机航线，并进行验证输出，数据可导入真实无人机，使其按照规定路线精准抵达战场任一位置，支持多人多设备编队联合行动。<br>
#### QQ交流1群：809473689（已满）
#### QQ交流2群：774627310（已满）
#### QQ交流3群：712810644
#### QQ交流4群：713783925
#### QQ交流5群：722396428
#### QQ交流6群：700903981
#### 加微信-进入交流群：wwy18795980897
### [视频简介](https://www.yuque.com/u12074055/kb/qqkaw9)<br>
### [安装手册](https://gitee.com/wwy2018/UAVS/blob/master/UAVS_InstructionManual.pdf)<br>
## 一、主要特点
![1](https://user-images.githubusercontent.com/39434325/110713673-43615400-823d-11eb-91db-b8151e68e926.jpeg)<br>
系统以开源无人机仿真平台SITL为支撑，通过FlightGear渲染真实战场环境，集成了动力学模型建模、二维俯视、三维模拟、脚本控制、地面站监控、数据处理等功能，此外，仿真系统支持加载多种全球地图，模拟各大重点地域的三维环境，可应用于全球各处遥感监测的场景中。
### 1. 软件界面
![2](https://user-images.githubusercontent.com/39434325/110713684-48260800-823d-11eb-8422-f051c9f1fd0a.png)
### 2. 软件架构（部分扩展功能的插件待实现）
![3](https://user-images.githubusercontent.com/39434325/110713694-4bb98f00-823d-11eb-8fe9-09c591975299.png)
### 3. 代码编写
![4](https://user-images.githubusercontent.com/39434325/110713702-4f4d1600-823d-11eb-97e8-5f58c69a1aa1.png)
### 4. 多维视图
#### 二维视图（一）
![5](https://user-images.githubusercontent.com/39434325/110713711-54aa6080-823d-11eb-8c17-ff3f1336b5a4.png)
#### 二维视图（二）
![6](https://user-images.githubusercontent.com/39434325/110713723-5bd16e80-823d-11eb-86ce-29389c362478.png)
#### 三维视图
![7](https://user-images.githubusercontent.com/39434325/110713736-61c74f80-823d-11eb-883c-b50c7e75486f.png)
### 5. 无人机控制
#### 控制台控制
![8](https://user-images.githubusercontent.com/39434325/110713744-668c0380-823d-11eb-8ec7-99b5a509d046.png)
#### 智能控制
![9](https://user-images.githubusercontent.com/39434325/110713758-6ab82100-823d-11eb-8015-2faff63fef55.png)
#### 地面站控制
![10](https://user-images.githubusercontent.com/39434325/110713826-891e1c80-823d-11eb-9929-085cbe7d00fc.png)
### 6. 制定飞行任务
#### 飞行任务（一）
![11](https://user-images.githubusercontent.com/39434325/110713844-90452a80-823d-11eb-9eb7-f2d83f21dd39.png)
#### 飞行任务（二）
![12](https://user-images.githubusercontent.com/39434325/110713854-963b0b80-823d-11eb-9fef-5fd23bde2a9c.png)
#### 飞行任务（三）
![13](https://user-images.githubusercontent.com/39434325/110713868-9cc98300-823d-11eb-9fe1-7e2ce670fb2e.png)
### 7. 路径规划
路径算法是基于Huiming Zhou的开源算法库（zhm-real/PathPlanning）的再开发，增加了无人机模拟、地理坐标转换、leaflet可视化等元素。
#### 目录导图<br>

	drone_PathPlanning.
		├─fence.txt
		├─leaflet_folium_plot.py
		├─mission.waypoints
		│          
		├─folium-0.12.1
		│              
		├─leaflet
		│          
		├─results
		│      
		├─Sampling_based_Planning
		│  ├─algorithm_mission_rrt2D
		│  │      algorithm_mission_batch_informed_trees.waypoints
		│  │      algorithm_mission_dubins_rrt_star.waypoints
		│  │      algorithm_mission_dynamic_rrt.waypoints
		│  │      algorithm_mission_extended_rrt.waypoints
		│  │      algorithm_mission_fast_marching_trees.waypoints
		│  │      algorithm_mission_informed_rrt_star.waypoints
		│  │      algorithm_mission_rrt.waypoints
		│  │      algorithm_mission_rrt_connect.waypoints
		│  │      algorithm_mission_rrt_star.waypoints
		│  │      algorithm_mission_rrt_star_smart.waypoints
		│  │      
		│  ├─indoor_obstacle_avoidance_rrt3D
		│  │      IOAPath_rrt3D.waypoints
		│  │      IOAPath_rrt_star3D.waypoints
		│  │      IOA_BIT_star3D.waypoints
		│  │      IOA_extend_rrt3D.waypoints
		│  │      
		│  ├─rrt_2D
		│  │      batch_informed_trees.py       BIT*算法
		│  │      draw.py
		│  │      dubins_path.py                Dubins路径算法
		│  │      dubins_rrt_star.py            Dubins_rrt*算法
		│  │      dynamic_rrt.py                动态RRT算法
		│  │      env.py
		│  │      extended_rrt.py               Extended_RRT算法
		│  │      fast_marching_trees.py        FMT*算法
		│  │      informed_rrt_star.py          Informed_rrt*算法
		│  │      judge.py
		│  │      plotting.py
		│  │      queue.py
		│  │      rrt.py                        rrt算法
		│  │      rrt_connect.py                RRT_CONNECT算法
		│  │      rrt_star.py                   rrt*算法
		│  │      rrt_star_smart.py             rrt*-Smart算法
		│  │      utils.py
		│  │      __init__.py
		│  │          
		│  ├─rrt_2D_路径优化效果图
		│  │      
		│  ├─rrt_3D
		│  │     ABIT_star3D.py
		│  │     BIT_star3D.py
		│  │     dynamic_rrt3D.py
		│  │     env3D.py
		│  │     extend_rrt3D.py
		│  │     FMT_star3D.py
		│  │     informed_rrt_star3D.py
		│  │     plot_util3D.py
		│  │     queueL.py
		│  │     rrt3D.py
		│  │     rrt_connect3D.py
		│  │     rrt_star3D.py
		│  │     utils3D.py
		│  │          
		│  └─rrt_3D_室内避障效果图
		│          
		└─Search_based_Planning
			├─algorithm_mission_Search2D
			│      algorithm_mission_Anytime_D_star.waypoints
			│      algorithm_mission_ARAstar.waypoints
			│      algorithm_mission_Astar.waypoints
			│      algorithm_mission_Best_First.waypoints
			│      algorithm_mission_bfs.waypoints
			│      algorithm_mission_Bidirectional_a_star.waypoints
			│      algorithm_mission_Bidirectional_dfs.waypoints
			│      algorithm_mission_Bidirectional_Dijkstra.waypoints
			│      algorithm_mission_Bidirectional_D_star.waypoints
			│      algorithm_mission_Bidirectional_D_star_Lite.waypoints
			│      algorithm_mission_Bidirectional_LPAstar.waypoints
			│      algorithm_mission_Bidirectional_LRTAstar.waypoints
			│      algorithm_mission_Bidirectional_RTAAStar.waypoints
			│      
			├─indoor_obstacle_avoidance_Search_3D
			│      IOA_Anytime_Dstar3D.waypoints
			│      IOA_Astar3D.waypoints
			│      IOA_bidirectional_Astar3D.waypoints
			│      IOA_Dstar3D.waypoints
			│      IOA_DstarLite3D.waypoints
			│      IOA_LP_Astar3D.waypoints
			│      IOA_LRT_Astar3D.waypoints
			│      IOA_RTA_Astar3D.waypoints
			│      
			├─Search_2D
			│     Anytime_D_star.py           AnytimeD*搜索算法
			│     ARAstar.py                  ARA*搜索算法
			│     Astar.py                    A*搜索算法
			│     Best_First.py               最佳路径优先搜索算法
			│     bfs.py                      广度优先算法
			│     Bidirectional_a_star.py     双向A*搜索算法
			│     dfs.py                      深度优先搜索算法
			│     Dijkstra.py                 Dijkstra搜索算法
			│     D_star.py                   D*搜索算法
			│     D_star_Lite.py              D*反向搜索算法
			│     env.py
			│     LPAstar.py                  终身规划A*算法
			│     LRTAstar.py                 LRTA*搜索算法
			│     plotting.py
			│     queueL.py
			│     RTAAStar.py                 RTAA*搜索算法
			│          
			├─Search_2D_路径优化效果图
			│      
			├─Search_3D
			│     Anytime_Dstar3D.py
			│     Astar3D.py
			│     bidirectional_Astar3D.py
			│     Dstar3D.py
			│     DstarLite3D.py
			│     env3D.py
			│     LP_Astar3D.py
			│     LRT_Astar3D.py
			│     plot_util3D.py
			│     queueL.py
			│     RTA_Astar3D.py
			│     utils3D.py
			│          
			└─Search_3D_室内避障效果图

### 室外避障
#### 自定义路线和障碍区域
![自定义路线与障碍区](https://user-images.githubusercontent.com/39434325/116529533-a7d09380-a90f-11eb-9ad6-6e239d336e0b.PNG)
#### rrt_2D_路径优化效果图
![rrt_2D_路径优化效果图](https://user-images.githubusercontent.com/39434325/116529610-c171db00-a90f-11eb-9506-8b2d7979d1f1.png)
#### Search_2D_路径优化效果图
![Search_2D_路径优化效果图](https://user-images.githubusercontent.com/39434325/116529702-cf276080-a90f-11eb-951e-f6e5ccd3f7ab.png) <br>

### 室内避障
由于室内结构具有空间狭窄，干扰物多的特点，此时路径规划程度更侧重于三维层次的避障效果，地图显得无意义。这里仍然依照Huiming Zhou的开源算法库为模型基础，使用建模的思想创建室内环境，运用Search_based_Planning及Sampling_based_Planning的3D算法对飞行路径进行避障规划。飞行演示如下：<br>
![IOA_DstarLite3D](https://user-images.githubusercontent.com/39434325/118637888-dd7ae500-b808-11eb-916b-530b1d8393ee.gif)
#### rrt_3D_室内避障效果图
![rrt_3D_室内避障效果图1](https://user-images.githubusercontent.com/39434325/118637923-e4a1f300-b808-11eb-83f0-5c9137af4a1a.PNG)
#### Search_3D_室内避障效果图
![Search_3D_室内避障效果图1](https://user-images.githubusercontent.com/39434325/118637946-e966a700-b808-11eb-8006-f21af8f695be.PNG)

### 路径优化
增加随机、贪心、路径最优算法聚类，区域路径随机生成、区域路径最短距离优先生成算法对多无人机集群飞行路径进行优化。
#### 算法生成各无人机飞行情况，经过航点，飞行距离信息
![路径优化-1](https://user-images.githubusercontent.com/39434325/125012329-9557a080-e09c-11eb-908d-01ae1a72e55d.PNG)
#### 路径优化效果图
![路径优化效果图片](https://user-images.githubusercontent.com/39434325/125012342-9be61800-e09c-11eb-8c72-672537dfb60c.png)

## 二、解决问题

智能无人机路径规划仿真系统解决了普通无人机无法精准规划路径的问题，且普通无人机不够托底，不便控制，难以运用于实际战争。本软件可以预先为飞行任务设计航线，使用飞行模拟器记录无人机在飞行任务中的实时状态，通过地面站模块强化无人机在体系对抗中的受控度，模拟无人机群联合行动的战术战法，然后输出航行数据供真实无人机使用，将无人机体型短小、行动迅速、资源庞大的优势尽可能的释放出来。

## 三、应用场景及效益

截止目前，全世界已有40多个国家在从事研究和生产无人机，60多个国家在使用无人机。无人机在战场发挥作用是未来战争的趋势。

使用该软件的优点是吸收国外已获得成果，将运行环境从Linux系统重新编译移植到Windows等其他操作系统，除仿真三维环境模块外均使用Python语言编写，程序易维护、易修改。通过Pyqt5编写的软件界面集成了软件各个模块，加入后台提示功能，设计智能控制脚本简化系统使用流程，联动FlightGear模拟器、MissionPlanner地面站程序进行可视化，以提高真实无人机飞行路径精准度、指定飞行计划为根本目的。

## 四、扩展<br>
### 关于多无人机的编队模拟
windows下使用 SITL 模拟多无人机编队请参照下面文章，注意路径要在ArduCopter/下执行测试命令：
https://blog.csdn.net/jzhd2015/article/details/108987818<br>
![电风扇的成熟度](https://user-images.githubusercontent.com/39434325/112772851-b94f2300-9065-11eb-8a29-4ac8b08d2c4f.PNG)<br>
双机编队路径算法测试：
![4326547](https://user-images.githubusercontent.com/39434325/112721732-9aa33c00-8f40-11eb-8fc5-45a0c5cdcd3c.PNG)
可分别规划左侧、右侧四翼无人机飞行路径
![6464161](https://user-images.githubusercontent.com/39434325/112722145-ac85de80-8f42-11eb-93ec-40d36548bd53.PNG)

### 关于flylitchi下的航线飞行
在油管上偶然看到，通过地面站Mission Planner规划航线,保存航点后，可用Excel对其进行编辑，再通过网页端或安卓端Litchi导入修改后的CSV格式的数据，进而实现大疆无人机在Litchi APP上按照航线飞行。<br>
1.网页版可在flylitchi官网直接编辑（国外网站-需要跳板）：https://flylitchi.com/hub<br>
使用方法十分简单，可见《好知》教程：http://www.howzhi.com/course/13669/lesson/84384<br>

2.安卓手机Litchi 4.7 APP编辑（吾爱破解下载地址）：https://www.52pojie.cn/thread-834234-1-1.html <br>
百度网盘链接: https://pan.baidu.com/s/14qzvBuRIYhr_LhL7BRjd4Q    提取码: w5eu <br>
内置的双地图，不用下载谷歌应用，让你的御AIR也有航点功能<br>
Android：Litchi for DJI Mavic / Phantom / Inspire / Spark版本4.7.0<br>
- 全景模式速度和可靠性改进<br>
- 全景模式设置改进<br>
- 修复了在某些设备上更改应用程序语言失败的错误<br>

### Mission planner + Google Earth 日志生成3D轨迹图
仍需跳板，这里使用谷歌中国卫星地图代替，主要是向地图导入地面站Mission planner或控制台生成的规划路径，以.waypoint或kmz文件为主<br>
![1111](https://user-images.githubusercontent.com/39434325/112245151-4facce80-8c8b-11eb-9ac9-706a7bb78bc5.PNG)

### CoppeliaSim仿真（2023年11月1日更新）
截至目前，项目在GitHub已超过400 star，Gitee也即将突破400 star，之前有用户反馈三维环境不够立体，仿真样式过于简单，现在CoppeliaSim仿真环境中增加三维室内避障，以Atar算法展示效果（为便于演示，缩短UAV与target距离）<br>
#### CoppeliaSim仿真环境<br>
![CoppeliaSim避障1](https://github.com/wangwei39120157028/UAVS/assets/39434325/5a8e716e-f246-4598-8853-2af3dca6f73b)
#### 仿真环境数据化颗粒化<br>
![CoppeliaSim避障2](https://github.com/wangwei39120157028/UAVS/assets/39434325/21a0cb8d-c770-4733-aae6-7c81bbc11944)
#### CoppeliaSim仿真效果<br>
![20231101-CoppeliaSim避障 00_00_00-00_00_30](https://github.com/wangwei39120157028/UAVS/assets/39434325/b2747ce2-65a1-43d5-8bd0-37a5b1b98eb6)

其他扩展插件请等待更新....

## Problems 关于一些普遍反映问题的解决方法<br>
### 1.关于Cywin64无法带参数<br>
关于Cywin64无法带参数启动于Windows下CMD终端，-e参数执行命令找不到目标文件夹无果，mintty的启动位置总是不统一，更重要的是没有具体在mintty内执行命令的语法参数。<br>
### 2.关于FlightGear在虚拟机中无法正常运行的问题<br>
智能无人机路径规划仿真系统在虚拟机内无法运行FlightGear 2018.2.2，其原因有二：一是虚拟机的VMTools有问题，导致与显卡交互不当，重新安装无果；二是虚拟机不支持opengl，无法显示FlightGear的界面。<br>
### 3.关于CorelDRAW和智能无人机仿真系统path冲突的问题<br>
UAVS和CorelDRAW等软件对QT_QPA_PLATFORM_PLUGIN_PATH路径均有使用，可能造成冲突，可在path中更改为UAVS路径...\python-3.7.5-embed-amd64\Lib\site-packages\PyQt5\Qt\plugins解决。<br>

## 五、感谢<br>
**CSDN：**<br>
https://blog.csdn.net/qinguoxiaoziyangyue/article/details/77712064<br>
https://blog.csdn.net/guojunxiu/article/details/79158843<br>
https://blog.csdn.net/huihut/article/details/86587782<br>
https://blog.csdn.net/u010946448/article/details/90718264<br>
https://blog.csdn.net/jzhd2015/article/details/108987818<br>
https://blog.csdn.net/jzhd2015/article/details/108663961<br>
**Zhihu:**<br>
https://zhuanlan.zhihu.com/p/50900595<br>
https://zhuanlan.zhihu.com/p/62017292<br>
**Freesion：**<br>
https://www.freesion.com/article/2344608320/<br>
**Gitee：**<br>
https://gitee.com/wwy2018/XTDrone<br>
**Github：**<br>
https://github.com/dhondta/dronesploit<br>

## 项目链接<br>
简书地址：https://www.jianshu.com/p/b1e6b2efb96f<br>
Github：https://github.com/wangwei39120157028/UAVS<br>
Gitee：https://gitee.com/wwy2018/UAVS<br>
欢迎star！！！
