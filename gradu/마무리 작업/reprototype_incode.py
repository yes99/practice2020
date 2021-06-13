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
x_down1, y_down1, x_down2, y_down2 = -1, -1, -1, -1
x_up1, y_up1, x_up2, y_up2 = -1, -1, -1, -1

# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
global numOfDot1, numOfDot2

squares = 0

zeroflag = 0
cornerflag = 0



form_class = uic.loadUiType("myEvent.ui")[0]


def Optical_flow(frame):
    global x_down1, y_down1, x_up1, y_up1, numOfDot

    width = frame.shape[1]
    height = frame.shape[0]

    print("좌표", x_down1,y_down1,x_up1,y_up1)
    if cnt == 1 or x_down1==-1:
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
        if px > x_down1 and px < x_up1 and py > y_down1 and py < y_up1:
            sumX=sumX+nx-px
            count=count+1
            sumY=sumY+ny-py

    moveX = round(sumX / count)
    moveY = round(sumY / count)
    #print("특징점 개수",count)

    numOfCurrent=count


    x_down1 = x_down1 + moveX
    x_up1 = x_up1 + moveX
    y_down1 = y_down1 + moveY
    y_up1 = y_up1 + moveY


    if cnt > 11:
        diff=numOfCurrent-numOfDot
        print(diff)
        # 현재특징점이 더 적을때->로고가 작아짐
        if x_up1 - x_down1 >= 20 and y_up1 - y_down1 >= 20:
            if diff < -6:
                # round(diff/div+plus)
                x_down1 = x_down1 + 2
                y_down1 = y_down1 + 2

                x_up1=x_up1-2
                y_up1 = y_up1 - 2
            #현재특징점이 더 많을때->로고가 커짐
            elif diff > 6:
                x_down1 = x_down1 - 2
                y_down1 = y_down1 - 2

                x_up1 = x_up1 + 2
                y_up1 = y_up1 + 2

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
    original= frame[int(y_down1):int(y_up1), int(x_down1):int(x_up1)]

    #자른 이미지 그레이스케일
    gray = cv2.cvtColor(original,cv2.COLOR_BGR2GRAY)

    #이진화
    binarization = np.zeros_like(gray)
    binarization[gray > 127] = 255
    #cv2.imshow('binary', binarization)

    #인페인팅 연산
    inPainted = cv2.inpaint(original, binarization, 10, cv2.INPAINT_TELEA)
    #cv2.imshow('inPainted', inPainted)

    blurImg = inPainted
    blurImg = cv2.blur(inPainted, (10, 10))
    img2[int(y_down1):int(y_up1), int(x_down1):int(x_up1)] = blurImg

    return img2


# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global x_down1, y_down1, drawing, mode, B, G, R

    print("마우스 이벤트 시작")
    cv2.namedWindow('image')
    cv2.imshow('image', frame)

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        global x_down1, y_down1
        x_down1, y_down1 = x, y

    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        if mode:
            global x_up1, y_up1
            x_up1, y_up1 = x, y
            # 사각형그리기
            cv2.rectangle(frame, (x_down1, y_down1), (x_up1, y_up1), (0, 225, 0), 3)

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
        video_file = QtWidgets.QFileDialog.getOpenFileName(self, 'Open File')
        self.openRoute.setText(video_file[0])
        if (self.openRoute.text() != ""):
            self.startButton.setEnabled(True)

    def filesave(self):
        FileSave = QFileDialog.getSaveFileName(self, 'Save File', './')
        self.saveRoute.setText(FileSave[0] + '.avi')
        global save_file
        save_file = FileSave[0] + '.avi'
        if (self.saveRoute.text() != ""):
            self.startButton.setEnabled(True)

    #main 함수 시작
    def editStart(self):
        global cnt, countM, squares, cornerflag
        global x_down1,y_down1,x_up1,y_up1
        x_down1, y_down1, x_up1, y_up=-1,-1,-1,-1

        countM = 0

        cnt = 0
        quitflag = 0

        print(save_file)

        cap = cv2.VideoCapture(video_file[0])
        width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        print(width, height)
        fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
        delay = int(1000 / fps)

        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        out = cv2.VideoWriter(save_file, fourcc, 20.0, (width, height))
        origincnt = 0
        convertcnt = 0

        while cap.isOpened():  # 캡쳐 객체 초기화 확인

            ret, frame = cap.read()
            if not ret:
                break
            cnt = cnt + 1
            img_draw = frame.copy()

            print('cnt',cnt)
            originframe = "origin%d.png" % origincnt
            cv2.imwrite('./origin/'+originframe, frame)
            origincnt += 1
            key = cv2.waitKey(delay)

            if key == 32 or cnt == 1:
                cv2.namedWindow('image')
                cv2.imshow('image', frame)


                x_down1, y_down1, x_up1, y_up = -1, -1, -1, -1

                cv2.setMouseCallback('image', onMouse, param=frame)
                while True:
                    k = cv2.waitKey(delay) & 0xFF
                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
                    if k == 27:
                        break
                    # 다시 영역지정
                    elif k == ord('r'):
                        x_down1, y_down1, x_up1, y_up = -1, -1, -1, -1

                        frame = img_draw.copy()
                        cv2.destroyAllWindows()
                        cv2.imshow('image', frame)
                        cv2.setMouseCallback('image', onMouse, param=frame)
                    elif k == ord('s'):
                        cv2.destroyAllWindows()
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
            newframe =Optical_flow(frame)
            cv2.imshow('result', newframe)
            convertframe = "convert%d.png" % convertcnt
            cv2.imwrite('./convert/'+convertframe, newframe)
            convertcnt += 1
        cv2.destroyAllWindows()

        cap.release()


if __name__ == "__main__":
    x_down1, y_down1, x_up1, y_up = -1, -1, -1, -1
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()