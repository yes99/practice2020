import cv2, numpy as np, os,math
from fuc import *

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


# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R

    cv2.namedWindow('image')
    cv2.imshow('image', frame)  # 화면에 표시  --- ③

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        global xi, yi
        xi, yi = x, y

        print("마우스 누름")
    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        print("마우스 땟음")

        drawing = False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy = x, y
            # 사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)
            print(xi, yi, x_copy, y_copy)




# __main__
video_file = "dance.mp4"

global cnt
cnt = 0  # 프레임 번호
mouseflag = 1

cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성
fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
delay = int(1000 / fps)

color = np.random.randint(0, 255, (200, 3))
lines = None  # 추적 선을 그릴 이미지 저장 변수




while cap.isOpened():  # 캡쳐 객체 초기화 확인
    ret, frame = cap.read()
    if not ret:
        break
    cnt = cnt + 1
    img_draw = frame.copy()
    #print(xi, yi, x_copy, y_copy)

    key = cv2.waitKey(delay)

    if key == 32 or cnt == 1:
        #print("스페이스바 누름")
        cv2.namedWindow('image')
        #print("그리기이미지")
        cv2.imshow('image', frame)  # 화면에 표시  --- ③
        cv2.setMouseCallback('image', onMouse, param=frame)
        while True:

            k = cv2.waitKey(delay) & 0xFF

            # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대

            if k == 27:
                # print("ESC키 눌러짐")
                #print("esc누름")
                mouseflag = 1
                break  # 키보드 while문 탈출
            # 다시 영역지정
            elif k == ord('r'):
                print('r을 누름')
                frame = img_draw.copy()
                cv2.destroyAllWindows()
                #print("r img")
                cv2.imshow('image', frame)
                cv2.setMouseCallback('image', onMouse, param=frame)
            elif k == ord('s'):
                #print('s를 누름')
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
    #print("result img")
    cv2.imshow('result', Optical_flow(frame, cnt, xi, yi, x_copy, y_copy))

cv2.destroyAllWindows()
cap.release()