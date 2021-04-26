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
                    elif k == ord('s'):
                        print('s를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg)
                        break
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
                    # surf 시작
                    elif k == ord('s'):
                        print('s를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg2
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg2 = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg2)
                        break

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