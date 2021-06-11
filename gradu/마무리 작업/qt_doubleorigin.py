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
xi, yi, x2, y2= -1, -1, -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy, x_copy2, y_copy2 = -1, -1, -1, -1
global numOfDot1, numOfDot2
squares = 0

stopbegin = 0
stopbegincnt = 0

form_class=uic.loadUiType("myEvent.ui")[0]

# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global xi, yi, x2, y2,  drawing, mode, B, G, R, squares, countM


    cv2.namedWindow('image')
    cv2.imshow('image', frame)

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        countM = countM + 1
        drawing = True
        if countM==1:
            global xi, yi
            xi, yi = x, y
            print(countM)
        elif countM==3:
            global x2, y2
            x2, y2 = x, y
            print(countM)

    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        countM = countM + 1
        drawing = False
        if mode:
            if countM==2:
                global x_copy, y_copy
                x_copy, y_copy = x, y
                # 사각형그리기
                cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)
                count=countM+1
                squares = squares + 1
                print(xi, yi, x_copy, y_copy)
                print(countM, squares)

            elif countM==4:
                global x_copy2, y_copy2
                x_copy2, y_copy2 = x, y
                # 사각형그리기
                cv2.rectangle(frame, (x2, y2), (x_copy2, y_copy2), (0, 225, 0), 3)
                squares=squares+1
                print(x2,y2,x_copy2,y_copy2)
                print(countM,squares)

            else:
                print(countM)
                return


