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


# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global x_down1, y_down1, x_down2, y_down2, drawing, mode, B, G, R, squares, countM

    cv2.namedWindow('image')
    cv2.imshow('image', frame)

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        countM = countM + 1
        drawing = True
        if countM == 1:
            global x_down1, y_down1
            x_down1, y_down1 = x, y
            print(countM)
        elif countM == 3:
            global x_down2, y_down2
            x_down2, y_down2 = x, y
            print(countM)

    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        countM = countM + 1
        drawing = False
        if mode:
            if countM == 2:
                global x_up1, y_up1
                x_up1, y_up1 = x, y
                # 사각형그리기
                cv2.rectangle(frame, (x_down1, y_down1), (x_up1, y_up1), (0, 225, 0), 3)
                count = countM + 1
                squares = squares + 1
                print(x_down1, y_down1, x_up1, y_up1)
                print(countM, squares)

            elif countM == 4:
                global x_up2, y_up2
                x_up2, y_up2 = x, y
                # 사각형그리기
                cv2.rectangle(frame, (x_down2, y_down2), (x_up2, y_up2), (0, 225, 0), 3)
                squares = squares + 1
                print(x_down2, y_down2, x_up2, y_up2)
                print(countM, squares)

            else:
                print(countM)
                return


# 네모 한개
def Optical_flow(frame, cnt):
    global x_down1, y_down1, x_up1, y_up1, numOfDot1, stopbegin, stopbegincnt, cornerflag

    width = frame.shape[1]
    height = frame.shape[0]
    if cnt == 1:
        return frame

    # 여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    termcriteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    # 코너검출
    prePt = cv2.goodFeaturesToTrack(gray1, 200, 0.01, 10)

    nextPt, status, err = cv2.calcOpticalFlowPyrLK(gray1, gray2, prePt, None, criteria=termcriteria)
    preMv = prePt[status == 1]
    nextMv = nextPt[status == 1]

    sumX = 0
    count = 0
    sumY = 0

    for i, (p, n) in enumerate(zip(preMv, nextMv)):
        px, py = p.ravel()
        nx, ny = n.ravel()
        if px > x_down1 and px < x_up1 and py > y_down1 and py < y_up1:
            sumX = sumX + nx - px
            count = count + 1
            sumY = sumY + ny - py

    if count == 0:
        cornerflag = 1
        print("corner is zero 1")
        return frame


    moveX = round(sumX / count)
    moveY = round(sumY / count)
    print("특징점 개수", count)

    numOfCurrent = count

    x_down1 = x_down1 + moveX
    x_up1 = x_up1 + moveX
    y_down1 = y_down1 + moveY
    y_up1 = y_up1 + moveY



    if cnt > 11:
        diff = numOfCurrent - numOfDot1
        # 현재특징점이 더 적을때->로고가 작아짐
        if x_up1 - x_down1 >= 20 and y_up1 - y_down1 >= 20:
            if diff < -6:
                # round(diff/div+plus)
                x_down1 = x_down1 + 2
                y_down1 = y_down1 + 2

                x_up1 = x_up1 - 2
                y_up1 = y_up1 - 2
            # 현재특징점이 더 많을때->로고가 커짐
            elif diff > 6:
                x_down1 = x_down1 - 2
                y_down1 = y_down1 - 2

                x_up1 = x_up1 + 2
                y_up1 = y_up1 + 2

    if (cnt % 10 == 0):
        numOfDot1 = count

    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)

    # inpainting
    # 원본 중 부분을 잘라서 저장
    original = frame[int(y_down1):int(y_up1), int(x_down1):int(x_up1)]

    # 자른 이미지 그레이스케일
    gray = cv2.cvtColor(original, cv2.COLOR_BGR2GRAY)

    # 이진화
    binary = np.zeros_like(gray)
    binary[gray > 127] = 255
    cv2.imshow('binary', binary)

    # 인페인팅 연산
    inPainted = cv2.inpaint(original, binary, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted', inPainted)

    blurImg = inPainted
    blurImg = cv2.blur(inPainted, (10, 10))
    img2[int(y_down1):int(y_up1), int(x_down1):int(x_up1)] = blurImg

    return img2


# 네모 두개
def Optical_flow2(frame, cnt):
    global x_down1, y_down1, x_up1, y_up1, x_down2, y_down2, x_up2, y_up2, numOfDot1, numOfDot2, stopbegin, stopbegincnt, cornerflag
    width = frame.shape[1]
    height = frame.shape[0]

    X1 = x_down1
    Y1 = y_down1
    X1_copy = x_up1
    Y1_copy = y_up1
    X2 = x_down2
    Y2 = y_down2
    X2_copy = x_up2
    Y2_copy = y_up2

    if cnt == 1:
        return frame

    # 여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query2.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    termcriteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    # 코너검출
    prePt = cv2.goodFeaturesToTrack(gray1, 200, 0.01, 10)

    nextPt, status, err = cv2.calcOpticalFlowPyrLK(gray1, gray2, prePt, None, criteria=termcriteria)
    preMv = prePt[status == 1]
    nextMv = nextPt[status == 1]

    sumX1 = 0
    count1 = 0
    sumY1 = 0

    for i, (p, n) in enumerate(zip(preMv, nextMv)):
        px, py = p.ravel()
        nx, ny = n.ravel()
        if px > X1 and px < X1_copy and py > Y1 and py < Y1_copy:
            sumX1 = sumX1 + nx - px
            count1 = count1 + 1
            sumY1 = sumY1 + ny - py
    if count1 == 0:
        cornerflag = 1
        print("corner is zero     2-1")
        return frame
    moveX1 = round(sumX1 / count1)
    moveY1 = round(sumY1 / count1)
    # print("특징점 개수1",count1)

    numOfCurrent1 = count1

    sumX2 = 0
    count2 = 0
    sumY2 = 0
    for i, (p, n) in enumerate(zip(preMv, nextMv)):
        px, py = p.ravel()
        nx, ny = n.ravel()
        if px > X2 and px < X2_copy and py > Y2 and py < Y2_copy:
            sumX2 = sumX2 + nx - px
            count2 = count2 + 1
            sumY2 = sumY2 + ny - py
    if count2 == 0:
        cornerflag = 1
        print("corner is zero     2-2")
        return frame
    moveX2 = round(sumX2 / count2)
    moveY2 = round(sumY2 / count2)
    # print("특징점 개수2", count2)

    numOfCurrent2 = count2

    X1 = X1 + moveX1
    X1_copy = X1_copy + moveX1
    Y1 = Y1 + moveY1
    Y1_copy = Y1_copy + moveY1
    X2 = X2 + moveX2
    X2_copy = X2_copy + moveX2
    Y2 = Y2 + moveY2
    Y2_copy = Y2_copy + moveY2



    if cnt > 11:
        diff1 = numOfCurrent1 - numOfDot1
        diff2 = numOfCurrent2 - numOfDot2
        # 현재특징점이 더 적을때->로고가 작아짐
        if X1_copy - X1 >= 20 and Y1_copy - Y1 >= 20:
            if diff1 < -6:
                # round(diff/div+plus)
                X1 = X1 + 2
                Y1 = Y1 + 2

                X1_copy = X1_copy - 2
                Y1_copy = Y1_copy - 2
            # 현재특징점이 더 많을때->로고가 커짐
            elif diff1 > 6:
                X1 = X1 - 2
                Y1 = Y1 - 2
                X1_copy = X1_copy + 2
                Y1_copy = Y1_copy + 2

        if X2_copy - X2 >= 20 and Y2_copy - Y2 >= 20:
            if diff1 < -6:
                # round(diff/div+plus)
                X2 = X2 + 2
                Y2 = Y2 + 2

                X2_copy = X2_copy - 2
                Y2_copy = Y2_copy - 2
            # 현재특징점이 더 많을때->로고가 커짐
            elif diff1 > 6:
                X2 = X2 - 2
                Y2 = Y2 - 2
                X2_copy = X2_copy + 2
                Y2_copy = Y2_copy + 2

    x_down1 = X1
    xi_copy = X1_copy
    y_down1 = Y1
    yi_copy = Y1_copy
    x_down2 = X2
    x_up2 = X2_copy
    y_down2 = Y2
    y_up2 = Y2_copy

    if (cnt % 10 == 0):
        numOfDot1 = count1
        numOfDot2 = count2

    try:
        os.remove("query2.jpg")
    except:
        pass
    cutimg2 = frame.copy()
    cv2.imwrite('query2.jpg', cutimg2)

    # inpainting
    # 원본 중 부분을 잘라서 저장
    One_Bon1 = frame[int(y_down1):int(y_up1), int(x_down1):int(x_up1)]
    One_Bon2 = frame[int(y_down2):int(y_up2), int(x_down2):int(x_up2)]
    # 자른 이미지 그레이스케일
    gray1 = cv2.cvtColor(One_Bon1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(One_Bon2, cv2.COLOR_BGR2GRAY)
    # 이진화
    binary1 = np.zeros_like(gray1)
    binary1[gray1 > 127] = 255
    cv2.imshow('binary1', binary1)
    binary2 = np.zeros_like(gray2)
    binary2[gray2 > 127] = 255
    cv2.imshow('binary2', binary2)
    # 인페인팅 연산
    inPainted1 = cv2.inpaint(One_Bon1, binary1, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted1', inPainted1)
    inPainted2 = cv2.inpaint(One_Bon2, binary2, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted2', inPainted2)
    blurImg1 = inPainted1
    blurImg1 = cv2.blur(inPainted1, (10, 10))
    blurImg2 = inPainted2
    blurImg2 = cv2.blur(inPainted2, (10, 10))
    img2[int(y_down1):int(y_up1), int(x_down1):int(x_up1)] = blurImg1
    img2[int(y_down2):int(y_up2), int(x_down2):int(x_up2)] = blurImg2
    cv2.imshow('monitor', img2)

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
        global cnt, stopbegin, countM, squares, cornerflag
        countM = 0
        cnt = 0
        quitflag = 0
        passflag = 0
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

        while cap.isOpened():  # 캡쳐 객체 초기화 확인

            ret, frame = cap.read()
            if not ret:
                break
            cnt = cnt + 1
            img_draw = frame.copy()
            print(cnt)
            originframe = "origin%d.png" % origincnt
            # print(originframe)
            # print('./origin/'+originframe)
            # cv2.imwrite('./origin/'+originframe, frame)
            origincnt += 1
            key = cv2.waitKey(delay)
            if cnt == 1 or key == 32 or cornerflag == 1:
                print("지금 어디에요? while 전에 멈춤", cnt)
                cornerflag = 0
                countM = 0
                squares = 0
                cv2.namedWindow('image')
                cv2.imshow('image', frame)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                cv2.setMouseCallback('image', onMouse, param=frame)
                print("1 squares : ", squares)

                while True:
                    k = cv2.waitKey(delay) & 0xFF
                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
                    if k == 27:
                        quitflag = 1
                        break
                    # 다시 영역지정
                    elif k == ord('r'):
                        frame = img_draw.copy()
                        cv2.destroyAllWindows()
                        cv2.imshow('image', frame)
                        countM = 0
                        squares = 0
                        cv2.setMouseCallback('image', onMouse, param=frame)
                        print("2 squares : ", squares)
                    elif k == 32:
                        passflag = 1
                        print("지금 어디에요? 아래서", cnt)
                        print("p누름 %d " % passflag)
                        stopbegin = 1
                        break
                    elif k == ord('s'):
                        cv2.destroyAllWindows()
                        stopbegin = 0
                        passflag = 0
                        # query 저장
                        global cutimg
                        global cutimg2
                        if squares == 1:
                            try:
                                os.remove("query.jpg")
                            except:
                                pass
                            cutimg = img_draw.copy()
                            cv2.imwrite('query.jpg', cutimg)
                        elif squares == 2:
                            try:
                                os.remove("query.jpg")
                            except:
                                pass
                            cutimg = img_draw.copy()
                            try:
                                os.remove("query2.jpg")
                            except:
                                pass
                            cv2.imwrite('query.jpg', cutimg)
                            cv2.imwrite('query2.jpg', cutimg)
                        countM = 0
                        print("3 squares : ", squares)
                        break
            elif key == ord('a'):
                hold = origincnt
                back = hold - 5
                print("되감기 테스트", hold, back, "########################################")
                # while back > hold:   #오리진 프레임에서 어느정도 빼줌



            elif key == 27:  # Esc:종료
                break
            print("while문 탈출")
            print("stopbegin", stopbegin)

            print("squares : ", squares)
            if quitflag == 1:  # 좀더 부드럽게 종료하도록 설정함
                break
            if squares == 0:
                print("박스 : 없음")
                out.write(frame)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)


            elif squares == 1:
                print("박스 : 1")
                newframe = Optical_flow(frame, cnt)
                print("zero stop check", cornerflag)
                cv2.imwrite('frame.png', frame)
                out.write(newframe)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                passflag = 0

            elif squares == 2:
                print("박스 : 2")
                newframe = Optical_flow2(frame, cnt)
                print("zero stop check", cornerflag)
                out.write(newframe)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                passflag = 0

            # if passflag == 1:
        cv2.destroyAllWindows()

        cap.release()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()