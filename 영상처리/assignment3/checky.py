import numpy as np
import cv2

 
img = cv2.imread('dgu_night_color.png',cv2.IMREAD_COLOR)
#cv2.imshow("color", img)
b,g,r = cv2.split(img)

print("r")
print(r)
print("g")
print(g)
print("b")
print(b)

height,width, channel=img.shape
Y = np.empty([img.shape[0],img.shape[1]], dtype = float)

for i in range(height):
    for j in range(width):
        #Y[i,j] = (0.299)*(img[i,j][2]) + (0.587)*(img[i,j][1]) + (0.114)*(img[i,j][0])
        Y[i,j] = (0.257)*(r[i,j]) +(0.504)*(b[i,j]) +(0.098)*(g[i,j]) +16
print("Y")
print(Y)
"""
print("Y")
for i in range(height):
    for j in range(width):
        print (Y[i,j])
"""
"""        
zeros = np.zeros((img.shape[0],img.shape[1]),dtype="uint8")
img_b = cv2.merge([img_b,zeros,zeros])
img_g = cv2.merge([zeros,img_g,zeros])
img_r = cv2.merge([zeros,zeros,img_r])

cv2.imshow("color", img)
cv2.imshow("b",img_b)
cv2.imshow("g", img_g)
cv2.imshow("r", img_r)
print(height)
print(width)
"""

cv2.waitKey(0)

cv2.destroyAllWindows()
