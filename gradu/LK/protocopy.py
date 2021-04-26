import cv2
import numpy as np
import math
import os

mode, drawing = True, False
# 마우스 눌렀을때 좌표
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1

def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R

    cv2.namedWindow('image')
    cv2.imshow('image', frame)  # 화면에 표시  --- ③

    #마우스 눌렀을때
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
        global xi, yi
        xi, yi=x, y

        print("마우스 누름")
    #마우스 뗏을때
    elif event==cv2.EVENT_LBUTTONUP:
        print("마우스 땟음")

        drawing=False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy=x,y
            #사각형그리기
            cv2.rectangle(frame, (xi,yi), (x_copy, y_copy), (0, 225, 0), 3)
            print(xi,yi,x_copy,y_copy)

#콜백추가
def mouse_callback(event, x, y, flags, param):
    print("마우스 이벤트 발생, x:", x, "y:", y)



video_file = "ddd.mp4"  # 동영상 파일 경로   #동영상을 뽑아와야겠지
cnt1 = 0#현재 프레임 표시용 변수
cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성  ---①

# 동영상 크기 설정이다, 나중에 정말로 필요하더라.
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

print("width = %d  height = %d" % (width, height))  # 디버깅 한번 해주고
color = np.random.randint(0,255,(200,3))
lines = None  #추적 선을 그릴 이미지 저장 변수
prevImg = None  # 이전 프레임 저장 변수
termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)
cnt=0
tavg = 0.0
mouseflag=0
count=1

