# -*- coding: utf-8 -*-
'''
---------------------------------------------------------------------------
Intelligent scripting: Simplified operation process, detailed instructions can help flight control better take-off.
控制无人机前后左右升降俯仰

---------------------------------------------------------------------------

'''


from __future__ import print_function
import time
from dronekit import connect, VehicleMode, LocationGlobalRelative
from pymavlink import mavutil

print("""
   此脚本可控制无人机前后左右升降俯仰，判断当前环境无人机灵敏性

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
vehicle = connect('127.0.0.1:14551', wait_ready=True)

#起飞
def arm_and_takeoff(aTargetAltitude):
    
    print("起飞前检查......") 
    while not vehicle.is_armable:
        print (" 等待飞机初始化......") 
        time.sleep(1)

    print ("切换至GUIDED模式......")
    vehicle.mode    = VehicleMode("GUIDED")
    print ("无人机解除锁定...")
    vehicle.armed   = True

    while not vehicle.armed:
        print ("等待解锁......")
        time.sleep(1)
    print ("起飞!!!......")
    vehicle.simple_takeoff(aTargetAltitude) 

    while True:
        print (" 当前高度: ", vehicle.location.global_relative_frame.alt)
        if vehicle.location.global_relative_frame.alt>=aTargetAltitude*0.95:
            print ("到达目标高度......")
            break
        time.sleep(1)

#前后左右上下移动
def send_ned_velocity(velocity_x, velocity_y, velocity_z, duration):
    """
    Move vehicle in direction based on specified velocity vectors.
    """
    msg = vehicle.message_factory.set_position_target_local_ned_encode(
        0,       
        0, 0,    
        mavutil.mavlink.MAV_FRAME_LOCAL_NED, 
        0b0000111111000111, 
        0, 0, 0, 
        velocity_x, velocity_y, velocity_z, 
        0, 0, 0, 
        0, 0)    
    #循环发送几次
    for x in range(0,duration):
        #发送指令
        vehicle.send_mavlink(msg)
        time.sleep(1)

#偏航
def condition_yaw(heading, relative=False):
    if relative:
        is_relative=1 
    else:
        is_relative=0 
    msg = vehicle.message_factory.command_long_encode(
        0, 0,  
        mavutil.mavlink.MAV_CMD_CONDITION_YAW, 
        0, 
        heading,    
        0,         
        1,         
        is_relative, 
        0, 0, 0)   
    #发送指令
    vehicle.send_mavlink(msg)

#起飞
arm_and_takeoff(10)

#移动
send_ned_velocity(5, 5, -2, 1)
time.sleep(3)

#偏航45
condition_yaw(45)
time.sleep(3)

print("设置模式返航...")
vehicle.mode = VehicleMode("RTL")

print("关闭连接")
vehicle.close()
