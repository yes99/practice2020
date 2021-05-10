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

video_file = "rerere.mp4"


def Optical_flow(frame):
    global xi, yi, x_copy, y_copy, numOfDot
    width = frame.shape[1]
    height = frame.shape[0]
    q1=0
    q2=0
    q3=0
    q4=0
    size = []
    move = [0,0,0,0]


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
            cv2.circle(frame, (nx, ny), 2, (0,255,0),3)
            dx = nx - px
            dy = ny - py
            if dx > 0 and dy > 0:
                q1 = q1 +1
                size.append(1)
                move[0] = move [0]+1
            elif dx > 0 and dy < 0:
                q2 = q2 +1
                size.append(-1)
                move[1] = move [1]+1
            elif dx < 0 and dy < 0:
                q3 = q3 +1
                size.append(-1)
                move[2] = move [2]+1
            elif dx < 0 and dy > 0:
                q4 = q4 +1
                size.append(1)
                move[3] = move [3]+1

    sizelen = (len(size))/2
    sizelen = int(sizelen)
    print("sizelen", sizelen)
    checksize = 0
    if cnt > 10:
        for i in range(1, sizelen):
            checksize = checksize + size[i]
    print("size please : ", checksize)

    print(move)
    scount = "CORNERS : %d" %(count)
    slist = "%d %d %d %d" %(move[0],move[1],move[2],move[3])
    cv2.putText(frame, scount, (5, 20), cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0))
    cv2.putText(frame, slist, (5, 100), cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0))


    moveX = round(sumX / count)
    moveY = round(sumY / count)
    print("특징점 개수",count)

    numOfCurrent=count


    xi = xi + moveX
    x_copy = x_copy + moveX
    yi = yi + moveY
    y_copy = y_copy + moveY

    cntdown = "query smaller, farfar "
    cntup = "query bigger, closer"
    sscount = "FRAME%d"%(cnt)
    cv2.imwrite('./im/'+sscount+'.PNG', img_draw)

    #크기 조절 ㄱㄱ
    """
    if checksize > 0:
        xi = xi + 2
        yi = yi + 2
        x_copy=x_copy-2
        y_copy = y_copy - 2
        cv2.putText(frame, cntdown, (10, 90), cv2.FONT_HERSHEY_PLAIN, 1, (255, 0, 0))
    elif checksize < 0:
        xi = xi - 2
        yi = yi - 2
        x_copy = x_copy + 2
        y_copy = y_copy + 2
        cv2.putText(frame, cntup, (10, 90), cv2.FONT_HERSHEY_PLAIN, 1, (255, 0, 0))
    """
    """
    if cnt > 11:
        diff=numOfCurrent-numOfDot   #현재점 - 이전점      
        #diff가 크면, 가까워 지는 것
        #diff가 작으면, 멀어지는 것
        print("numOfCurrent : ", numOfCurrent)
        print("numOfDot : ", numOfDot)
        #print("diff : " diff, numOfCurrent, numOfDot)
        # 현재특징점이 더 적을때->로고가 작아짐
        if x_copy - xi >= 20 and y_copy - yi >= 20:
            if diff < -6:
                # round(diff/div+plus)
                cv2.putText(frame, cntdown, (10, 90), cv2.FONT_HERSHEY_PLAIN, 1, (255, 0, 0))

                xi = xi + 2
                yi = yi + 2

                x_copy=x_copy-2
                y_copy = y_copy - 2
        #현재특징점이 더 많을때->로고가 커짐
            elif diff > 6:
                cv2.putText(frame, cntup, (10, 90), cv2.FONT_HERSHEY_PLAIN, 1, (255, 0, 0))
                xi = xi - 2
                yi = yi - 2

                x_copy = x_copy + 2
                y_copy = y_copy + 2
        print("diff", diff)
    """
    if(cnt%10==0):
        numOfDot=count
    swidth ="width : %f" %(x_copy-xi)
    sheight = "height : %f" %(y_copy-yi)
    cntframe = "frame : %d" %(count)
    cv2.putText(frame, swidth, (10, 40), cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0))
    cv2.putText(frame, sheight, (10, 60), cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0))

    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)
    print((xi+moveX, yi+moveY), (x_copy+moveX, y_copy+moveY), moveX, moveY )
    cv2.rectangle(img2, (xi+moveX, yi+moveY), (x_copy+moveX, y_copy+moveY), (B, G, R), 3)

    return img2


# 마우스 이벤트
def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R

    cv2.namedWindow('image')
    cv2.imshow('image', frame)

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        global xi, yi
        xi, yi = x, y

    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy = x, y
            # 사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)

# __main__

global cnt
global key
cnt = 0  # 프레임 번호
mouseflag = 1

cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성
fps = cap.get(cv2.CAP_PROP_FPS)  # 프레임 수 구하기
delay = int(1000 / fps)

while cap.isOpened():  # 캡쳐 객체 초기화 확인
    ret, frame = cap.read()
    if not ret:
        break
    cnt = cnt + 1
    print("cnt :", cnt)
    img_draw = frame.copy()

    key = cv2.waitKey(delay)
#
    if key == 32 or cnt == 1 :
        cv2.namedWindow('image')
        cv2.imshow('image', frame)
        cv2.setMouseCallback('image', onMouse, param=frame)
        while True:
            k = cv2.waitKey(delay) & 0xFF
            # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
            if k == 27:
                mouseflag = 1
                break
            # 다시 영역지정
            elif k == ord('r'):
                print('r을 누름')
                frame = img_draw.copy()
                cv2.destroyAllWindows()
                cv2.imshow('image', frame)
                cv2.setMouseCallback('image', onMouse, param=frame)
            elif k == ord('s'):
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
    cv2.imshow('result', Optical_flow(frame))

cv2.destroyAllWindows()
cap.release()