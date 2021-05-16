import cv2
import numpy as np
import math


img = cv2.imread('meantest.png', cv2.IMREAD_COLOR)

h,w,c = img.shape
print(h , w , c)

img = cv2.resize(img, (216 ,135 )) 
h,w,c = img.shape

print(h , w , c)

print("이미지 출력", img[0][0])


a = [[255,255,255]]


for i in range (1, h):
    for j in range(1, w):        
        
            


print(len(a))
print(a[1][0], a[1][1], a[1][2])



for i in range(0, len(b)):
    print(b[i], i)


#정상적으로 출력되는지 확인
cv2.imshow('image1',img)







cv2.waitKey(0)
cv2.destroyAllWindows()