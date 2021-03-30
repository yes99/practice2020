import cv2
import numpy as np

img = cv2.imread('nn1.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# FASt 특징 검출기 생성 ---①
fast = cv2.FastFeatureDetector_create(50)
# 특징점 검출 ---②
keypoints = fast.detect(gray, None)
# 특징점 그리기 ---③
img = cv2.drawKeypoints(img, keypoints, None)
# 결과 출력 ---④
cv2.imshow('FAST1', img)


img = cv2.imread('nn3.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# FASt 특징 검출기 생성 ---①
fast = cv2.FastFeatureDetector_create(50)
# 특징점 검출 ---②
keypoints = fast.detect(gray, None)
# 특징점 그리기 ---③
img = cv2.drawKeypoints(img, keypoints, None)
# 결과 출력 ---④
cv2.imshow('FAST2', img)
cv2.waitKey()
cv2.destroyAllWindows()