import cv2
import numpy as np
import math




img = cv2.imread('meantest.png', cv2.IMREAD_COLOR)

h,w,c = img.shape
print(h , w , c)

img = cv2.resize(img, (216 ,135 )) 
h,w,c = img.shape

print(h , w , c)


gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)



print(gray)
a = []

Z= np.pad(gray, pad_width=3, mode='constant', constant_values=0)


print(Z)
"""
for i in range (1, h):
    for j in range(1, w):        
        if(gray[i][j] != 255):
            print("#", end= ' ')
            a.append(gray[i][j])
        else:
            print(gray[i][j], end= ' ')

    print("\n")    
"""
b = set(a)
a = list(b)

print(a)
a.sort()
print(a)
print(len(a))
#for i in a:
#    print(a[i])

#정상적으로 출력되는지 확인
#cv2.imshow('image1',img)
#cv2.imshow('image2',gray)
cv2.imshow('pad', Z)

cv2.waitKey(0)
cv2.destroyAllWindows()