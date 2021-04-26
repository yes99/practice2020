import cv2, numpy as np,os

mode, drawing = True, False
# 마우스 눌렀을때 좌표
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1

def Optical_flow(frame):


    #여기서 다음쿼리를 찾는 과정을 수행

#마우스 이벤트
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

#__main__
video_file = "dddd.mp4"

current_cnt = 0  # 현재 프레임 표시용 변수

cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성
fps = cap.get(cv2.CAP_PROP_FPS) # 프레임 수 구하기
delay = int(1000/fps)

global prevImg
prevImg=None
color = np.random.randint(0,255,(200,3))
lines = None  #추적 선을 그릴 이미지 저장 변수

#동영상 크기 받아오기
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)


def LK(prevImg, nextImg):
    if prevImg is None:
        img_draw = nextImg
        prevImg = gray
        # 추적선 그릴 이미지를 프레임 크기에 맞게 생성
        lines = np.zeros_like(frame)
        # 추적 시작을 위한 코너 검출  ---①
        prevPt = cv2.goodFeaturesToTrack(prevImg, 200, 0.01, 10)
    else:
        nextImg = gray
        # 옵티컬 플로우로 다음 프레임의 코너점  찾기 ---②
        nextPt, status, err = cv2.calcOpticalFlowPyrLK(prevImg, nextImg, \
                                                       prevPt, None, criteria=termcriteria)
        # 대응점이 있는 코너, 움직인 코너 선별 ---③
        prevMv = prevPt[status == 1]
        nextMv = nextPt[status == 1]
        for i, (p, n) in enumerate(zip(prevMv, nextMv)):
            px, py = p.ravel()
            nx, ny = n.ravel()
            # 이전 코너와 새로운 코너에 선그리기 ---④
            cv2.line(lines, (px, py), (nx, ny), color[i].tolist(), 2)
            # 새로운 코너에 점 그리기
            cv2.circle(img_draw, (nx, ny), 2, color[i].tolist(), -1)
        # 누적된 추적 선을 출력 이미지에 합성 ---⑤
        img_draw = cv2.add(img_draw, lines)
        # 다음 프레임을 위한 프레임과 코너점 이월
        prevImg = nextImg
        prevPt = nextMv.reshape(-1, 1, 2)
    
    cv2.imshow('OpticalFlow-LK', img_draw)







while cap.isOpened():  # 캡쳐 객체 초기화 확인
    ret, frame = cap.read()
    if not ret:
        break
    cnt=cnt+1
    img_draw = frame.copy()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 최초 프레임 경우
    
    

    key = cv2.waitKey(delay)
    
    if key==32 or cnt==1:
        print("스페이스바 누름")
        cv2.namedWindow('image')
        print("그리기이미지")
        cv2.imshow('image', frame)  # 화면에 표시  --- ③
        cv2.setMouseCallback('image', onMouse, param=frame)
        ti = np.zeros((x_copy - xi, y_copy - yi), np.unit8)
        timg = cv2.rectangle(ti, (xi,yi), (x_copy, y_copy), (255,255,255), -1)
#yi:y_copy, xi:x_copy
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
                cutimg = frame[yi:y_copy, xi:x_copy].copy()
                cv2.imwrite('query.jpg', cutimg)
                qimg = cv2.imread('query.jpg')
                LK(timg, qimg)
                timg = qimg

                break

    elif key == 27:  # Esc:종료
        break
    elif key == 8:  # Backspace:추적 이력 지우기
        prevImg = None
cv2.destroyAllWindows()
cap.release()