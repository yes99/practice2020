import cv2
import numpy as np
import math

def rgb_to_ycrbr1(image):
    img = (image.astype(float))
    b,g,r = cv2.split(img)
    YCbCr_img = np.empty((img.shape[0], img.shape[1], 3), float)
    Y = np.empty([img.shape[0],img.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            Y[i,j] = (0.257)*(r[i,j]) + (0.504)*(g[i,j]) + (0.098)*(b[i,j]) +16
    print("히스토그램 검토")
    print(Y)
    Y = histogram_equalize(Y)
    YCbCr_img = Y
    return YCbCr_img

def originalY(image):
    b,g,r = cv2.split(image)
    YCbCr_img = np.empty((image.shape[0], image.shape[1]), float)
    Y = np.empty([image.shape[0],image.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            Y[i,j] = math.ceil((0.257)*(r[i,j]) +(0.504)*(g[i,j]) +(0.098)*(b[i,j]) +16)
    return Y

def histogram_equalize(img):
    image = np.asarray(img, dtype=float)

    # height, width : 세로, 가로 길이
    # ints_array는 histgoram 값을 저장하는 배열. 0~255 중 ints값에 해당하는 부분 +1
    ints_array = np.zeros(256)
    height, width = image.shape[:2]
    for i in range(0, height):
        for j in range(0, width):
            ints = (image[i, j]) #반올림 미리 해주자 , y값들은 일단 다 소수이기때문에
            ints = math.ceil(ints)
            image[i, j] = ints
            ints_array[ints] = ints_array[ints] + 1

    #MN = 0
    #for i in range(0, 256):
    #    MN = MN + ints_array[i]
    #print(MN)
    print(height*width)
    # 0~255 각 값이 이미지 내에 등장할 확률을 계산 (히스토그램값 / 전체넓이)
    array_pdf = ints_array / (height*width)

    # cdf의 초깃값은 array_pdf로 먼저 초기화 한 뒤 (cdf[1] = cdf[0] + cdf[1]) -> (cdf[2] = cdf[1] + cdf[2]) -> ...
    CDF = 0
    CDF_accu = np.zeros(256)
    for i in range(256):
        CDF = CDF + array_pdf[i]
        CDF_accu[i] = CDF

    # 결과 gray level을 구한다. => complete_his_array 
    complete_his_array = np.zeros(256)
    complete_his_array = (CDF_accu * 255)
    for i in range(256):
        complete_his_array[i] = math.ceil(complete_his_array[i])
        if (complete_his_array[i] > 255):
            complete_his_array[i] = 255

    # output histogram p(s) => finalimg(complete_his_array)
    finalimg = np.zeros(img.shape)
    for i in range(0, height):
        for j in range(0, width):
            for value in range(0, 255): #value를 한바뀌 쭉 돌면서 맞는거가 있나 찾는과정, 맞는거는 분명히 있게 설계된다
                if (image[i, j] == value):
                    finalimg[i, j] = complete_his_array[value]
                    break

    cv2.imwrite('histogram_equalize.png', finalimg)
    return finalimg



def rgb_to_y(image):
    img = (image.astype(float)/255)
    b,g,r = cv2.split(img)
    YCbCr_img = np.empty((img.shape[0], img.shape[1]), float)
    Y = np.empty([img.shape[0],img.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            Y[i,j] = (0.299)*(r[i,j]) + (0.587)*(g[i,j]) + (0.114)*(b[i,j])
    originY = Y

    return originY





input_image = cv2.imread('car.png', cv2.IMREAD_COLOR)
hisy = rgb_to_ycrbr1(input_image)
#cv2.imwrite('HEQ_Y_dgu.png', ycrbr)
oriy = originalY(input_image)
s = 0.8
b,g,r = cv2.split(input_image)
print("원래Y")
#print(oriy)
print("히스토그램 평활된 Y")
#print(hisy)


ior = np.empty([input_image.shape[0],input_image.shape[1]], dtype = float)
iog = np.empty([input_image.shape[0],input_image.shape[1]], dtype = float)
iob = np.empty([input_image.shape[0],input_image.shape[1]], dtype = float)


###
for i in range(input_image.shape[0]):
    for j in range(input_image.shape[1]):
        ior[i,j]= int(hisy[i,j]*((r[i,j]/oriy[i,j])**s)) 
        iog[i,j]= int(hisy[i,j]*((g[i,j]/oriy[i,j])**s))
        iob[i,j]= int(hisy[i,j]*((b[i,j]/oriy[i,j])**s))
"""
print(ior)
print(iog)
print(iob)
"""

merge = cv2.merge([iob,iog,ior])

#cv2.imshow("ior",ior)
#cv2.imshow("iog",iog)
#cv2.imshow("iob",iob)
#print(merge)
cv2.imwrite('final_dgu.png', merge)

cv2.waitKey(0)
cv2.destroyAllWindows()












"""

ior = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
iog = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
iob = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
"""