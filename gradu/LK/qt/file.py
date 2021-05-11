from PyQt5 import QtWidgets
import sys
from PyQt5 import uic
from PyQt5.QtWidgets import *

form_class=uic.loadUiType("fff.ui")[0]

class MyWindow(QDialog, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("파일 오픈")
        self.pushButton.clicked.connect(self.fileopen)

    def fileopen(self):
        global filename
        filename= QtWidgets.QFileDialog.getOpenFileName(self,'Open File')

if __name__=="__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()