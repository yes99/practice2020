import numpy as np
import cv2


img = cv2.imread('dgu_night_color.png',cv2.IMREAD_COLOR)
#cv2.imshow("color", img)
img_b,img_g,img_r = cv2.split(img)

height,width, channel=img.shape

zeros = np.zeros((img.shape[0],img.shape[1]),dtype=np.float64)
hisR = np.zeros((256,),dtype=np.uint8)
hisY = np.zeros((256,),dtype=np.float64)
calY = np.zeros((256,),dtype=np.uint8)


"""
img_b = cv2.merge([img_b,zeros,zeros])
img_g = cv2.merge([zeros,img_g,zeros])
img_r = cv2.merge([zeros,zeros,img_r])

cv2.imshow("color", img)
cv2.imshow("b",img_b)
cv2.imshow("g", img_g)
cv2.imshow("r", img_r)
"""
#cv2.imshow("color", img)
print(height)
print(width)

for i in range(width):
    for j in range(height):
        hY = 0.257 * img_r[j,i] + 0.504*img_g[j,i] + 0.098*img_b[j,i]+16
        ihY = int(hY)
        hisY[ihY] = hisY[ihY]+1
        

for i in range(256):
    for j in range(i+1):
        calY[i] += hisY[j]
#print(calY)


for i in range(256):
    calY[i] = calY[i] * (1.0/(height*width))    
#print(calY)

#max - min 을 곱해준다
for i in range(256):
    calY[i] = round(calY[i] * 255)
#print(calY)

#변환된 히스토그램을 해당 변환된 값으로 변환해주어서 img에 넣는다
for i in range(width):
    for j in range(height):
        his = img[j,i]
        img[j,i]= calY[his]

cv2.imshow('image',img)

cv2.waitKey(0)

cv2.destroyAllWindows()
