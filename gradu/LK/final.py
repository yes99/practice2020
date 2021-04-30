import cv2, numpy as np, os,math

mode, drawing = True, False
# 마우스 눌렀을때 좌표
# global xi, yi, x_copy, y_copy
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1


def Optical_flow(frame):
    global xi, yi, x_copy, y_copy
    print("optical flow 안의 xi, yi,,", xi, yi, x_copy, y_copy)
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

    nextPt, status, err=cv2.calcOpticalFlowPyrLK(gray1,gray2, prePt,None, criteria=termcriteria)
    #print("prept")
    #print(prePt)

    #print("사이")
    #print("nextPt")
    #print(nextPt)
    preMv=prePt[status==1]
    nextMv=nextPt[status==1]
    #print("차원",preMv.shape)
    sumX=0
    countX=0
    sumY=0
    countY=0


    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        px,py=p.ravel()
        nx,ny=n.ravel()

        if px > xi and px < x_copy and py > yi and py < y_copy:

            sumX=sumX+nx-px
            countX=countX+1
            sumY=sumY+ny-py
            countY=countY+1



    #moveX=int(sumX/countX/10)
    #moveY=int(sumY/countY/10)



    moveX = int(sumX / countX)
    moveY = int(sumY / countY)
    xi = xi + moveX
    x_copy = x_copy + moveX
    yi = yi + moveY
    y_copy = y_copy + moveY
    print("moveX",moveX)
    print("moveY",moveY)

    cv2.rectangle(img2, (xi, yi), (x_copy, y_copy), (B, G, R), 3)


    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    # cnt=0
    
    cv2.imwrite('query.jpg', cutimg)
    return img2

"""
    blurImg = img2[int(yi):int(y_copy), int(xi):int(x_copy)]
    blurImg = cv2.blur(blurImg, (30, 30))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg
"""



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


def mouse_callback(event, x, y, flags, param):
    print("마우스 이벤트 발생, x:", x, "y:", y)


# __main__
video_file = "son.mp4"

current_cnt = 0  # 현재 프레임 표시용 변수
global cnt
cnt = 0  # 프레임 번호
#fc = 0  # flag change의 약자임, 플래그로 두번 멈추는거 컨트롤 하려고 만들었음
mouseflag = 1

cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성
fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
delay = int(1000 / fps)

global prevImg
prevImg = None
color = np.random.randint(0, 255, (200, 3))
lines = None  # 추적 선을 그릴 이미지 저장 변수

# 동영상 크기 받아오기
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)


while cap.isOpened():  # 캡쳐 객체 초기화 확인
    ret, frame = cap.read()
    if not ret:
        break
    cnt = cnt + 1
    img_draw = frame.copy()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 최초 프레임 경우
    # cv2.imshow('OpticalFlow-LK', img_draw)
    print(xi, yi, x_copy, y_copy)

    key = cv2.waitKey(delay)

    if key == 32 or cnt == 1:
        print("스페이스바 누름")
        cv2.namedWindow('image')
        print("그리기이미지")
        cv2.imshow('image', frame)  # 화면에 표시  --- ③
        cv2.setMouseCallback('image', onMouse, param=frame)
        while True:

            k = cv2.waitKey(delay) & 0xFF

            # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대

            if k == 27:
                # print("ESC키 눌러짐")
                print("esc누름")
                mouseflag = 1
                break  # 키보드 while문 탈출
            # 다시 영역지정
            elif k == ord('r'):
                print('r을 누름')

                frame = img_draw.copy()
                cv2.destroyAllWindows()
                print("r img")
                cv2.imshow('image', frame)
                cv2.setMouseCallback('image', onMouse, param=frame)
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
                cutimg = img_draw.copy()
                # cnt=0
                cv2.imwrite('query.jpg', cutimg)

                break

    elif key == 27:  # Esc:종료
        break
    elif key == 8:  # Backspace:추적 이력 지우기
        prevImg = None
    print("result img")
    cv2.imshow('result', Optical_flow(frame))

cv2.destroyAllWindows()
cap.release()