#네모 한개
def Optical_flow(frame,cnt):
    global xi, yi, x_copy, y_copy, numOfDot1, stopbegin , stopbegincnt

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
            diff=numOfCurrent-numOfDot1
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
        numOfDot1=count

    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)



    #inpainting
    #원본 중 부분을 잘라서 저장
    original= frame[int(yi):int(y_copy), int(xi):int(x_copy)]

    #자른 이미지 그레이스케일
    gray = cv2.cvtColor(original,cv2.COLOR_BGR2GRAY)

    #이진화
    binary = np.zeros_like(gray)
    binary[gray > 127] = 255
    cv2.imshow('binary', binary)

    #인페인팅 연산
    inPainted = cv2.inpaint(original, binary, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted', inPainted)

    blurImg = inPainted
    blurImg = cv2.blur(inPainted, (10, 10))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg
    return img2




#네모 두개
def Optical_flow2(frame,cnt):
    global xi, yi, x_copy, y_copy, x2, y2, x_copy2, y_copy2, numOfDot1, numOfDot2, stopbegin , stopbegincnt
    width = frame.shape[1]
    height = frame.shape[0]

    X1 = xi
    Y1 = yi
    X1_copy = x_copy
    Y1_copy = y_copy
    X2 = x2
    Y2 = y2
    X2_copy = x_copy2
    Y2_copy = y_copy2


    if cnt == 1:
        return frame

    # 여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query2.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)


    termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    #코너검출
    prePt = cv2.goodFeaturesToTrack(gray1,200,0.01,10)

    nextPt, status, err = cv2.calcOpticalFlowPyrLK(gray1, gray2, prePt, None, criteria=termcriteria)
    preMv=prePt[status==1]
    nextMv=nextPt[status==1]

    sumX1=0
    count1=0
    sumY1=0

    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        px,py=p.ravel()
        nx,ny=n.ravel()
        if px > X1 and px < X1_copy and py > Y1 and py < Y1_copy:
            sumX1=sumX1+nx-px
            count1=count1+1
            sumY1=sumY1+ny-py

    moveX1 = round(sumX1 / count1)
    moveY1 = round(sumY1 / count1)
    print("특징점 개수1",count1)

    numOfCurrent1=count1



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

    moveX2 = round(sumX2 / count2)
    moveY2 = round(sumY2 / count2)
    print("특징점 개수2", count2)

    numOfCurrent2 = count2

    X1= X1 + moveX1
    X1_copy = X1_copy + moveX1
    Y1 = Y1 + moveY1
    Y1_copy = Y1_copy + moveY1
    X2 = X2 + moveX2
    X2_copy = X2_copy + moveX2
    Y2 = Y2 + moveY2
    Y2_copy = Y2_copy + moveY2


    if stopbegin == 1:
        stopbegincnt = stopbegincnt +1
        if(stopbegincnt ==10):
            stopbegin == 0
    else:
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


    xi= X1
    xi_copy = X1_copy
    yi = Y1
    yi_copy = Y1_copy
    x2 = X2
    x_copy2 = X2_copy
    y2 = Y2
    y_copy2 = Y2_copy


    if(cnt%10==0):
        numOfDot1=count1
        numOfDot2=count2

    try:
        os.remove("query2.jpg")
    except:
        pass
    cutimg2 = frame.copy()
    cv2.imwrite('query2.jpg', cutimg2)



    #inpainting
    #원본 중 부분을 잘라서 저장
    One_Bon1= frame[int(yi):int(y_copy), int(xi):int(x_copy)]
    One_Bon2 = frame[int(y2):int(y_copy2), int(x2):int(x_copy2)]
    #자른 이미지 그레이스케일
    gray1 = cv2.cvtColor(One_Bon1,cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(One_Bon2, cv2.COLOR_BGR2GRAY)
    #이진화
    binary1 = np.zeros_like(gray1)
    binary1[gray1 > 127] = 255
    cv2.imshow('binary1', binary1)
    binary2 = np.zeros_like(gray2)
    binary2[gray2 > 127] = 255
    cv2.imshow('binary2', binary2)
    #인페인팅 연산
    inPainted1 = cv2.inpaint(One_Bon1, binary1, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted1', inPainted1)
    inPainted2 = cv2.inpaint(One_Bon2, binary2, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted2', inPainted2)
    blurImg1 = inPainted1
    blurImg1 = cv2.blur(inPainted1, (10, 10))
    blurImg2 = inPainted2
    blurImg2 = cv2.blur(inPainted2, (10, 10))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg1
    img2[int(y2):int(y_copy2), int(x2):int(x_copy2)] = blurImg2
    cv2.imshow('monitor',img2)
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
        global cnt, stopbegin, countM, squares
        countM=0
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

            key = cv2.waitKey(delay)
            if cnt == 1 or key ==32:
                countM= 0
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
                        countM=0
                        squares = 0
                        cv2.setMouseCallback('image', onMouse, param=frame)
                        print("2 squares : ", squares)
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
                        countM=0
                        print("3 squares : ", squares)
                        break
            elif key == 27:  # Esc:종료
                break
            print("while문 탈출")
            print("stopbegin", stopbegin)


            print("squares : ",squares)
            if quitflag ==1:    # 좀더 부드럽게 종료하도록 설정함
                break
            if  squares == 0:
                print("박스 : 없음")
                out.write(frame)
                cv2.imwrite('frame.png', frame)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                
                ''' 되감기 '''
                # 현재 프레임 세는 거 그거를 -하고 그거를 지표로 찾아서 편집을 거기서 부터 새로 하자
                # out 이 생기지만 전에 있던게 있으면
                # 프레임을 다 저장해 놓고 다 하면은 왔다갔다는 할 수 있다. 
                # 뒤로 가기 하는 이유가 왔다 갔다 하면 된다. 
                # 원본을 뒤로 가기 해도 고치겠다. 
                # 원본도 저장을 한다????????
                # 프레임을 저장하면 되는
                # frame 1 2 3 결과가 나올때 마다 
                # 키보드 누를 경우 이제 cnt를 10개 만큼 빼는 식으로 줄인다, 전역변수로 해가지고 함수에 관여할수 있게 해야하고
                # cnt를 매개로 번호에 따라서 재생을 해야한다........
                # 있는 상황에서도 할수 있는게 안 읽어오면 된다, 
                # 다음 순서에 cap read안에 있는 함수들은 아래에 cnt 기준으로 하는 다 옮겨가서 그 안에서 while

                ''' 빨리감기 '''


                """
                지금 이철 교수님께서 우리는 원래 그걸 직접 만드려고 했는데 
                저번주 까지 어떻게 하려 했는데
                발표를 했는데 이철 교수님이 너무 쉬운방법이고 이미 만들어 진거 잘 있는데
                겉모습, qt 활용 하는 쪽으로 한번 말하셔서 고치고 있었는데
                어떤 방향을 원하시는지 모르겠다. 

                알고리즘은 직접 구현해 봤지만, 성능이 좋지 않아서 그냥 내장함수 쓰는거로 생각중이다. 
                **은나르 파나벡** ?? 모든 픽셀 계산 하는 거라서
                이제와서?? 이거를??? 제안이라는거가 ... ... ...
                qt를 고치라고 하셨는데, 정확히 어떻게 하라고 하셨는지 잘 모르겠다. 
                """

            elif squares == 1:
                print("박스 : 1")
                newframe = Optical_flow(frame, cnt)
                cv2.imwrite('frame', frame)
                out.write(newframe)
                self.qPixmapFileVar = QPixmap()
                self.qPixmapFileVar.load("frame.png")
                self.qPixmapFileVar = self.qPixmapFileVar.scaledToWidth(600)
                self.video_label.setPixmap(self.qPixmapFileVar)
                passflag = 0

            elif squares == 2:
                print("박스 : 2")
                newframe = Optical_flow2(frame, cnt)
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