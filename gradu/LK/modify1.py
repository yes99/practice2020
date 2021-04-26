import cv2, numpy as np, os

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


def Optical_flow(tcnt):
    if tcnt ==0:
        temp = cv2.imread('preimg.jpg')
        tempp = cv2.imwrite('nowimg.jpg', temp)
        tcnt= tcnt+1

    img1 = cv2.imread('preimg.jpg')
    img2 = cv2.imread('nowimg.jpg')

    print("여긱여기")
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    print("여긱여adsafs기")
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    print("이래도 안된다고?")
    termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    prePt = cv2.goodFeaturesToTrack(img1,200,0.01,10)
    status,err,nextPt=cv2.calcOpticalFlowPyrLK(img1,img2, prePt,None, criteria=termcriteria)

    preMv=prePt[status==1]
    nextMv=nextPt[status==1]
    sumX=0
    countX=0
    sumY=0
    countY=0
    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        px,py=p.ravel()
        nx,ny=n.ravel()
        if px > xi and px > x_copy and nx < xi and nx < x_copy and py > yi and py > y_copy and ny < yi and ny < y_copy:
            sumX+=nx-px
            countX+=1
            sumY+=ny-py
            countY+=1
        moveX=sumX/countX
        moveY=sumX/countY
    cv2.rectangle(img2, (xi+moveX, yi+moveY), (x_copy+moveX, y_copy+moveY), (B, G, R), 3)

    return img2




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
video_file = "ddd.mp4"
global tcnt
tcnt =0
current_cnt = 0  # 현재 프레임 표시용 변수
global cnt
cnt = 0  # 프레임 번호
fc = 0  # flag change의 약자임, 플래그로 두번 멈추는거 컨트롤 하려고 만들었음
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

termcriteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

while cap.isOpened():  # 캡쳐 객체 초기화 확인
    count =0
    ret, frame = cap.read()
    count=count+1

    if count==1:
        print("여기임무다")
        frame1=cv2.imwrite('preimg.jpg',frame)
        frame2=cv2.imwrite('preimg.jpg',frame)
    else:
        frame2=cv2.imwrite('preimg.jpg',frame)
    if not ret:
        break
    cnt = cnt + 1
    img_draw = frame.copy()

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
                break

    elif key == 27:  # Esc:종료
        break
    elif key == 8:  # Backspace:추적 이력 지우기
        prevImg = None
    print("result img")
    cv2.imshow('result', Optical_flow(tcnt))

    frame1=cv2.imwrite('preimg.jpg',frame)
cv2.destroyAllWindows()
cap.release()