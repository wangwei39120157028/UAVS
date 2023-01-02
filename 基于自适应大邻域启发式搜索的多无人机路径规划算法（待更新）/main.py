#!usr/bin/env python
#encoding:utf-8
from __future__ import division

import math
import random
import os
import json
import folium
import pandas as pd
from folium import plugins


#随即聚类算法：返回结果是vector2:[[类1（numTar序号排列）],[类2],[类三],[类四]]
def get_Clustering_Rand2(numUAV, numTar):
    #step1:确定每组目标的数量，并存于数组arr1_num中
    eachNumUp = math.fabs((1.0 * numTar) / numUAV)
    eachNumLow = int(math.floor((1.0 * numTar) / numUAV))
    surplusNum = numTar - numUAV * eachNumLow
    arr1_num = {}
    for i in range(numUAV):
        arr1_num[i] = eachNumLow
    if surplusNum != 0:  #未分配完毕
        arr1_num[numUAV - 1] = eachNumLow + surplusNum
    #step2:创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
    arr2_temp1 = {}
    ranList = random.sample(range(1,numTar + 1),numTar)
    #random.sample(range(A,B+1),COUNT)
    for i in range(numTar):
        arr2_temp1[i] = ranList[i]
    #step3:将step1生成的数组按照第2列的随机数进行排序（升序或降序）
    arr2_temp1 = sorted(arr2_temp1.items(),key = lambda x:x[1],reverse = False)  # 按字典集合中，每一个元组的第二个元素排列，对第2列升序 
    #step4:将step3排序后的数组的第1列（编号）逐一赋值给vector1,当vec1存的元素数量满足arr1_num（每组无人机需访问的目标数量）要求时，将vec1赋值给vector2
    vector1 = []
    vector2 = []
    #index=0
    for j in range(numUAV):
        cumm = 0
        for k in range(numTar):
            vector1.append(arr2_temp1[k][0])
            cumm = cumm + 1
            #index = index +1
            if cumm == arr1_num[j]:
                vector2.append(vector1)
                arr2_temp1 = arr2_temp1[cumm:]
                #if j != numUAV - 1:
                #    for vecd in range(cumm):
                #        arr2_temp1.pop(vecd)
                vector1 = []
                break
    print("vector2:",vector2)
    return vector2

#P1,P2为点的序号和坐标
def get_Dis(P1,P2):
    res = math.sqrt(math.pow(P1[1] - P2[1],2) + math.pow(P1[2] - P2[2],2))
    return res

#贪婪搜索聚类算法：pointUAV，pointTar的类型为[[num,精度,纬度],...]，arr2_coorUAV, arr2_coorTar是无人机，目标点的[[顺序，坐标经度，坐标纬度],[],[]...]
#返回结果是vec2_Tar:[[类1（numTar序号排列）],[类2],[类三],[类四]]
def get_Clustering_GreedySearch(numUAV, numTar, arr2_coorUAV, arr2_coorTar):
    #Step1：将坐标值赋值给列表
    pointUAV = []
    pointTar = []
    pointUAV = arr2_coorUAV[:]
    pointTar = arr2_coorTar[:]
    #Step2：确定离每个无人机最近的一个点，并分别将其添加到vec2_Tar的每行的第1个元素位置
    vec1_Tar = [[] for _ in range(numUAV)]
    vec2_Tar = [[] for _ in range(numUAV)]
    index1 = 0
    for pointU in pointUAV:
        code = [] #记录符合条件的point的数据
        tmp = 999999999999.99
        for pointT in pointTar:
            tmpDis = get_Dis(pointU,pointT)
            if tmpDis < tmp:
                tmp = tmpDis
                code = pointT
        vec1_Tar[index1].append(code)
        vec2_Tar[index1].append(code[0])
        pointTar.remove(code)
        index1 = index1 + 1
        #print("vec2_Tar-------------:",code)
    #Step3：将vec1_Tar中的其他元素也分别添加到vec2_Tar中
    for pointT in pointTar:
        for i in range(len(pointUAV)):
            P = vec1_Tar[i][-1]  #vec2_Tar的第i行的最新一个元素
            code = []  #记录符合条件的point的数据
            tmp = 999999999999.99
            for pointT1 in pointTar:
                tmpDis=get_Dis(P,pointT1);
                if tmpDis < tmp:
                    tmp = tmpDis
                    code = pointT1
            if len(pointTar) == 0:
                break
            vec2_Tar[i].append(code[0])
            pointTar.remove(code)
            
    return vec2_Tar

