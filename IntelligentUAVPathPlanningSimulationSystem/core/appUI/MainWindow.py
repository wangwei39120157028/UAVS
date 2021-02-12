# -*- coding:utf-8 -*-

import os
import sys
import time
from multiprocessing import Process
import subprocess
import ctypes

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog, QMessageBox, QTableWidgetItem

from MainWindowDesigner import Ui_MainWindow
from InitResource import get_icon, get_pixmap, get_gif
from AppSettingDialog import AppSettingDialog

STD_INPUT_HANDLE = -10
STD_OUTPUT_HANDLE = -11
STD_ERROR_HANDLE = -12

# 字体颜色定义 ,关键在于颜色编码，由2位十六进制组成，分别取0~f，前一位指的是背景色，后一位指的是字体色
#由于该函数的限制，应该是只有这16种，可以前景色与背景色组合。也可以几种颜色通过或运算组合，组合后还是在这16种颜色中

# Windows CMD命令行 字体颜色定义 text colors
FOREGROUND_BLACK = 0x00 # black.
FOREGROUND_DARKBLUE = 0x01 # dark blue.
FOREGROUND_DARKGREEN = 0x02 # dark green.
FOREGROUND_DARKSKYBLUE = 0x03 # dark skyblue.
FOREGROUND_DARKRED = 0x04 # dark red.
FOREGROUND_DARKPINK = 0x05 # dark pink.
FOREGROUND_DARKYELLOW = 0x06 # dark yellow.
FOREGROUND_DARKWHITE = 0x07 # dark white.
FOREGROUND_DARKGRAY = 0x08 # dark gray.
FOREGROUND_BLUE = 0x09 # blue.
FOREGROUND_GREEN = 0x0a # green.
FOREGROUND_SKYBLUE = 0x0b # skyblue.
FOREGROUND_RED = 0x0c # red.
FOREGROUND_PINK = 0x0d # pink.
FOREGROUND_YELLOW = 0x0e # yellow.
FOREGROUND_WHITE = 0x0f # white.


# Windows CMD命令行 背景颜色定义 background colors
BACKGROUND_BLUE = 0x10 # dark blue.
BACKGROUND_GREEN = 0x20 # dark green.
BACKGROUND_DARKSKYBLUE = 0x30 # dark skyblue.
BACKGROUND_DARKRED = 0x40 # dark red.
BACKGROUND_DARKPINK = 0x50 # dark pink.
BACKGROUND_DARKYELLOW = 0x60 # dark yellow.
BACKGROUND_DARKWHITE = 0x70 # dark white.
BACKGROUND_DARKGRAY = 0x80 # dark gray.
BACKGROUND_BLUE = 0x90 # blue.
BACKGROUND_GREEN = 0xa0 # green.
BACKGROUND_SKYBLUE = 0xb0 # skyblue.
BACKGROUND_RED = 0xc0 # red.
BACKGROUND_PINK = 0xd0 # pink.
BACKGROUND_YELLOW = 0xe0 # yellow.
BACKGROUND_WHITE = 0xf0 # white.



# get handle
std_out_handle = ctypes.windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)

def set_cmd_text_color(color, handle=std_out_handle):
    Bool = ctypes.windll.kernel32.SetConsoleTextAttribute(handle, color)
    return Bool

#reset white
def resetColor():
    set_cmd_text_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

###############################################################

#暗蓝色
#dark blue
def printDarkBlue(mess):
    set_cmd_text_color(FOREGROUND_DARKBLUE)
    sys.stdout.write(mess)
    resetColor()

#暗绿色
#dark green
def printDarkGreen(mess):
    set_cmd_text_color(FOREGROUND_DARKGREEN)
    sys.stdout.write(mess)
    resetColor()

#暗天蓝色
#dark sky blue
def printDarkSkyBlue(mess):
    set_cmd_text_color(FOREGROUND_DARKSKYBLUE)
    sys.stdout.write(mess)
    resetColor()

#暗红色
#dark red
def printDarkRed(mess):
    set_cmd_text_color(FOREGROUND_DARKRED)
    sys.stdout.write(mess)
    resetColor()

#暗粉红色
#dark pink
def printDarkPink(mess):
    set_cmd_text_color(FOREGROUND_DARKPINK)
    sys.stdout.write(mess)
    resetColor()

