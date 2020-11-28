import numpy as np
import cv2

img = cv2.imread('dgu_night_color.png',0)

#정상적으로 출력되는지 확인
cv2.imshow('image1',img)
#히스토그램을 긁어오는데 쓴다
histogram = np.zeros((256,),dtype=np.float64)
#구해온 히스토그램을 바탕으로 equalization 계산을 위해 쓴다 
cal = np.zeros((256,),dtype=np.float64)
#float16으로 하니까, 용량때문에 수치가 너무 커져서 64로 바꿔주니 정상으로 작동한다
height,width=img.shape
#현재 주어진 수치들을 확인한다.
print ("height = ", height)
print ("width  = ", width)
print("histogram")
print(histogram)
print("cal")
print(cal) 
print("image")
print(img)

#주어진 이미지를 바탕으로 히스토그램을 모두 하나씩 다 긁어온다
for i in range(width):
    for j in range(height):
        his = img[j,i]
        histogram[his] = histogram[his]+1

print("다시 A출력")
print(histogram)   

#누적으로 계산을 먼저 해주는 것이 좋다
for i in range(256):
    for j in range(i+1):
        cal[i] += histogram[j]
print(cal)
#총 픽셀수 만큼 나눠준다
for i in range(256):
    cal[i] = cal[i] * (1.0/(height*width))    
print(cal)
#max - min 을 곱해준다
for i in range(256):
    cal[i] = round(cal[i] * 255)
print(cal)

#변환된 히스토그램을 해당 변환된 값으로 변환해주어서 img에 넣는다
for i in range(width):
    for j in range(height):
        his = img[j,i]
        img[j,i]= cal[his]

cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()