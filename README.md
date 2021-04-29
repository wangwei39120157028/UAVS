# IntelligentUAVPathPlanningSimulationSystemS-Drone
Drone  Intelligent UAV path planning simulation system is a software with fine operation control, strong platform integration, omnidirectional model building and application automation. It takes the UAV war between A and B in Zone C as the background. The core function of the system is to plan the UAV route through the simulation platform and verify the output. The data can be imported into the real UAV to make it accurately arrive at any position in the battlefield according to the specified route and support the joint action of multi-person and multi-device formation.
### [Video Introduction](https://www.yuque.com/u12074055/kb/qqkaw9)
## Main Features
![1](https://user-images.githubusercontent.com/39434325/110713243-8d960580-823c-11eb-9caf-3b7a572d9732.jpeg)<br>
System supported by open source SITL uav simulation platform, through FlightGear rendering real battlefield environment, integrated modeling, 2 d vertical, three-dimensional dynamic model simulation, script control, ground station monitoring, data processing, and other functions, in addition, the simulation system supports a variety of global map load, simulate the key region of the three dimensional environment, can be used throughout the global remote sensing monitoring in the scene.
### 1. Software Interface
![2](https://user-images.githubusercontent.com/39434325/110713299-a69eb680-823c-11eb-8689-3b634a2a5f91.png)
### 2. Software Architecture (plug-ins to be implemented for some extended functions)
![3](https://user-images.githubusercontent.com/39434325/110713307-ab636a80-823c-11eb-93a0-fc7b6c8434c9.png)
### 3. Code
![4](https://user-images.githubusercontent.com/39434325/110713325-b4543c00-823c-11eb-8535-9cbf0aabecc6.png)
### 4. Multidimensional View
#### Two-dimensional view (1)
![5](https://user-images.githubusercontent.com/39434325/110713334-b9b18680-823c-11eb-95c8-d9ace97e9842.png)
#### Two-dimensional view (2)
![6](https://user-images.githubusercontent.com/39434325/110713350-c209c180-823c-11eb-8284-167268a5533a.png)
#### 3d view
![7](https://user-images.githubusercontent.com/39434325/110713362-c7ffa280-823c-11eb-9d30-d08ae469522f.png)
### 5. UAV Control
#### Console Control
![8](https://user-images.githubusercontent.com/39434325/110713375-cdf58380-823c-11eb-8efd-367f4535d42b.png)
#### Intelligent Control
![9](https://user-images.githubusercontent.com/39434325/110713391-d2ba3780-823c-11eb-882f-a82430b8bc42.png)
#### Ground Station Control
![10](https://user-images.githubusercontent.com/39434325/110713407-da79dc00-823c-11eb-9c8d-5cd2208a6c87.png)
### 6. Set Flight Mission
#### Flight Mission(1)
![11](https://user-images.githubusercontent.com/39434325/110713425-e1a0ea00-823c-11eb-8beb-1d9d7f52724a.png)
#### Flight Mission(2)
![12](https://user-images.githubusercontent.com/39434325/110713442-e9608e80-823c-11eb-86df-85b19b823738.png)
#### Flight Mission(3)
![13](https://user-images.githubusercontent.com/39434325/110713570-1b71f080-823d-11eb-97da-6651e9a00d60.png)
### 7. Path planning
The path algorithm is based on the redevelopment of Huiming Zhou's open source algorithm library (ZHM-Real /PathPlanning), adding elements such as UAV simulation, geographic coordinate conversion, and Leaflet visualization.
#### Directory Structure<br>

	drone_PathPlanning
		│  fence.txt
		│  leaflet_folium_plot.py
		│  mission.waypoints
		│          
		├─folium-0.12.1
		│              
		├─leaflet
		│          
		├─results
		│      CheckZorder.html
		│      us-states.json
		│      US_Unemployment_Oct2012.csv
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
		│  ├─rrt_2D
		│  │	  RRT
		│  │	  RRT-Connect
		│  │	  Extended-RRT
		│  │	  Dynamic-RRT
		│  │	  RRT*
		│  │	  Informed RRT*
		│  │	  RRT* Smart
		│  │	  Anytime RRT*
		│  │	  Closed-Loop RRT*
		│  │	  Spline-RRT*
		│  │	  Fast Marching Trees (FMT*)
		│  │	  Batch Informed Trees (BIT*)
		│  │          
		│  ├─rrt_2D_路径优化效果图
		│  │      
		│  └─rrt_3D        
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
			├─Search_2D
			│      Breadth-First Searching (BFS)
			│      Depth-First Searching (DFS)
			│      Best-First Searching
			│      Dijkstra's
			│      A*
			│      Bidirectional A*
			│      Anytime Repairing A*
			│      Learning Real-time A* (LRTA*)
			│      Real-time Adaptive A* (RTAA*)
			│      Lifelong Planning A* (LPA*)
			│      Dynamic A* (D*)
			│      D* Lite
			│      Anytime D*
			│          
			├─Search_2D_路径优化效果图
			│      
			└─Search_3D

#### Custom routes and obstacle areas
![自定义路线与障碍区](https://user-images.githubusercontent.com/39434325/116529533-a7d09380-a90f-11eb-9ad6-6e239d336e0b.PNG)
#### rrt_2D Path optimization effect chart
![rrt_2D_路径优化效果图](https://user-images.githubusercontent.com/39434325/116529610-c171db00-a90f-11eb-9506-8b2d7979d1f1.png)
#### Search_2D Path optimization effect chart
![Search_2D_路径优化效果图](https://user-images.githubusercontent.com/39434325/116529702-cf276080-a90f-11eb-951e-f6e5ccd3f7ab.png) <br>

## Solve The Problem

Intelligent UAV path planning simulation system solves the problem that ordinary UAV can not accurately plan the path, and ordinary UAV is not enough support, inconvenient to control, difficult to use in the actual war. This software can be designed for flight mission routes in advance, using a flight simulator unmanned aerial vehicle (uav) in the real-time state of mission, through strengthening unmanned aerial vehicle (uav) in the system against ground station module control, simulation of the unmanned aerial vehicle (uav) group of joint action tactical fighting, sailing and output data for the use of real unmanned aerial vehicle (uav), the uav size short, quick release, huge resource advantage as far as possible.

## Application Scenarios And Benefits

Up to now, more than 40 countries are engaged in the research and production of UAVs, and more than 60 countries are using UAVs. The use of drones on the battlefield is the future of warfare.

The advantage of using this software is that it absorbs the results obtained abroad, recompiles and transplants the operating environment from Linux system to Windows and other operating systems, and uses Python language to write the program except the simulation 3D environment module. The program is easy to maintain and modify. The software interface prepared by PyQT5 integrates each module of the software, adds background prompt function, designs intelligent control scripts to simplify the use process of the system, and integrates FlightGear simulator and MissionPlanner ground station program for visualization, so as to improve the accuracy of real UAV flight path and specify flight plan as the fundamental purpose.

## EXTENSION<br>
### On the formation simulation of multi-UAV
Using SITL to simulate multi-UAV formation under Windows, please refer to the following article. Note that the path should be tested under ArduCopter/ :<br>
https://blog.csdn.net/jzhd2015/article/details/108987818<br>
![电风扇的成熟度](https://user-images.githubusercontent.com/39434325/112772851-b94f2300-9065-11eb-8a29-4ac8b08d2c4f.PNG)<br>
Test of two-plane formation path algorithm:<br>
![4326547](https://user-images.githubusercontent.com/39434325/112721732-9aa33c00-8f40-11eb-8fc5-45a0c5cdcd3c.PNG)<br>
It can plan the flight path of left wing and right wing UAV respectively:<br>
![6464161](https://user-images.githubusercontent.com/39434325/112722145-ac85de80-8f42-11eb-93ec-40d36548bd53.PNG)<br>

### About the flight line under Flylitchi
I happened to see it on the oil pipe. After planning the flight route on the ground station Mission Planner and saving the navigation point, I could edit it with Excel, and then import the modified data in CSV format through the webpage or Android Litchi, so as to realize the DJI UAV flying in accordance with the flight route on the Litchi App.<br>
1.The web version can be edited directly on Flylitchi's website：https://flylitchi.com/hub<br>
Use method is very simple, visible "good know" tutorial：http://www.howzhi.com/course/13669/lesson/84384<br>

2.Litchi 4.7 APP editor for Android phone：https://www.52pojie.cn/thread-834234-1-1.html <br>
Baidu network disk link: https://pan.baidu.com/s/14qzvBuRIYhr_LhL7BRjd4Q    Extract the code: w5eu <br>
Built-in dual map, no need to download Google application, so that your Royal Air also has navigation point function.<br>
Android：Litchi for DJI Mavic / Phantom / Inspire / Spark Version 4.7.0<br>
- Panoramic mode speed and reliability improvements<br>
- Panorama mode Settings improved<br>
- Fixed failure to change the application language on some devices<br>

### Mission Planner + Google Earth log generates 3D trajectory maps
Google China satellite map is used instead. It mainly imports the planned path generated by the Mission Planner or the console of the ground station to the map, with.waypoint or KMZ file as the main file.<br>
![1111](https://user-images.githubusercontent.com/39434325/112245151-4facce80-8c8b-11eb-9ac9-706a7bb78bc5.PNG)

Please wait for updates on other extensions....

## Gratitude<br>
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

## Project Link<br>
JianShu：https://www.jianshu.com/p/b1e6b2efb96f<br>
Github：https://github.com/wangwei39120157028/IntelligentUAVPathPlanningSimulationSystem-Drone<br>
Gitee：https://gitee.com/wwy2018/intelligent-uavpath-planning-simulation-system-S<br>
Welcome To Star！！！
