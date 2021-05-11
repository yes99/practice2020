import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic

uiclass = uic.loadUiType("ffff.ui")[0]
print(type(uiclass))

# ui호출용 Class 생성
class TestWindow(QMainWindow, uiclass):
    def __init__(self):
        super().__init__()
        self.setupUi(self)



if __name__ == "__main__":
    app = QApplication(sys.argv)
    myApp = TestWindow()
    myApp.show()
    app.exec_()