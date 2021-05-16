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
        if(img[i][j][0] != 255 and img[i][j][1] != 255 and img[i][j][2] != 255):            
            a.append(img[i][j])
            


print(len(a))
print(a[1][0], a[1][1], a[1][2])
#myset = set(a)
#a = list(myset)
b = [[255,255,255]]

cnt = 0
flag = 0
for v in a:
    print(v[0],v[1],v[2])
    for i in range(len(b)):
        #print("dd",b)
        if v[0] == b[i][0] and v[1] == b[i][1] and v[2] == b[i][2]:
            flag = 1
            #cnt = cnt +1
            #print("추가", cnt)
    if flag == 1:
        flag =0
    else:
        b.append(v)

for i in range(0, len(b)):
    print(b[i], i)

#for i in a:
#    print(a[i])

#정상적으로 출력되는지 확인
cv2.imshow('image1',img)







cv2.waitKey(0)
cv2.destroyAllWindows()