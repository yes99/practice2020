import cv2
import numpy as np
import math

black = (0,0,0)
img = cv2.imread('circle.png', cv2.COLOR_BGR2GRAY)
img2 = cv2.imread('circle2.png', cv2.COLOR_BGR2GRAY)
h,w,c = img.shape
h2,w2,c2 = img2.shape

print(h , w , c)
print(h2 , w2 , c2)


img = cv2.resize(img, (864 ,496 )) 
img2 = cv2.resize(img2, (864 ,496)) 



gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

Z= np.pad(gray, pad_width=10, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=10, mode='constant', constant_values=0)



h,w,c = img.shape
h2,w2,c2 = img2.shape



#정상적으로 출력되는지 확인

gray1 = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)



#cv2.imshow('image1',gray1)
#cv2.imshow('image2',gray2)

'''
for i in range(0,3):
    for j in range (0,3):
        print(i, j, end= '  ')
    print("\n")
'''
arr = np.ones((10,10), int)
arr2 = np.ones((10,10), int)
arr2x = np.ones((10,10), int)
arr2y = np.ones((10,10), int)
dx = np.ones((10,10), int)
dy = np.ones((10,10), int)
dt = np.ones((10,10), int)

A = np.ones((100,2), int)
B = np.ones((100,1), int)
At= np.ones((2,100), int)
AtA = np.ones((2,2), int)
As = At= np.ones((2,100), int)
R = np.ones((2,2), int)
uv = np.ones((2,1), int)

print(arr - 10)

x = np.array([[5, 4, 3, 2, 1], 
            [2 ,-5, 10, -5 ,-30]])

y = np.array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11],
       [12, 13, 14, 15],
       [16, 17, 18, 19]])

print(x)
print(x.max())
print(x.min())
print(x.argmax())
y - 10
print(np.argmax(y) // 4, np.argmax(y)%4)




