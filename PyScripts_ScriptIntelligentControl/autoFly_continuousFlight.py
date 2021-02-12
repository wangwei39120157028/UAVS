#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Intelligent scripting: Simplified operation process, detailed instructions can help flight control better take-off.
此脚本可设置精准航点，使无人机连续飞行到达指定目的地

"""

from __future__ import print_function
import time
from dronekit import connect, VehicleMode, LocationGlobalRelative

print("""
   此脚本可设置精准航点，使无人机按照配置连续飞行到达指定目的地

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

# 通过本地的14551端口，使用UDP连接到SITL模拟器
connection_string ='127.0.0.1:14550' #'tcp:127.0.0.1:5760'  #
print('正在连接无人机: %s' % connection_string)
# connect函数将会返回一个Vehicle类型的对象，即此处的vehicle
# 即可认为是无人机的主体，通过vehicle对象，我们可以直接控制无人机
vehicle = connect(connection_string, wait_ready=True)

# 定义arm_and_takeoff函数，使无人机解锁并起飞到目标高度
# 参数aTargetAltitude即为目标高度，单位为米
def arm_and_takeoff(aTargetAltitude):
    # 进行起飞前检查
    print("正在进行起飞前检查......")
    # vehicle.is_armable会检查飞控是否启动完成、有无GPS fix、卡曼滤波器
    # 是否初始化完毕。若以上检查通过，则会返回True
    while not vehicle.is_armable:
        print(" 无人机正在初始化，请等待......")
        time.sleep(1)

    # 解锁无人机（电机将开始旋转）
    print("无人机初始化完毕，电机开始旋转")
    # 将无人机的飞行模式切换成"GUIDED"（一般建议在GUIDED模式下控制无人机）
    vehicle.mode = VehicleMode("GUIDED")
    # 通过设置vehicle.armed状态变量为True，解锁无人机
    vehicle.armed = True

    # 在无人机起飞之前，确认电机已经解锁
    while not vehicle.armed:
        print(" 正在为无人机供电，请等待......")
        time.sleep(1)

    # 发送起飞指令
    print("起飞!")
    # simple_takeoff将发送指令，使无人机起飞并上升到目标高度
    vehicle.simple_takeoff(aTargetAltitude)

    # 在无人机上升到目标高度之前，阻塞程序
    while True:
        print(" 上升高度: ", vehicle.location.global_relative_frame.alt)
        # 当高度上升到目标高度的0.95倍时，即认为达到了目标高度，退出循环
        # vehicle.location.global_relative_frame.alt为相对于home点的高度
        if vehicle.location.global_relative_frame.alt >= aTargetAltitude * 0.95:
            print("无人机已达到目标上升高度，随时准备行动")
            break
        # 等待1s
        time.sleep(1)

# 调用上面声明的arm_and_takeoff函数，目标高度10m
takeoff_high = input("请输入飞行高度m： ")
arm_and_takeoff(float(takeoff_high))

# 设置在运动时，默认的空速为3m/s
air_speed = input("请设置无人机空中运行速度m/s： ")
# vehicle.airspeed变量可读可写，且读、写时的含义不同。
# 读取时，为无人机的当前空速；写入时，设定无人机在执行航点任务时的默认速度
vehicle.airspeed = float(air_speed)

# 发送指令，让无人机前往第一个航点
#time_fly = input("请设置飞行时间/秒：  #无人机将在此时间过后前往下一处航点")
ground_speed_Q = input("是否设置地速[y/n]： ")

num = 1
record = []
while True:
    # LocationGlobalRelative是一个类，它由经纬度(WGS84)和相对于home点的高度组成
    # 这条语句将创建一个位于南纬35.361354，东经149.165218，相对home点高20m的位置
    waypointS = input("请输入第" + str(num) + "个航点纬度，若退出任务请输入E，南纬： ")#则填写35.361354,149.165218,20
    waypointE = input("请输入第" + str(num) + "个航点经度，若退出任务请输入E，东经： ")
    waypointH = input("请输入第" + str(num) + "个航点高度，若退出任务请输入E，高度： ")
    if waypointS == "E" or waypointE == "E" or waypointH == "E" or waypointS == "e" or waypointE == "e" or waypointH == "e":
        break
    point = LocationGlobalRelative(float(waypointS),float(waypointE),float(waypointH))

    if ground_speed_Q == "y" or ground_speed_Q == "Y":
        ground_speed = input("请设置无人机对地速度m/s： ")
        # simple_goto将目标航点发送给无人机，groundspeed=10设置飞行时的地速为ground_speed
        vehicle.simple_goto(point, groundspeed=float(ground_speed))
    else:
        # simple_goto函数将位置发送给无人机，生成一个目标航点
        vehicle.simple_goto(point)
    record.append(point)
    num += 1
    time.sleep(2)
    #time.sleep(float(time_fly))
    #vehicle.mode = VehicleMode("AUTO")
    # simple_goto函数只发送指令，不判断有没有到达目标航点
    # 它可以被其他后续指令打断，此处延时30s，即让无人机朝向point1飞行30s
    #if time_fly == "n" or time_fly == "N":
    #    vehicle.mode = VehicleMode("AUTO")
    #else:
    #    time.sleep(time_fly)

# 发送"返航"指令
print("飞行任务退出，无人机返回基地......")
# 返航，只需将无人机的飞行模式切换成"RTL(Return to Launch)"
# 无人机会自动返回home点的正上方，之后自动降落
vehicle.mode = VehicleMode("RTL")
#防止无人机继续向目的地飞行，将飞行模式调为可控，再返回基地
time.sleep(3)
vehicle.mode = VehicleMode("GUIDED")
vehicle.mode = VehicleMode("RTL")

filename = time.strftime("%Y-%m-%d_%H-%M-%S", time.localtime()) + '.txt'
with open(filename, 'a') as file_object:
    for i in range(len(record)):
        file_object.write(str(i))
        file_object.write("    ")
        file_object.write(str(record[i]))
        file_object.write("\n")
print("航点记录成功！")   
# 退出之前，清除vehicle对象
print("......任务结束......")
vehicle.close()


