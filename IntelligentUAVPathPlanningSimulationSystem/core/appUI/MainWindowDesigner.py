# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\MainWindowDesigner.ui'
#
# Created by: PyQt5 UI code generator 5.12.3
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(402, 676)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setSpacing(5)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.toolBoxTreeWidget = QtWidgets.QTreeWidget(self.centralwidget)
        self.toolBoxTreeWidget.setHeaderHidden(True)
        self.toolBoxTreeWidget.setObjectName("toolBoxTreeWidget")
        self.toolBoxTreeWidget.headerItem().setText(0, "1")
        item_0 = QtWidgets.QTreeWidgetItem(self.toolBoxTreeWidget)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        
        item_0 = QtWidgets.QTreeWidgetItem(self.toolBoxTreeWidget)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        item_2 = QtWidgets.QTreeWidgetItem(item_1)
        
        item_0 = QtWidgets.QTreeWidgetItem(self.toolBoxTreeWidget)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)

        self.horizontalLayout.addWidget(self.toolBoxTreeWidget)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusBar = QtWidgets.QStatusBar(MainWindow)
        self.statusBar.setObjectName("statusBar")
        MainWindow.setStatusBar(self.statusBar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "智能无人机路径规划仿真系统 V1.0.0"))
        __sortingEnabled = self.toolBoxTreeWidget.isSortingEnabled()
        self.toolBoxTreeWidget.setSortingEnabled(False)
        self.toolBoxTreeWidget.topLevelItem(0).setText(0, _translate("MainWindow", "虚拟飞行"))
        self.toolBoxTreeWidget.topLevelItem(0).child(0).setText(0, _translate("MainWindow", "启动FlightGear飞行模拟器"))
        
        self.toolBoxTreeWidget.topLevelItem(0).child(1).setText(0, _translate("MainWindow", "选择作战地图"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(0).setText(0, _translate("MainWindow", "测试位置：德国吕纳堡(EDHG)"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(1).setText(0, _translate("MainWindow", "测试位置：布兰肯塞机场(EDHL)"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(2).setText(0, _translate("MainWindow", "测试位置：佛罗里达(SCSE)"))
        self.toolBoxTreeWidget.topLevelItem(0).child(1).child(3).setText(0, _translate("MainWindow", "自定义地理坐标"))
        
        self.toolBoxTreeWidget.topLevelItem(1).setText(0, _translate("MainWindow", "作战控制台"))
        self.toolBoxTreeWidget.topLevelItem(1).child(0).setText(0, _translate("MainWindow", "启动编程环境——作战平台"))
        self.toolBoxTreeWidget.topLevelItem(1).child(1).setText(0, _translate("MainWindow", "仅加载Mavproxy控制台"))
        self.toolBoxTreeWidget.topLevelItem(1).child(2).setText(0, _translate("MainWindow", "加载Mavproxy控制台与战场俯视图"))
        
        self.toolBoxTreeWidget.topLevelItem(1).child(3).setText(0, _translate("MainWindow", "智能控制"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(0).setText(0, _translate("MainWindow", "启动编程环境——智能平台"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(1).setText(0, _translate("MainWindow", "autoFly获取无人机信息"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(2).setText(0, _translate("MainWindow", "autoFly前后左右升降俯仰"))
        self.toolBoxTreeWidget.topLevelItem(1).child(3).child(3).setText(0, _translate("MainWindow", "autoFly连续飞行"))
                
        self.toolBoxTreeWidget.topLevelItem(2).setText(0, _translate("MainWindow", "地面站"))
        self.toolBoxTreeWidget.topLevelItem(2).child(0).setText(0, _translate("MainWindow", "启动地面站Mission Planner"))

        self.toolBoxTreeWidget.setSortingEnabled(__sortingEnabled)
