import cv2
import numpy as np
import math
import time

img = cv2.imread( 'test1.png', cv2.COLOR_BGR2GRAY)
h,w,c = img.shape

print(h,w)
cv2.imshow('img0', img)

img = cv2.resize(img, (w//2 ,h//2)) 
h,w,c = img.shape
print(h,w)

cv2.imshow('img1', img)

img = cv2.resize(img, (w//4 ,h//4)) 
h,w,c = img.shape
print(h,w)
cv2.imshow('img2', img)
cv2.imwrite('img2.png', img)



cv2.waitKey(0)
cv2.destroyAllWindows()
