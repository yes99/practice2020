import cv2, numpy as np, os,math

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

def Optical_flow(frame):
    global xi, yi, x_copy, y_copy, numOfDot

    print("optical flow 안의 xi, yi,,", xi, yi, x_copy, y_copy)
    if cnt == 1:
        return frame
    # 여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    #종결 조건
    termcriteria =  (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)

    #코너검출
    prePt = cv2.goodFeaturesToTrack(gray1,200,0.01,10)

    #다음 장면의 코너점 검출/움직인 점 검출
    nextPt, status, err=cv2.calcOpticalFlowPyrLK(gray1,gray2, prePt,None, criteria=termcriteria)

    #움직인점들(status==1인 점들)만 Mv에 저장
    preMv=prePt[status==1]
    nextMv=nextPt[status==1]

    sumX=0
    count=0
    sumY=0
                    #한점씩 차례로 추출
    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        #한점씩 차례로 추출
        px,py=p.ravel()
        nx,ny=n.ravel()
        if px > xi and px < x_copy and py > yi and py < y_copy:
            print(n-p)
            sumX=sumX+nx-px
            count=count+1
            sumY=sumY+ny-py

    moveX = int(sumX / count)
    moveY = int(sumY / count)
    print("특징점 개수",count)


    xi = xi + moveX
    x_copy = x_copy + moveX
    yi = yi + moveY
    y_copy = y_copy + moveY


    print("moveX,moveY",moveX,moveY)
    #print("moveY",moveY)

    print(xi,yi,x_copy,y_copy)

    #cv2.rectangle(img2, (xi, yi), (x_copy, y_copy), (B, G, R), 3)


    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)


    #인페인팅

    #원본
    img = frame[int(yi):int(y_copy), int(xi):int(x_copy)]

    #그레이스케일
    mask = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #이진화
    thresh_np = np.zeros_like(mask)
    thresh_np[mask > 127] = 255
    #인페인팅 연산
    dst = cv2.inpaint(img, thresh_np, 3, cv2.INPAINT_TELEA)


    blurImg = dst
    blurImg = cv2.blur(dst, (30, 30))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg


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

        #print("마우스 누름")
    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        #print("마우스 땟음")

        drawing = False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy = x, y
            # 사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)
            #print(xi, yi, x_copy, y_copy)


#def mouse_callback(event, x, y, flags, param):
    #print("마우스 이벤트 발생, x:", x, "y:", y)


# __main__
video_file = "dddd.mp4"

global cnt
cnt = 0  # 프레임 번호
mouseflag = 1

cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성
fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
delay = int(1000 / fps)

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
    cv2.imshow('result', Optical_flow(frame))

cv2.destroyAllWindows()
cap.release()