if cap.isOpened():  # 캡쳐 객체 초기화 확인
    print("열림")
    while True:
        ret, img = cap.read()  # 다음 프레임 읽기
        newimg = img.copy()

        if ret:  # 프레임 읽기 정상일 경우
            print(" 프레임 읽기 정상일 경우")
            space = cv2.waitKey(1) & 0xFF
            img_draw = img.copy()
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

            if space == 32:
                cv2.namedWindow('image')
                cv2.imshow('image', img)  # 화면에 표시  --- ③
                cv2.setMouseCallback('image', onMouse, param=img)
                while True:
                    k = cv2.waitKey(1) & 0xFF
                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
                    if k == 27:
                        # print("ESC키 눌러짐")
                        print("esc누름")
                        mouseflag = 1
                        break  # 키보드 while문 탈출
                    # 다시 영역지정
                    elif k == ord('r'):
                        print('r을 누름')
                        img = newimg.copy()
                        cv2.destroyAllWindows()
                        cv2.imshow('image', img)
                        cv2.setMouseCallback('image', onMouse, param=img)
                    # surf 시작
                    elif k == ord('l'):
                        print('l를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg)
                        qqq = cv2.imread("query.jpg")
                        qdst = qqq.copy()

                        gray = cv2.cvtColor(qqq, cv2.COLOR_RGB2GRAY)
                        corners = cv2.goodFeaturesToTrack(gray, 100, 0.01, 5 , blockSize = 3, useHarrisDetector= True, k=0.03)
                        for i in corners:
                            cv2.circle(qdst, tuple(i[0]), 3,(0,0,255),2)
                        cv2.imshow("qdst", qdst)
                        #cv2.waitKey(0)
                        cv2.destroyAllWindows()
                        img[yi:y_copy, xi:x_copy] = qdst
                        cv2.imshow("img", img)
                        prevPt = img
                        if prevImg is None:
                            prevImg = gray
                            # 추적선 그릴 이미지를 프레임 크기에 맞게 생성
                            lines = np.zeros_like(img)
                        else:
                            nextImg = gray
                            # 옵티컬 플로우로 다음 프레임의 코너점  찾기 ---②
                            nextPt, status, err = cv2.calcOpticalFlowPyrLK(prevImg, nextImg, \
                                                            prevPt, None, criteria=termcriteria)
                            # 대응점이 있는 코너, 움직인 코너 선별 ---③
                            prevMv = prevPt[status==1]
                            nextMv = nextPt[status==1]
                            for i,(p, n) in enumerate(zip(prevMv, nextMv)):
                                cnt = cnt +1
                                px,py = p.ravel()
                                nx,ny = n.ravel()
                                # 이전 코너와 새로운 코너에 선그리기 ---④
                                cv2.line(lines, (px, py), (nx,ny), color[i].tolist(), 2)
                                # 새로운 코너에 점 그리기
                                cv2.circle(img_draw, (nx,ny), 2, color[i].tolist(), -1)
                            # 누적된 추적 선을 출력 이미지에 합성 ---⑤
                            img_draw = cv2.add(img_draw, lines)
                            prevImg = nextImg
                            prevPt = nextMv.reshape(-1,1,2)

            if count ==1:
                count =2
                cnt3 = "double stop"
                #cv2.putText(img, text3, (50, 400), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)
                fc = 1  # 한번 멈추면 분명 그 다음에 또 같은 이유로 멈춰서 플래그를 세워준다
                cv2.namedWindow('image')
                cv2.imshow('image', img)  # 화면에 표시  --- ③
                cv2.setMouseCallback('image', onMouse, param=img)
                while True:

                    k = cv2.waitKey(1) & 0xFF
                  # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대

                    if k == 27:
                        # print("ESC키 눌러짐")
                        print("esc누름")
                        mouseflag = 1
                        break  # 키보드 while문 탈출
                    # 다시 영역지정
                    elif k == ord('r'):
                        print('r을 누름')
                        img = newimg.copy()
                        cv2.destroyAllWindows()
                        cv2.imshow('image', img)
                        cv2.setMouseCallback('image', onMouse, param=img)
                    # LK 시작
                    elif k == ord('l'):
                        print('l를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg2
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg2 = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg2)
                        qqq = cv2.imread("query.jpg")
                        qdst = qqq.copy()

                        gray = cv2.cvtColor(qqq, cv2.COLOR_RGB2GRAY)
                        corners = cv2.goodFeaturesToTrack(gray, 100, 0.01, 5 , blockSize = 3, useHarrisDetector= True, k=0.03)
                        for i in corners:
                            cv2.circle(qdst, tuple(i[0]), 3,(0,0,255),2)
                        cv2.imshow("qdst", qdst)
                        #cv2.waitKey(0)
                        cv2.destroyAllWindows()
                        img[yi:y_copy, xi:x_copy] = qdst
                        cv2.imshow("img", img)
                        prevPt = img
                        if prevImg is None:
                            prevImg = gray
                            # 추적선 그릴 이미지를 프레임 크기에 맞게 생성
                            lines = np.zeros_like(img)
                        else:
                            nextImg = gray
                            # 옵티컬 플로우로 다음 프레임의 코너점  찾기 ---②
                            nextPt, status, err = cv2.calcOpticalFlowPyrLK(prevImg, nextImg, \
                                                            prevPt, None, criteria=termcriteria)
                            # 대응점이 있는 코너, 움직인 코너 선별 ---③
                            prevMv = prevPt[status==1]
                            nextMv = nextPt[status==1]
                            for i,(p, n) in enumerate(zip(prevMv, nextMv)):
                                cnt = cnt +1
                                px,py = p.ravel()
                                nx,ny = n.ravel()
                                # 이전 코너와 새로운 코너에 선그리기 ---④
                                cv2.line(lines, (px, py), (nx,ny), color[i].tolist(), 2)
                                # 새로운 코너에 점 그리기
                                cv2.circle(img_draw, (nx,ny), 2, color[i].tolist(), -1)
                            # 누적된 추적 선을 출력 이미지에 합성 ---⑤
                            img_draw = cv2.add(img_draw, lines)
                            prevImg = nextImg
                            prevPt = nextMv.reshape(-1,1,2)
                            break

            cv2.imshow('OpticalFlow-LK', img_draw)
            if mouseflag ==1:
                break
            else:  # 그 외에는 그냥 넘겨
                cv2.waitKey(25)  # 25ms 지연(40fps로 가정)   --- ④
        else:  # 다음 프레임 읽을 수 없슴,
            break  # 재생 완료

else:
    print("can't open video.")  # 캡쳐 객체 초기화 실패
cap.release()  # 캡쳐 자원 반납
cv2.destroyAllWindows()