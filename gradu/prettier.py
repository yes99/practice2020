# RANSAC 원근 변환 근사 계산으로 나쁜 매칭 제거 (match_homography_accuracy.py)

import cv2, numpy as np


img1 = cv2.imread('kappa_query.jpg')
img2 = cv2.imread('kappa_train66.jpg')
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



#print (dst_pts_x)

# RANSAC으로 변환 행렬 근사 계산 ---⑥
mtrx, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 55)
h,w = img1.shape[:2]
pts = np.float32([ [[0,0]],[[0,h-1]],[[w-1,h-1]],[[w-1,0]] ])
dst = cv2.perspectiveTransform(pts,mtrx)

print(dst)
print(dst[0][0][1])
#dst_pts_x=np.float32([ dst[m][0][0] for m in dst])
#dst_pts_y=np.float32([ dst[m][0][1] for m in dst])

x_min=min(dst[0][0][0],dst[1][0][0],dst[2][0][0],dst[3][0][0])
x_max=max(dst[0][0][0],dst[1][0][0],dst[2][0][0],dst[3][0][0])
y_min=min(dst[0][0][1],dst[1][0][1],dst[2][0][1],dst[3][0][1])
y_max=max(dst[0][0][1],dst[1][0][1],dst[2][0][1],dst[3][0][1])

new_pts=np.float32([ [[x_min,y_min]],[[x_min,y_max]],[[x_max,y_max]],[[x_max,y_min]] ])
img2 = cv2.polylines(img2,[np.int32(new_pts)],True,255,3, cv2.LINE_AA)

#img2 = cv2.polylines(img2,[np.int32(dst)],True,(0,0,255),3, cv2.LINE_AA)

# 정상치 매칭만 그리기 ---⑦
matchesMask = mask.ravel().tolist()
res2 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                    matchesMask = matchesMask,
                    flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
# 모든 매칭점과 정상치 비율 ---⑧
accuracy=float(mask.sum()) / mask.size
print("accuracy: %d/%d(%.2f%%)"% (mask.sum(), mask.size, accuracy))

# 결과 출력
cv2.imshow('Matching-All', res1)
cv2.imshow('Matching-Inlier ', res2)
cv2.waitKey()
cv2.destroyAllWindows()