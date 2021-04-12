# RANSAC 원근 변환 근사 계산으로 나쁜 매칭 제거 (match_homography_accuracy.py)

import cv2, numpy as np, os



#surf 함수로 지정
def SURF(frame) :
    img1 = cv2.imread('kapWhiteIn.jpg')

    img2=cv2.resize(frame, dsize=(640, 480), interpolation=cv2.INTER_AREA)
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    # ORB, BF-Hamming 로 knnMatch  ---①
    detector = cv2.xfeatures2d.SURF_create()
    kp1, desc1 = detector.detectAndCompute(gray1, None)
    kp2, desc2 = detector.detectAndCompute(gray2, None)
    matcher = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
    matches = matcher.match(desc1, desc2)

    # 매칭 결과를 거리기준 오름차순으로 정렬 ---③
    matches = sorted(matches, key=lambda x:x.distance)
    # 모든 매칭점 그리기 ---④
    res1 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                      flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)

    # 매칭점으로 원근 변환 및 영역 표시 ---⑤
    src_pts = np.float32([ kp1[m.queryIdx].pt for m in matches ])
    dst_pts = np.float32([ kp2[m.trainIdx].pt for m in matches ])
    # RANSAC으로 변환 행렬 근사 계산 ---⑥
    mtrx, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 55)
    h,w = img1.shape[:2]
    pts = np.float32([ [[0,0]],[[0,h-1]],[[w-1,h-1]],[[w-1,0]] ])
    dst = cv2.perspectiveTransform(pts,mtrx)
    img2 = cv2.polylines(img2,[np.int32(dst)],True,255,3, cv2.LINE_AA)

    # 정상치 매칭만 그리기 ---⑦
    matchesMask = mask.ravel().tolist()
    res2 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                       matchesMask = matchesMask,
                        flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    # 모든 매칭점과 정상치 비율 ---⑧
    accuracy=float(mask.sum()) / mask.size
    print("accuracy: %d/%d(%.2f%%)" % (mask.sum(), mask.size, accuracy))

    return res2



















#동영상에 적용



#현재 작업 폴더 확인하는 함수
#os.getcwd()

#동영상이 들어있는 위치로 작업 폴더를 변경하기
#os.chdir('C:\\Users\\JUEUN\\PycharmProjects\\pythonProject1')


os.getcwd()

#cv2.VideoCapture() = 비디오 여는 함수(를 cap이라고 지정)
#cv2.VideoCapture.read() = 비디오를 프레임별로 읽는 함수(뒤에 cap.read로 씀)
cap= cv2.VideoCapture('kappaVideo.mp4')


#그렇게 읽은 프레임의 높이와 너비(픽셀), 초당 프레임수(밀리초)를 확인한다.
width=cap.get(3)#비디오의 너비를 확인할 수 있는 함수.(확인 하고 또 새로 높이 수정하고 싶으면 cap.set(3, 원하는 너비)
height=cap.get(4)#비디오의 높이를 확인할 수 있는 함수.(확인 하고 또 새로 높이 수정하고 싶# 면 cap.set(4, 원하는 높이)
fps=cap.get(5)#비디오 초당 프레임수 확인할 수 있는 함수
print('프레임 너비:%d, 프레임 높이:%d, 초당 브레임 수:%d'%(width, height, fps))


#비디오가 정상적으로 읽히는 동안 계속 프레임 불러와서
#프레임 하나 당 surf적용
while cap.isOpened():
    run, frame = cap.read()#run값이 참이면 read()로 프레임별로 읽기
    if not run:
        print("[프레임 수신 불가] - 종료합니다")
        break

    cv2.imshow('KAPPA', SURF(frame))

    if cv2.waitKey(27) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()