#目标聚类（距离优先聚类）算法：返回结果是vec2_Tar:[[类1（numTar顺序排列）],[类2],[类三],[类四]]
def get_Clustering_DistancePrior2(numUAV,numTar,arr2_coorUAV, arr2_coorTar):
    #Step1：将坐标值赋值给列表
    pointUAV = []
    pointTar = []
    pointUAV = arr2_coorUAV[:]
    pointTar = arr2_coorTar[:]
    #Step2：将vec1_Tar中的元素也分别添加到vec2_Tar中，按照顺序与无人机坐标比较距离，取最近点
    vec2_Tar = [[] for _ in range(numUAV)]
    for pointT in pointTar:
        for i in range(len(pointUAV)):
            P = pointUAV[i]  #vec2_Tar的第i行的最新一个元素
            code = []  #记录符合条件的point的数据
            tmp = 999999999999.99
            for pointT1 in pointTar:
                tmpDis=get_Dis(P,pointT1);
                if tmpDis < tmp:
                    tmp = tmpDis
                    code = pointT1
            if len(pointTar) == 0:
                break
            vec2_Tar[i].append(code[0])
            pointTar.remove(code)
    return vec2_Tar
    
#调用“区域路径随机生成”算子get_PathGeneration_Rand2：返回结果是vec2_Tar:[[类1（numTar随机顺序排列）],[类2],[类三],[类四]]
def get_PathGeneration_Rand2(vec2_group):
    #step1:将存放分组信息的vector转化为二维数组，便于调用排序算法进行随机排序
    #创建一个二维数组，用于存储目标编号的随机数（第1列是目标编号，第2列是随机数）
    vector1 = {}
    vector2 = []
    vec2_Tar = []
    for group in vec2_group:
        for i in group:
            vector1[i] = random.sample(range(0,len(group)),1)[0]
        #step2:将step4生成的数组按照第2列的随机数进行排序（升序或降序）
        vector1 = sorted(vector1.items(),key = lambda x:x[1],reverse = False)  # 按字典集合中，每一个元组的第二个元素排列，对第2列升序    
        #step3:将排序后的目标访问顺序赋值给vec2_Tar
        for vec in vector1:
            vector2.append(vec[0])
        vec2_Tar.append(vector2)
        vector1 = {}
        vector2 = []
    print("vec2_Tar:",vec2_Tar)
    return vec2_Tar

#调用“区域路径最近距离优先生成”算子get_PathGeneration_DistancePriorA&B
#返回结果是vector4:[[类1（numTar最近距离优先顺序排列）],[类2],[类三],[类四]]
def get_PathGeneration_DistancePriorA( numTar, arr2_coorTar, vec2_group):  
    #step1将vec2_group按照arr2_coorTar重新填充完整
    vector1 = []
    vector2 = []
    for group in vec2_group:
        for y in range(len(group)):
            for z in range(numTar):
                if(group[y] == arr2_coorTar[z][0]):
                    vector1.append(arr2_coorTar[z])
                    break
        vector2.append(vector1)
        vector1 = []
    return vector2

def get_PathGeneration_DistancePriorB(numTar, arr2_coorTar, vec2_group):
    vector2 = get_PathGeneration_DistancePriorA(numTar, arr2_coorTar, vec2_group)
    #step2遍历vector2，生成新的路径
    vector3 = []
    vector4 = []
    v1 = []
    v2 = []
    print("vector2dfsdfsdfs",vector2)
    for i in range(len(vector2)):
        v1.append(vector2[i][0])
        for vec2 in vector2[i][1:]:
            v2.append(vec2)
        print("v2000000:----------------------",v2)
        minDis = 9999999999999.999  #定义一个最短距离值
        tempCode = 0
        #遍历vector2中剩余的元素
        for j in range(len(v2)):
            print("v21111:----------------------",v2)
            for k in v2:
                tempDis = get_Dis(v1[-1],k)
                if(tempDis < minDis):
                    minDis = tempDis  #更新最短距离
                    tempCode = k  #确定最短距离对应的Point的点K
                    
            vector3.append(tempCode[0])
            print("tempCode:----------------------",tempCode)
            print("v2:----------------------",v2)
            v2.remove(tempCode)
            minDis = 9999999999999.999  #定义一个最短距离值
        vector4.append(vector3)
        vector3 = []
    return vector4

#计算路径长度,计算初始解
def get_RoutDistance2(len2,numTar, arr2_coorUAV, arr2_coorTar, vector):
    indexUAV = 1
    for vec in vector:
        for j in range(len(vec) - 1):
            len2 = get_Dis(vec[j],vec[j + 1])
        len1 = get_Dis(arr2_coorUAV[indexUAV - 1],vec[0])
        len3 = get_Dis(arr2_coorUAV[indexUAV - 1],vec[-1])
        sum_len = len1 + len2 + len3
        print("第" + str(indexUAV) + "架无人机飞行距离为：" + str(sum_len))
        indexUAV = indexUAV + 1