#暗黄色
#dark yellow
def printDarkYellow(mess):
    set_cmd_text_color(FOREGROUND_DARKYELLOW)
    sys.stdout.write(mess)
    resetColor()

#暗白色
#dark white
def printDarkWhite(mess):
    set_cmd_text_color(FOREGROUND_DARKWHITE)
    sys.stdout.write(mess)
    resetColor()

#暗灰色
#dark gray
def printDarkGray(mess):
    set_cmd_text_color(FOREGROUND_DARKGRAY)
    sys.stdout.write(mess)
    resetColor()

#蓝色
#blue
def printBlue(mess):
    set_cmd_text_color(FOREGROUND_BLUE)
    sys.stdout.write(mess)
    resetColor()

#绿色
#green
def printGreen(mess):
    set_cmd_text_color(FOREGROUND_GREEN)
    sys.stdout.write(mess)
    resetColor()

#天蓝色
#sky blue
def printSkyBlue(mess):
    set_cmd_text_color(FOREGROUND_SKYBLUE)
    sys.stdout.write(mess)
    resetColor()

#红色
#red
def printRed(mess):
    set_cmd_text_color(FOREGROUND_RED)
    sys.stdout.write(mess)
    resetColor()

#粉红色
#pink
def printPink(mess):
    set_cmd_text_color(FOREGROUND_PINK)
    sys.stdout.write(mess)
    resetColor()

#黄色
#yellow
def printYellow(mess):
    set_cmd_text_color(FOREGROUND_YELLOW)
    sys.stdout.write(mess)
    resetColor()

#白色
#white
def printWhite(mess):
    set_cmd_text_color(FOREGROUND_WHITE)
    sys.stdout.write(mess)
    resetColor()

##################################################

#白底黑字
#white bkground and black text
def printWhiteBlack(mess):
    set_cmd_text_color(FOREGROUND_BLACK | BACKGROUND_WHITE)
    sys.stdout.write(mess)
    resetColor()

#白底黑字
#white bkground and black text
def printWhiteBlack_2(mess):
    set_cmd_text_color(0xf0)
    sys.stdout.write(mess)
    resetColor()


#黄底蓝字
#white bkground and black text
def printYellowRed(mess):
    set_cmd_text_color(BACKGROUND_YELLOW | FOREGROUND_RED)
    sys.stdout.write(mess)
    resetColor()


##############################################################
global location
location = "KSFO"

