import cv2
import numpy as np
import os

mode, drawing=True,False
#마우스 눌렀을때 좌표
xi, yi=-1,-1
#주황색
B=0
G=255
R=0
#마우스 뗐을 때 좌표
x_copy, y_copy=-1,-1


def surf():
    img1 = cv2.imread('query.jpg')
    img2 = cv2.imread('kwkw3.jpg')
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    # ORB, BF-Hamming 로 knnMatch  ---①
    detector = cv2.xfeatures2d.SURF_create()
    kp1, desc1 = detector.detectAndCompute(gray1, None)
    kp2, desc2 = detector.detectAndCompute(gray2, None)
    matcher = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
    matches = matcher.match(desc1, desc2)

    # 매칭 결과를 거리기준 오름차순으로 정렬 ---③
    matches = sorted(matches, key=lambda x: x.distance)
    # 모든 매칭점 그리기 ---④
    res1 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                           flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)

    # 매칭점으로 원근 변환 및 영역 표시 ---⑤
    src_pts = np.float32([kp1[m.queryIdx].pt for m in matches])
    dst_pts = np.float32([kp2[m.trainIdx].pt for m in matches])
    # RANSAC으로 변환 행렬 근사 계산 ---⑥
    mtrx, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 55)
    h, w = img1.shape[:2]
    pts = np.float32([[[0, 0]], [[0, h - 1]], [[w - 1, h - 1]], [[w - 1, 0]]])
    dst = cv2.perspectiveTransform(pts, mtrx)
    img2 = cv2.polylines(img2, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)

    # 정상치 매칭만 그리기 ---⑦
    matchesMask = mask.ravel().tolist()
    res2 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                           matchesMask=matchesMask,
                           flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    # 모든 매칭점과 정상치 비율 ---⑧
    accuracy = float(mask.sum()) / mask.size
    print("accuracy: %d/%d(%.2f%%)" % (mask.sum(), mask.size, accuracy))

    # 결과 출력
    cv2.imshow('Matching-All', res1)
    cv2.imshow('Matching-Inlier ', res2)
    cv2.waitKey()
    cv2.destroyAllWindows()


img=cv2.imread('kwkw3.jpg',cv2.IMREAD_COLOR)
#복사이미지따로저장
newimg=img.copy()
#마우스이벤트

def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R

    #마우스 눌렀을때
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
        xi, yi=x, y
    #마우스 뗏을때
    elif event==cv2.EVENT_LBUTTONUP:
        drawing=False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy=x,y
            #사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (B, G, R), 10)

#콜백추가
def mouse_callback(event, x, y, flags, param):
    print("마우스 이벤트 발생, x:", x, "y:", y)

#256*256 에다가 brg
#img=np.zeros((256,256,3), np.uint8)
#newimg.copyTo(img)

cv2.namedWindow('image')

cv2.setMouseCallback('image',onMouse,param=img)
while(True):
    cv2.imshow('image',img)
    k=cv2.waitKey(1)&0xFF
    #비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
    if k==27:
        #print("ESC키 눌러짐")
        break
    #다시 영역지정
    elif k==ord('r'):
        img=newimg.copy()
        cv2.imshow('image', img)
        cv2.setMouseCallback('image', onMouse, param=img)
    #surf 시작
    elif k==ord('s'):
        cv2.destroyAllWindows()
        global cutimg
        #query 저장
        try:
            os.remove("query.jpg")
        except:
            pass
        cutimg= img[yi:y_copy,xi:x_copy].copy()
        cv2.imwrite('query.jpg', cutimg)
        #surf 진행
        surf()


cv2.destroyAllWindows()