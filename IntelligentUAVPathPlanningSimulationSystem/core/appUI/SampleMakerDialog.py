# -*- coding: utf-8 -*-

import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication, QFileDialog, QMessageBox
import numpy as np

from InitResource import get_icon
from SampleMakerDialogDesigner import Ui_SampleMakerDialog
from fileIO import ExcelIO
from data import SampleMaker
from chart.StatsChart import CoordinateAxis, BarChart, HistgramChart


class SampleMakerDialog(QDialog, Ui_SampleMakerDialog):
    '''
    '''
    #
    qSetting = None
    #
    training_cv_samples = None
    test_samples = None


    


if __name__ == "__main__":
    os.system("C:\cygwin64\home\Lenovo\ardupilot\Tools\autotest\fg_quad_view.bat")
    
