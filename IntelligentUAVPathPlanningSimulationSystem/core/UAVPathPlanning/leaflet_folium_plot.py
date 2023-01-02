#!usr/bin/env python
#encoding:utf-8
from __future__ import division
 
import os
import json
import folium
import pandas as pd
from folium import plugins
 
 
#url = 'https://raw.githubusercontent.com/python-visualization/folium/master/examples/data'
#try:
#    state_geo = 'https://raw.githubusercontent.com/python-visualization/folium/master/examples/data/us-states.json'
#    state_unemployment = 'https://raw.githubusercontent.com/python-visualization/folium/master/examples/data/US_Unemployment_Oct2012.csv'
#except:
#    state_geo='us-states.json'
#    state_unemployment='US_Unemployment_Oct2012.csv'
#
#state_data = pd.read_csv(state_unemployment)
with open("mission.waypoints",'r') as f:
    content = f.readlines()
content.pop(0)
contents = []
for con in content:
    con = con.replace('\n','').split('\t')
    contents.append([float(con[8]),float(con[9])])
x_start = contents[0]  # Starting node
x_goal = contents[-1]  # Goal node

with open("fence.txt",'r') as f1:
    content = f1.readlines()
obs_rectangle = []
for con in content:
    con = con.replace('\n','').split('\t')
    marxy = [float(con[0]),float(con[1])]
    obs_rectangle.append(marxy)
    
with open("Search_based_Planning/algorithm_mission_Search2D/algorithm_mission_Bidirectional_RTAAStar.waypoints",'r') as f2:
    contentA = f2.readlines()
contentA.pop(0)
contentsA = []
for conA in contentA:
    conA = conA.replace('\n','').split('\t')
    contentsA.append([float(conA[8]),float(conA[9])])
            
'''创建Map对象'''
m = folium.Map(location=x_start,
              zoom_start=16,
              control_scale=True,
              #width='50%',)
              tiles='Stamen Terrain')

#folium.Choropleth(state_geo,data=state_data,columns=['State', 'Unemployment'],
#                  key_on='feature.id',fill_color='YlGn',fill_opacity=0.7,
#                  line_opacity=0.2,legend_name='Unemployment Rate (%)').add_to(m)
#popup = 'Must be on top of the choropleth'
#folium.CircleMarker(location=[48, -102],radius=10,fill=True,popup=popup,
#                    weight=1,).add_to(m)


              
'''为m添加标记部件，并将部件上的图形设置为云朵'''
folium.Marker(x_start,  #起点
              popup='Mt. Hood Meadows',
              icon=folium.Icon(icon='cloud'),).add_to(m)
              #icon=folium.Icon(color='green')
              #icon=folium.Icon(color='red', icon='info-sign')

'''为m添加标记部件'''
folium.Marker(
    location=x_goal,  #终点
    popup='Some Other Location',
    icon=folium.Icon(color='red', icon='info-sign')
).add_to(m)
              
#'''为m添加标记部件,如圆圈，填充'''
#folium.Circle(
#            radius=100,
#            location=[37.626639,-122.384176],
#            popup='The Waterfront',
#            color='crimson',  #'#3388ff'
#            fill=False,  #True
#            #fill_color='#FF66CC'
#            ).add_to(m)

'''创建障碍物'''
fence = folium.PolyLine(locations=obs_rectangle,color='black',fill=True,closed=True,alpha=0.2)  #黑色线为障碍物
fence.add_to(m)

'''绘制任务路线'''
mission = folium.PolyLine(locations=contents,color='blue')  #蓝色线为自己大致所定路线
mission.add_to(m)

'''绘制算法路线'''
algorithm_mission = folium.PolyLine(locations=contentsA,color='red')  #红色为智能算法路线
algorithm_mission.add_to(m)

'''为地图对象添加点击显示经纬度的子功能，实现点击地图任意位置获取经纬度信息提示'''
m.add_child(folium.LatLngPopup())

'''实现点击地图任意位置产生一个新的图标'''
m.add_child(folium.ClickForMarker())

m.save(os.path.join('results', 'CheckZorder.html'))