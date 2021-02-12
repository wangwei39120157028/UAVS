# -*- coding: utf-8 -*-

'''
---------------------------------------------------------------------------
Intelligent scripting: Simplified operation process, detailed instructions can help flight control better take-off.
获取无人机基础状态信息

---------------------------------------------------------------------------

'''
from __future__ import print_function
import time
from dronekit import connect, VehicleMode, LocationGlobalRelative
from pymavlink import mavutil

print("""
               此脚本可获取无人机基础状态信息

                                                    version==1.0

                       /$$               /$$$$$$$$ /$$          
                      | $$              | $$_____/| $$          
  /$$$$$$  /$$   /$$ /$$$$$$    /$$$$$$ | $$      | $$ /$$   /$$
 |____  $$| $$  | $$|_  $$_/   /$$__  $$| $$$$$   | $$| $$  | $$
  /$$$$$$$| $$  | $$  | $$    | $$  \ $$| $$__/   | $$| $$  | $$
 /$$__  $$| $$  | $$  | $$ /$$| $$  | $$| $$      | $$| $$  | $$
|  $$$$$$$|  $$$$$$/  |  $$$$/|  $$$$$$/| $$      | $$|  $$$$$$$
 \_______/ \______/    \___/   \______/ |__/      |__/ \____  $$
                                                       /$$  | $$
                                                      |  $$$$$$/
                                                       \______/ 
                      
                                                    by:wwy
"""

)

#连接
vehicle = connect('127.0.0.1:14550', wait_ready=True)

#起飞
def arm_and_takeoff(aTargetAltitude):
    
    print("起飞前检查......") 
    while not vehicle.is_armable:
        print (" 等待飞机初始化......") 
        time.sleep(1)
    print ("切换至GUIDED模式......")
    vehicle.mode    = VehicleMode("GUIDED")
    print ("无人机解除锁定......")
    vehicle.armed   = True
    while not vehicle.armed:
        print ("等待解锁...")
        time.sleep(1)
    print ("起飞!!!......")
    vehicle.simple_takeoff(aTargetAltitude) 
    while True:
        print (" 当前高度：", vehicle.location.global_relative_frame.alt)
        
        if vehicle.location.global_relative_frame.alt>=aTargetAltitude*0.95:
            print ("到达目标高度......")
            break
        time.sleep(1)
#起飞5m
arm_and_takeoff(5)

#版本
print ("固件版本：%s" % vehicle.version)
#全球定位信息
#经纬和高度
print ("经度、纬度和飞行高度：%s" % vehicle.location.global_frame) 
#经纬和相对高度
print ("经度、纬度和相对飞行高度：%s" % vehicle.location.global_relative_frame) 
#相对home点的位置信息
print ("相对基地的位置信息：%s" % vehicle.location.local_frame  )  
#高度
print ("无人机高度：%s" % vehicle.attitude) 
#速度
print ("无人机速度：%s" % vehicle.velocity) 
#Gps质量
print ("GPS：%s" % vehicle.gps_0) 
#地速
print ("飞行地速：%s" % vehicle.groundspeed)
#空速 
print ("飞行空速：%s" % vehicle.airspeed) 
#云台
print ("云台状态：%s" % vehicle.gimbal) 
#电量
print ("电量：%s" % vehicle.battery) 
#ekf
print ("EKF OK?：%s" % vehicle.ekf_ok) 
#心跳
print ("最近一次检测信号：%s" % vehicle.last_heartbeat) 
#超声波或激光
print ("测距仪：%s" % vehicle.rangefinder) 
#距离
print ("测距仪——距离：%s" % vehicle.rangefinder.distance) 
#电压
print ("测距仪——电压：%s" % vehicle.rangefinder.voltage) 
#朝向
print ("无人机朝向：%s" % vehicle.heading) 
#是否可以解锁
print ("无人机是否解除锁定?：%s" % vehicle.is_armable) 
#系统状态
print ("系统状态：%s" % vehicle.system_status.state) 
#飞行模式
print ("当前飞行模式：%s" % vehicle.mode.name  )   
#解锁状态
print ("无人机解除锁定：%s" % vehicle.armed  )  


print("飞行任务退出，无人机返回基地......")
vehicle.mode = VehicleMode("LAND")
print("......任务结束......")
vehicle.close()