def ObjectFunction(numUAV, numTar, arr2_coorUAV, arr2_coorTar):
    #Step1:目标聚类
    x = random.sample(range(0,3),1)[0]
    if x == 2:  #调用“随机聚类”算子：get_Clustering_Rand2
        vec2_group = get_Clustering_Rand2(numUAV,numTar)
    elif x == 1:  #调用“距离优先聚类”算子：get_Clustering_DistancePrior
        vec2_group = get_Clustering_GreedySearch(numUAV,numTar,arr2_coorUAV,arr2_coorTar)
    else:  #调用“距离优先聚类”算子：get_Clustering_DistancePrior
        vec2_group = get_Clustering_DistancePrior2(numUAV,numTar,arr2_coorUAV,arr2_coorTar)
    #Step2:路径生成
    y = random.sample(range(0,2),1)[0]
    if y == 0:  #调用“区域路径随机生成”算子：get_PathGeneration_Rand2
        vec3_group = get_PathGeneration_Rand2(vec2_group)
    else:  #调用“区域路径最近距离优先生成”算子：get_PathGeneration_DistancePriorA&B
        vec3_group = get_PathGeneration_DistancePriorB(numTar,arr2_coorTar,vec2_group)
    #print("vec3_group:----------------------",vec3_group)
    vector = get_PathGeneration_DistancePriorA(numTar, arr2_coorTar, vec3_group)
    #plant_got写入algorithm_mission.waypoints
    for z in range(len(vector)):
        vector[z].insert(0,arr2_coorUAV[z])
    for j in range(numUAV):
        with open("algorithm_mission_Multi_UAV _Based_on_Adaptive_Large_Neighborhood_Heuristic_Search" + str(j) + ".waypoints",'w') as f1:
            f1.writelines(["QGC WPL 110\n"])
            a = 0
            for i in vector[j]:
                #plan_got = env.marcator(i[0],i[1],env.num)
                #if a == 0:
                #    f1.writelines([str(a) + '\t','0\t','0\t','16\t','0\t','0\t','0\t','0\t',str(arr2_coorUAV[j][1]) + '\t',str(arr2_coorUAV[j][2]) + '\t','10\t','1\n'])
                #else:
                f1.writelines([str(a) + '\t','0\t','3\t','16\t','0\t','0\t','0\t','0\t',str(i[1]) + '\t',str(i[2]) + '\t','10\t','1\n'])
                a = a + 1

    print("vector:",vector)
    #Step3:计算路径长度,计算初始解
    len2 = 0
    get_RoutDistance2(len2,numTar, arr2_coorUAV, arr2_coorTar, vector)
    #Step4:使用leaflet_folium绘图
    leaflet_folium_plot(vector)

def plot_maker(m,x_start,x_path,h):
    '''为m添加标记部件，并将部件上的图形设置为云朵'''
    folium.Marker(x_start,  #起点
                  popup='Mt. Hood Meadows',
                  icon=folium.Icon(icon='cloud'),).add_to(m)

    colorA = ['blue','red','black']
    for pathA in x_path:
        if  pathA != x_path[0]:
            '''为m添加标记部件'''
            folium.Marker(
                location=pathA,  #终点
                popup='Some Other Location',
                icon=folium.Icon(color='red', icon='info-sign')
            ).add_to(m)
        '''绘制任务路线'''
        mission = folium.PolyLine(locations = x_path,color=colorA[h])
        mission.add_to(m)

    #'''绘制算法路线'''
    #algorithm_mission = folium.PolyLine(locations = contentsA,color='red')  #红色为智能算法路线
    #algorithm_mission.add_to(m)

    '''为地图对象添加点击显示经纬度的子功能，实现点击地图任意位置获取经纬度信息提示'''
    m.add_child(folium.LatLngPopup())

    '''实现点击地图任意位置产生一个新的图标'''
    m.add_child(folium.ClickForMarker())
    m.save(os.path.join('results', 'CheckZorder.html'))
    
def leaflet_folium_plot(vector):
    '''创建Map对象'''
    m = folium.Map(location = list([vector[0][0][1],vector[0][0][2]]),
                  zoom_start = 16,
                  control_scale = True,
                  #width='50%',)
                  tiles='Stamen Terrain')
    h = 0
    for vec in vector:
        x_start = list([vec[0][1],vec[0][2]])  # Starting node
        x_path = []
        for pathA in vec:
            x_path.append([pathA[1],pathA[2]])  # path node
        print("x_path:",x_path)
        plot_maker(m,x_start,x_path,h)
        h += 1

def main():
    with open("../mission.waypoints",'r') as f:
        content = f.readlines()
    content.pop(0)
    arr2_cooruav = []
    for con in content:
        con = con.replace('\n','').split('\t')
        arr2_cooruav.append([int(con[0]) + 1,float(con[8]),float(con[9])])
    #s_start = env.marcatorxy(contents[0][0],contents[0][1],env.num)  # Starting node
    #s_goal = env.marcatorxy(contents[-1][0],contents[-1][1],env.num)  # Goal node

    with open("../fence.txt",'r') as f:
        content = f.readlines()
    arr2_coortar = []
    index = 0
    for con in content:
        con = con.replace('\n','').split('\t')
        #marxy = marcatorxy(float(con[0]),float(con[1]))
        arr2_coortar.append([index, float(con[0]), float(con[1])])  #marxy
        index = index + 1
    
    numUAV = len(arr2_cooruav)
    numTar = len(arr2_coortar)
    len2 = 0
    print(arr2_cooruav)
    print(arr2_coortar)
    print("start!!!")
    RRRR = ObjectFunction(numUAV,numTar,arr2_cooruav,arr2_coortar)

if __name__ == '__main__':
    main()

 
