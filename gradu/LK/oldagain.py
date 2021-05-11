import cv2, numpy as np,os

mode, drawing = True, False
# 마우스 눌렀을때 좌표
#global xi, yi, x_copy, y_copy
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1




def Optical_flow(frame):
    global xi, yi, x_copy, y_copy
    print("optical flow 안의 xi, yi,,",xi,yi,x_copy,y_copy)
    if cnt==1:
        return frame
    #여기서 다음쿼리를 찾는 과정을 수행
    img1 = cv2.imread('query.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    # y, x=>u, v
    #vector_u = list()
    #vector_v = list()
    vector_u=0
    vector_v=0
    #optical flow
    #kernel_dx=np.array([-1,1])
    #kernel_dy=np.array([[-1],
    #                    [1]])

    #img_gx=cv2.filter2D(gray1,-1,kernel_dx)
    #img_gy=cv2.filter2D(gray1,-1,kernel_dy)

    img_gx = cv2.Sobel(gray1, -1, 1,0)
    img_gy = cv2.Sobel(gray1, -1, 0,1)
    img_dt = gray2-gray1

    print(img_gx.shape)
    print(img_gy.shape)
    print(img_dt.shape)
    for i in range(yi,y_copy):
        for j in range(xi,x_copy):
            #dx=img_gx[i-1:i+2,j-1:j+2].copy()
            #dy=img_gy[i-1:i+2,j-1:j+2].copy()
            #dt=gray2[i-1:i+2,j-1:j+2].copy()-gray1[i-1:i+2,j-1:j+2].copy()

            #print(dx)
            #print(dy)
            '''
            A=np.array([[dy[0,0],dx[0,0]],
                        [dy[0,1],dx[0,1]],
                        [dy[0,2],dx[0,2]],
                        [dy[1,0],dx[1,0]],
                        [dy[1,1], dx[1,1]],
                        [dy[1,2], dx[1,2]],
                        [dy[2, 0], dx[2, 0]],
                        [dy[2, 1], dx[2, 1]],
                        [dy[2, 2], dx[2, 2]]
                        ])
            b=np.array([[-dt[0,0]],
                       [-dt[0,1]],
                       [-dt[0,2]],
                       [-dt[1,0]],
                       [-dt[1,1]],
                       [-dt[1,2]],
                       [-dt[2,0]],
                       [-dt[2,1]],
                       [-dt[2,2]]
                        ])
            '''
            A = np.array([[img_gy[i-1, j-1], img_gx[i-1, j-1]],
                          [img_gy[i-1, j], img_gx[i-1, j]],
                          [img_gy[i-1, j+1], img_gx[i-1, j+1]],
                          [img_gy[i, j-1], img_gx[i, j-1]],
                          [img_gy[i, j], img_gx[i, j]],
                          [img_gy[i, j+1], img_gx[i, j+1]],
                          [img_gy[i+1, j-1], img_gx[i+1, j-1]],
                          [img_gy[i+1, j], img_gx[i+1, j]],
                          [img_gy[i+1, j+1], img_gx[i+1, j+1]]
                          ])
            b = np.array([[-img_dt[i-1, j-1]],
                          [-img_dt[i-1, j]],
                          [-img_dt[i-1, j+1]],
                          [-img_dt[i, j-1]],
                          [-img_dt[i, j]],
                          [-img_dt[i, j+1]],
                          [-img_dt[i+1, j-1]],
                          [-img_dt[i+1, j]],
                          [-img_dt[i+1, j+1]]
                          ])
            #print("a",A)
            #print("b",b)
            try:
                #print("왜 역행렬없는데 ㅅㅂ")
                #print(A)
                #print(np.dot(A.T,A))
                vec=np.dot(np.linalg.inv((np.dot(A.T,A))),np.dot(A.T,b))
                #print(vec,"for 문안 벡터")

                #print(vec[0][0]," ",vec[1][0])
                vector_u=vector_u+vec[0][0]
                vector_v=vector_v+vec[1][0]
            except:
                #print("실패")
                pass

    ssize=(x_copy-xi)*(y_copy-yi)
    u_avg = int(vector_u / ssize/2)
    v_avg = int(vector_v / ssize/2)

    #u_avg=int(sum(vector_u)/len(vector_u))
    #v_avg=int(sum(vector_v)/len(vector_v))

    print(u_avg,v_avg,"평균들")

    yi=yi+u_avg
    xi=xi+v_avg
    x_copy=x_copy+v_avg
    y_copy=y_copy+u_avg

    #print(xi, yi, x_copy,y_copy)

    blurImg=img2[int(yi):int(y_copy),int(xi):int(x_copy)]
    blurImg = cv2.blur(blurImg, (30, 30))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg

    return img2


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
video_file = "rere.mp4"

current_cnt = 0  # 현재 프레임 표시용 변수
global cnt
cnt=0 #프레임 번호
fc = 0  # flag change의 약자임, 플래그로 두번 멈추는거 컨트롤 하려고 만들었음
mouseflag=1

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


while cap.isOpened():  # 캡쳐 객체 초기화 확인
    ret, frame = cap.read()
    if not ret:
        break
    cnt=cnt+1
    img_draw = frame.copy()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 최초 프레임 경우
    '''
    if prevImg is None:
        
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
    '''
    #cv2.imshow('OpticalFlow-LK', img_draw)
    print(xi, yi, x_copy,y_copy)

    key = cv2.waitKey(delay)

    if key==32 or cnt==1:
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
                #cutimg = frame[yi-1:y_copy+1, xi-1:x_copy+1].copy()
                cutimg=frame
                #cnt=0
                cv2.imwrite('query.jpg', cutimg)

                break

    elif key == 27:  # Esc:종료
        break
    elif key == 8:  # Backspace:추적 이력 지우기
        prevImg = None
    print("result img")
    cv2.imshow('result',Optical_flow(frame))

cv2.destroyAllWindows()
cap.release()