class MainWindow(QMainWindow, Ui_MainWindow):  

    def __init__(self):
        super(MainWindow, self).__init__(None)
        self.setupUi(self)
        #
        self.init_app_config()
        self.init_window_ui()
        self.init_toolBar_ui()
        self.init_toolBox_ui()
        self.connect_signal_slot()
    
    def init_app_config(self):
        #
        self.setting_filename = os.path.dirname(os.path.dirname(__file__)) + \
                                                r"\resource\data\setting.ini"
        self.qSetting = QtCore.QSettings(self.setting_filename, QtCore.QSettings.IniFormat)
        #
        self.working_dir = str(self.qSetting.value("lastFileDir"))
        if self.working_dir is None or not os.path.isdir(self.working_dir):
            self.working_dir = os.path.expanduser('~')
            #
            self.qSetting.setValue("lastFileDir", self.working_dir)
        #
        self.sklearn_params_filepath = str(self.qSetting.value("sklearnParamsFilepath"))
        if self.sklearn_params_filepath is None or not os.path.isdir(self.sklearn_params_filepath):
            self.sklearn_params_filepath = os.path.dirname(os.path.dirname(__file__)) + \
                                                           r"\resource\data\sklearn_params.json"
            self.qSetting.setValue("sklearnParamsFilepath", self.sklearn_params_filepath)
        #
        self.curl_bin_dir = str(self.qSetting.value("curlBinDir"))
        if self.curl_bin_dir is None or not os.path.isdir(self.curl_bin_dir):
            self.curl_bin_dir = os.path.dirname(os.path.dirname(__file__)) + \
                                                r"\bin\curl-7.65.3-win64-mingw\bin"
            #
            self.qSetting.setValue("curlBinDir", self.curl_bin_dir)

    def init_window_ui(self):
        self.setWindowIcon(get_icon("s"))
        self.setWindowFlags(QtCore.Qt.WindowMinimizeButtonHint|QtCore.Qt.WindowCloseButtonHint)

    def init_toolBar_ui(self):
        self.mainToolBar = QtWidgets.QToolBar(self)
        self.mainToolBar.setMovable(False)
        self.mainToolBar.setToolButtonStyle(QtCore.Qt.ToolButtonTextUnderIcon)
        self.mainToolBar.setObjectName("mainToolBar")
        self.addToolBar(QtCore.Qt.TopToolBarArea, self.mainToolBar)
        # 
        self.appSettingToolBarAction = QtWidgets.QAction(get_icon("toolBarAppSetting"), "设置", self)
        self.mainToolBar.addAction(self.appSettingToolBarAction)
        self.mainToolBar.addSeparator()

        self.helpToolBarAction = QtWidgets.QAction(get_icon("toolBarHelp"), "帮助", self)
        self.mainToolBar.addAction(self.helpToolBarAction)

        self.feedbackToolBarAction = QtWidgets.QAction(get_icon("toolBarFeedback"), "反馈", self)
        self.mainToolBar.addAction(self.feedbackToolBarAction)

        self.aboutToolBarAction = QtWidgets.QAction(get_icon("toolBarAbout"), "关于", self)
        self.mainToolBar.addAction(self.aboutToolBarAction)

    def init_toolBox_ui(self):
        # 虚拟飞行
        self.toolBoxTreeWidget.topLevelItem(0).setIcon(0, get_icon("select_folder"))
        self.toolBoxTreeWidget.topLevelItem(0).child(0).setIcon(0, get_icon("1"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).setIcon(0, get_icon("select_folder"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(0).setIcon(0, get_icon("2"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(1).setIcon(0, get_icon("9"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(2).setIcon(0, get_icon("10"))        
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(3).setIcon(0, get_icon("3"))
        
        # 作战控制台
        self.toolBoxTreeWidget.topLevelItem(1).setIcon(0, get_icon("select_folder"))
        self.toolBoxTreeWidget.topLevelItem(1).child(0).setIcon(0, get_icon("Cygwin-Terminal"))
        self.toolBoxTreeWidget.topLevelItem(1).child(1).setIcon(0, get_icon("tableFile_FileListTreeWidget"))
        self.toolBoxTreeWidget.topLevelItem(1).child(2).setIcon(0, get_icon("dataViewToolBar"))
        #self.toolBoxTreeWidget.topLevelItem(1).child(3).setIcon(0, get_icon("toolBoxToolTreeWidget"))
        
        # 智能控制台
        self.toolBoxTreeWidget.topLevelItem(1).child(3).setIcon(0, get_icon("select_folder"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(0).setIcon(0, get_icon("Cygwin-Terminal"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(1).setIcon(0, get_icon("5"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(2).setIcon(0, get_icon("6"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(3).setIcon(0, get_icon("7"))
        
        # 地面站
        self.toolBoxTreeWidget.topLevelItem(2).setIcon(0, get_icon("select_folder"))
        self.toolBoxTreeWidget.topLevelItem(2).child(0).setIcon(0, get_icon("4"))
       
        
    def connect_signal_slot(self):
        self.appSettingToolBarAction.triggered.connect(self.appSettingToolBarActionTriggered)
        self.toolBoxTreeWidget.doubleClicked.connect(self.toolBoxTreeWidgetDoubleClicked)
    
    def appSettingToolBarActionTriggered(self):
        appSettingDialog = AppSettingDialog(self.qSetting)
        appSettingDialog.exec()

    def toolBoxTreeWidgetDoubleClicked(self):
        selectToolName = self.toolBoxTreeWidget.currentItem().text(0)
        global location
        
        if selectToolName == "启动FlightGear飞行模拟器":
            printSkyBlue(u'正在启动FlightGear飞行模拟器......\n')
            process1 = subprocess.Popen(["C:/cygwin64/home/Lenovo/ardupilot/Tools/autotest/fg_quad_view.bat"])
            #printSkyBlue(u'FlightGear飞行模拟器启动完成\n')
            #subprocess.call("start /wait C:/cygwin64/home/Lenovo/ardupilot/Tools/autotest/fg_quad_view.bat", shell=True)
            #son_p1=Process(target=run_FlightGear,args={})
            #son_p1.start()
            #son_p1.join()
        elif selectToolName == "测试位置：德国吕纳堡(EDHG)":
            location = "EDHG"
            printBlue(u'目标位置确定：' + location + '\n')
        elif selectToolName == "测试位置：布兰肯塞机场(EDHL)":
            location = "EDHL"
            printBlue(u'目标位置确定：' + location + '\n')
        elif selectToolName == "测试位置：佛罗里达(SCSE)":
            location = "SCSE"
            printBlue(u'目标位置确定：' + location + '\n')
        elif selectToolName == "自定义地理坐标":
            printBlue(u'因平台重新编译原因，请开启编程环境——作战平台并执行以下两段代码，注意替换实际的值：\n')
            printBlue(u'cd /home/Lenovo/ardupilot/ArduCopter\n')
            printBlue(u'../Tools/autotest/sim_vehicle.py --map -l ' + "目标纬度,目标经度,飞行高度,无人机朝向" + ' --console\n')
            
        elif selectToolName == "启动编程环境——作战平台": 
            printYellow(u'正在启动编程环境——作战平台......\n')
            os.system("mintty.exe -i /Cygwin-Terminal.ico -")
            printYellow(u'编程环境——作战平台启动完成\n')
            
        elif selectToolName == "仅加载Mavproxy控制台":
            printDarkGreen(u'因平台重新编译原因，请分别在编程环境——作战平台下执行以下两段代码：\n')
            printDarkGreen(u'cd /home/Lenovo/ardupilot/ArduCopter\n')
            printDarkGreen(u'../Tools/autotest/sim_vehicle.py  --console\n')

        elif selectToolName == "加载Mavproxy控制台与战场俯视图":
            printDarkSkyBlue(u'因平台重新编译原因，请分别在编程环境——作战平台下执行以下两段代码：\n')
            printDarkSkyBlue(u'cd /home/Lenovo/ardupilot/ArduCopter\n')
            printDarkSkyBlue(u'../Tools/autotest/sim_vehicle.py --map -L ' + location + ' --console\n')

        elif selectToolName == "启动编程环境——智能平台": 
            printYellow(u'正在启动编程环境——智能平台......\n')
            os.system("mintty.exe -i /Cygwin-Terminal.ico -")
            printYellow(u'编程环境——智能平台启动完成\n')
            
        elif selectToolName == "autoFly获取无人机信息":
            printDarkPink(u'因平台重新编译原因，请分别在编程环境——智能平台下执行以下两段代码：\n')
            printDarkPink(u'cd /home/Lenovo/ardupilot/ArduCopter/PyScripts\n')
            printDarkPink(u'python autoFly获取无人机信息.py\n')
    
        elif selectToolName == "autoFly前后左右升降俯仰":
            printDarkYellow(u'因平台重新编译原因，请分别在编程环境——智能平台下执行以下两段代码：\n')
            printDarkYellow(u'cd /home/Lenovo/ardupilot/ArduCopter/PyScripts\n')
            printDarkYellow(u'python autoFly前后左右升降俯仰.py\n')
            
        elif selectToolName == "autoFly连续飞行":
            printSkyBlue(u'因平台重新编译原因，请分别在编程环境——智能平台下执行以下两段代码：\n')
            printSkyBlue(u'cd /home/Lenovo/ardupilot/ArduCopter/PyScripts\n')
            printSkyBlue(u'python autoFly连续飞行.py\n')
            
        elif selectToolName == "启动地面站Mission Planner":
            printDarkRed(u'地面站Mission Planner启动......\n')
            son_p2=Process(target=run_MP,args={})
            son_p2.start()
            son_p2.join()
            printDarkRed(u'请在Mavproxy控制台输入代码并执行：\n')
            printDarkRed(u'output add 127.0.0.1:14550\n')
            printDarkRed(u'地面站Mission Planner启动完成\n')

        else:
            pass
           
    def closeEvent(self, QCloseEvent):
        qMsg = QMessageBox.question(self, "提示","退出仿真程序？")
        if qMsg == QMessageBox.Yes:
            QCloseEvent.accept()  
        else:
            QCloseEvent.ignore()

def run_MP():
    process2 = subprocess.Popen([subprocess.call("start start /B /wait MissionPlanner.exe", shell=True)])
    
def main():
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())



if __name__ == "__main__":
    #启动
    main()
