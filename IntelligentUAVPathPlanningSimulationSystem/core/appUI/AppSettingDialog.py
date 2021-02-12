# -*- coding:utf-8 -*-

import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import numpy as np
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QMessageBox, QTableWidgetItem
#from fileIO import ExcelIO, RasterImgIO, ModelIO
#from data.DataPreprocessor import min_max_scaler, standard_scaler
#from raster.BandCalculator import band_calc
from AppSettingDialogDesigner import Ui_AppSettingDialog
from InitResource import get_icon


class AppSettingDialog(QDialog, Ui_AppSettingDialog):

    def __init__(self, setting):
        super(AppSettingDialog, self).__init__(None)
        self.setupUi(self)
        #
        self.qSetting = setting
        self.working_dir = None
        #
        self.init_ui_element()
        #
        #========singal and slot========
        self.connect_signal_slot()

    def init_ui_element(self):
        #
        self.setWindowIcon(get_icon("setting"))
        #
        self.selectWorkingDirPushButton.setIcon(get_icon("select_folder"))
        #
        working_dir = self.qSetting.value("lastFileDir")
        if working_dir is None or not os.path.isdir(working_dir):
            working_dir = os.path.expanduser('~')
        #
        sklearn_params_filepath = self.qSetting.value("sklearnParamsFilepath")
        curl_bin_dir = self.qSetting.value("curlBinDir")
        mySQLHost = self.qSetting.value("mySQLHost")
        mySQLPort = self.qSetting.value("mySQLPort")
        geoserverHost = self.qSetting.value("geoserverHost")
        geoserverPort = self.qSetting.value("geoserverPort")
        #
        self.selectWorkingDirLineEdit.setText(working_dir)
        self.paramsFileDirLineEdit.setText(sklearn_params_filepath)
        self.cURLBinDirLineEdit.setText(curl_bin_dir)
        self.mySQLHostLineEdit.setText(mySQLHost)
        self.mySQLPortLineEdit.setText(mySQLPort)
        self.geoserverHostLineEdit.setText(geoserverHost)
        self.geoserverPortLineEdit.setText(geoserverPort)

    def connect_signal_slot( self ):
        self.appSettingTreeWidget.clicked.connect(self.appSettingTreeWidgetClicked)
        self.selectWorkingDirPushButton.clicked.connect(self.selectWorkingDirPushButtonClicked)
        #
        self.okPushButton.clicked.connect(self.okPushButtonClicked)
        self.cancelPushButton.clicked.connect(self.cancelPushButtonClicked)

    def appSettingTreeWidgetClicked(self):
        selectItemName = self.appSettingTreeWidget.currentItem().text(0)
        #
        if selectItemName == "工作空间":
            self.appSettingStackedWidget.setCurrentIndex(0)
        elif selectItemName == "ML模型库":
            self.appSettingStackedWidget.setCurrentIndex(1)
        elif selectItemName == "cURL程序":
            self.appSettingStackedWidget.setCurrentIndex(2)
        elif selectItemName == "MySQL数据库":
            self.appSettingStackedWidget.setCurrentIndex(3)
        elif selectItemName == "GeoServer":
            self.appSettingStackedWidget.setCurrentIndex(4)
        else:
            pass

    def selectWorkingDirPushButtonClicked(self):
        lastFileDir = str(self.qSetting.value("lastFileDir"))
        if not os.path.isdir(lastFileDir):
            lastFileDir = os.path.expanduser('~')
        #
        self.working_dir =  QFileDialog.getExistingDirectory(self, "选择一个当前工作路径", lastFileDir)
        if self.working_dir != "":
            self.selectWorkingDirLineEdit.setText(self.working_dir)

    def okPushButtonClicked(self):
        self.mySQLHost = self.mySQLHostLineEdit.text()
        self.mySQLPort = self.mySQLPortLineEdit.text()
        self.geoserverHost = self.geoserverHostLineEdit.text()
        self.geoserverPort = self.geoserverPortLineEdit.text()
        #
        if self.working_dir != "" and self.working_dir is not None:
            self.qSetting.setValue("lastFileDir", self.working_dir)
        #
        if self.mySQLHost != "" and self.mySQLHost is not None:
            self.qSetting.setValue("mySQLHost", self.mySQLHost)
        #
        if self.mySQLPort != "" and self.mySQLPort is not None:
            self.qSetting.setValue("mySQLPort", self.mySQLPort)
        #
        if self.geoserverHost != "" and self.geoserverHost is not None:
            self.qSetting.setValue("geoserverHost", self.geoserverHost)   
        #
        if self.geoserverPort != "" and self.geoserverPort is not None:
            self.qSetting.setValue("geoserverPort", self.geoserverPort)
        #
        self.close()

    def cancelPushButtonClicked(self):
        #
        self.close()


def main(setting):
    app = QApplication(sys.argv)
    appSettingDialog = AppSettingDialog(setting)
    appSettingDialog.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    #
    setting_filename = "Setting.ini"
    qSetting = QtCore.QSettings(setting_filename, QtCore.QSettings.IniFormat)
    #
    main(qSetting)



