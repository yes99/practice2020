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
global numOfDot


def scaling(cnt, numOfCurrent, count, xi, yi, x_copy, y_copy, numOfDot):
    if cnt > 11:
        diff=numOfCurrent-numOfDot
        print(diff)
        #현재특징점개수/이전특징점개수
        # 현재특징점이 더 적을때->로고가 작아짐

        if diff < -6:
            plus = 0.5
            div = 2
            diff=abs(diff)
            # round(diff/div+plus)
            xi = xi + 2
            yi = yi + 2

            x_copy=x_copy-2
            y_copy = y_copy - 2
        #현재특징점이 더 많을때->로고가 커짐
        elif diff > 6:
            plus2 = 0.5
            div2 = 2
            diff = abs(diff)
            xi = xi - 2
            yi = yi - 2

            x_copy = x_copy + 2
            y_copy = y_copy + 2
    



def InPainting(frame, img2,xi, yi, x_copy, y_copy ):
    #원본 중 부분을 잘라서 저장
    One_Bon= frame[int(yi):int(y_copy), int(xi):int(x_copy)]

    #자른 이미지 그레이스케일
    gray = cv2.cvtColor(One_Bon,cv2.COLOR_BGR2GRAY)

    #이진화
    E_Zin_Hwa = np.zeros_like(gray)
    E_Zin_Hwa[gray > 127] = 255
    #E_Zin_Hwa[gray <= 127] = 0
    cv2.imshow('binary', E_Zin_Hwa)

    #인페인팅 연산
    inPainted = cv2.inpaint(One_Bon, E_Zin_Hwa, 10, cv2.INPAINT_TELEA)
    cv2.imshow('inPainted', inPainted)

    blurImg = inPainted
    blurImg = cv2.blur(inPainted, (30, 30))
    img2[int(yi):int(y_copy), int(xi):int(x_copy)] = blurImg
    return img2



def Optical_flow(frame, cnt, xi, yi, x_copy, y_copy):

    # 동영상 크기 받아오기
    width = frame.shape[1]
    height = frame.shape[0]


    #print(frame.shape)
    #print("optical flow 안의 xi, yi,,", xi, yi, x_copy, y_copy)
    if cnt == 1:
        return frame
    #print("cnt",cnt)
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
    print("좌표들 ", xi , yi, x_copy, y_copy)
    for i,(p,n) in enumerate(zip(preMv,nextMv)):
        px,py=p.ravel()
        nx,ny=n.ravel()
        if px > xi and px < x_copy and py > yi and py < y_copy:
            #print(n-p)
            sumX=sumX+nx-px
            count=count+1
            sumY=sumY+ny-py
    print("카운트: ", count)
    moveX = round(sumX / count)
    moveY = round(sumY / count)
    print("특징점 개수",count)

    numOfCurrent=count


    xi = xi + moveX
    x_copy = x_copy + moveX
    yi = yi + moveY
    y_copy = y_copy + moveY

    if(cnt%10==0):
        numOfDot=count
    scaling(cnt, numOfCurrent, count, xi , yi , x_copy, y_copy, numOfDot)


        
    #print("moveX,moveY",moveX,moveY)
    #print(xi,yi,x_copy,y_copy)

    try:
        os.remove("query.jpg")
    except:
        pass
    cutimg = frame.copy()
    cv2.imwrite('query.jpg', cutimg)
###########################인페인팅##########################################3
    InPainting(frame, img2, xi, yi, x_copy, y_copy)
    return img2





#def mouse_callback(event, x, y, flags, param):
    #print("마우스 이벤트 발생, x:", x, "y:", y)
