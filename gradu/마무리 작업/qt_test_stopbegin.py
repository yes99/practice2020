import cv2
import numpy as np
import os
import threading
import sys
from PyQt5 import QtWidgets
from PyQt5 import QtGui
from PyQt5 import QtCore
from PyQt5 import uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtGui import *


mode, drawing = True, False
# 마우스 눌렀을때 좌표
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1
global numOfDot
squares =0
stopbegin = 0
stopbegincnt = 0

form_class=uic.loadUiType("myEvent.ui")[0]

# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R, squares

    cv2.namedWindow('image')
    cv2.imshow('image', frame)

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        global xi, yi
        xi, yi = x, y

    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy = x, y
            # 사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)
            squares = squares +1
            print("네모 개수 %d" %squares)


def Optical_flow(frame,cnt):
    global xi, yi, x_copy, y_copy, numOfDot, stopbegin , stopbegincnt

    width = frame.shape[1]
    height = frame.shape[0]
    if cnt == 1:
        return frame

    # 여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)


    termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    #코너검출
    prePt = cv2.goodFeaturesToTrack(gray1,200,0.01,10)

    nextPt, status, err = cv2.calcOpticalFlowPyrLK(gray1, gray2, prePt, None, criteria=termcriteria)
    preMv=prePt[status==1]
    nextMv=nextPt[status==1]

    sumX=0
    count=0
    sumY=0

    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        px,py=p.ravel()
        nx,ny=n.ravel()
        if px > xi and px < x_copy and py > yi and py < y_copy:
            sumX=sumX+nx-px
            count=count+1
            sumY=sumY+ny-py

    moveX = round(sumX / count)
    moveY = round(sumY / count)
    print("특징점 개수",count)

    numOfCurrent=count


    xi = xi + moveX
    x_copy = x_copy + moveX
    yi = yi + moveY
    y_copy = y_copy + moveY

    if stopbegin == 1:
        stopbegincnt = stopbegincnt +1
        if(stopbegincnt ==10):
            stopbegin == 0
    else:
        if cnt > 11:
            diff=numOfCurrent-numOfDot
            # 현재특징점이 더 적을때->로고가 작아짐
            if x_copy - xi >= 20 and y_copy - yi >= 20:
                if diff < -6:
                    # round(diff/div+plus)
                    xi = xi + 2
                    yi = yi + 2

                    x_copy=x_copy-2
                    y_copy = y_copy - 2
                #현재특징점이 더 많을때->로고가 커짐
                elif diff > 6:
                    xi = xi - 2
                    yi = yi - 2

                    x_copy = x_copy + 2
                    y_copy = y_copy + 2

    if(cnt%10==0):
        numOfDot=count

    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)



    #inpainting
    #원본 중 부분을 잘라서 저장
    One_Bon= frame[int(yi):int(y_copy), int(xi):int(x_copy)]

    #자른 이미지 그레이스케일
    gray = cv2.cvtColor(One_Bon,cv2.COLOR_BGR2GRAY)

    #이진화
    E_Zin_Hwa = np.zeros_like(gray)
    E_Zin_Hwa[gray > 127] = 255
    cv2.imshow('binary', E_Zin_Hwa)

    #인페인팅 연산
    inPainted = cv2.inpaint(One_Bon, E_Zin_Hwa, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted', inPainted)

    blurImg = inPainted
    blurImg = cv2.blur(inPainted, (10, 10))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg

    return img2



class MyWindow(QDialog, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Optical Flow")
        self.openButton.clicked.connect(self.fileopen)
        self.saveButton.clicked.connect(self.filesave)
        self.startButton.clicked.connect(self.editStart)
        self.quitButton.clicked.connect(QCoreApplication.instance().quit)
    
    def fileopen(self):
        global video_file
        video_file= QtWidgets.QFileDialog.getOpenFileName(self,'Open File')
        self.openRoute.setText(video_file[0])
        if(self.openRoute.text() != ""):
            self.startButton.setEnabled(True)


    def filesave(self):
        FileSave = QFileDialog.getSaveFileName(self, 'Save File','./')
        self.saveRoute.setText(FileSave[0]+'.avi')
        global save_file
        save_file= FileSave[0]+'.avi'
        if(self.saveRoute.text() != ""):
            self.startButton.setEnabled(True)


    def editStart(self):
        global cnt ,stopbegin
        cnt=0
        quitflag = 0
        passflag = 0
        print(save_file)
        cap = cv2.VideoCapture(video_file[0])
        fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
        delay = int(1000 / fps)
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        out = cv2.VideoWriter(save_file, fourcc, 20.0, (640, 480))

        while cap.isOpened():  # 캡쳐 객체 초기화 확인
            ret, frame = cap.read()
            if not ret:
                break
            cnt = cnt + 1
            img_draw = frame.copy()

            print(cnt)
            # if cnt==1 or 2:
            #    cv2.imwrite('img'+str(cnt)+".jpg",frame)

            key = cv2.waitKey(delay)
            global squares
            if cnt == 1 or key ==32:
                cv2.namedWindow('image')
                cv2.imshow('image', frame)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                cv2.setMouseCallback('image', onMouse, param=frame)
                squares = 0
                while True:
                    k = cv2.waitKey(delay) & 0xFF
                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
                    if k == 27:
                        quitflag = 1
                        break
                    # 다시 영역지정
                    elif k == ord('r'):
                        
                        frame = img_draw.copy()
                        cv2.imshow('image', frame)
                        cv2.setMouseCallback('image', onMouse, param=frame)
                        squares = 0
                    elif  k == 32: #k == ord('p'):
                        passflag = 1
                        print("p누름 %d " %passflag)
                        cv2.destroyAllWindows()
                        stopbegin = 1
                        break
                    elif k == ord('s'):
                        cv2.destroyAllWindows()
                        stopbegin = 0
                        passflag = 0
                        # query 저장
                        global cutimg
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg = img_draw.copy()
                        cv2.imwrite('query.jpg', cutimg)
                        break
            elif key == 27:  # Esc:종료
                break
            print("while문 탈출")
            print("stopbegin", stopbegin)

            if quitflag ==1:    # 좀더 부드럽게 종료하도록 설정함
                break
            if  squares == 0:
                print("네모 없다")
                out.write(frame)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
            else:
                print("네모 있다")
                newframe = Optical_flow(frame, cnt)
                out.write(newframe)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                passflag = 0
 
            #if passflag == 1:
        cv2.destroyAllWindows()

        cap.release()

if __name__=="__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()