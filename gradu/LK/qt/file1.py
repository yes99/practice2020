import cv2
import threading
import sys
from PyQt5 import QtWidgets
from PyQt5 import QtGui
from PyQt5 import QtCore
from PyQt5 import uic
from PyQt5.QtWidgets import *

form_class=uic.loadUiType("MyEvent.ui")[0]

class MyWindow(QDialog, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("파일 오픈")
        self.pushButton.clicked.connect(self.fileopen)
        self.startButton.clicked.connect(self.start)

    def fileopen(self):
        global filename, FILE
        filename= QtWidgets.QFileDialog.getOpenFileName(self,'Open File')
        self.lineEdit.setText(filename[0])
        FILE = filename[0]
        print(FILE)

    def start(self):
        global FILE
        print(FILE)

if __name__=="__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()