import cv2
import numpy as np
import math

def rgb_to_ycrbr(image):
    img = (image.astype(float)/255)
    YCbCr_img = np.empty((img.shape[0], img.shape[1], 3), float)
    Y = np.empty([img.shape[0],img.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            Y[i,j] = (0.299)*(img[i,j][2]) + (0.587)*(img[i,j][1]) + (0.114)*(img[i,j][0])
    Y = histogram_equalize(Y*255)
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

    ints_array = np.zeros(256)
    x_axis, y_axis = image.shape[:2]
    for i in range(0, x_axis):
        for j in range(0, y_axis):
            ints = (image[i, j]) #round up because input is of type float
            ints = math.ceil(ints)
            image[i, j] = ints
            ints_array[ints] = ints_array[ints] + 1

    MN = 0
    for i in range(1, 256):
        MN = MN + ints_array[i]

    array_pdf = ints_array / MN

    CDF = 0
    CDF_matrix = np.zeros(256)
    for i in range(1, 256):
        CDF = CDF + array_pdf[i]
        CDF_matrix[i] = CDF

    final_array = np.zeros(256)
    final_array = (CDF_matrix * 255)
    for i in range(1, 256):
        final_array[i] = math.ceil(final_array[i])
        if (final_array[i] > 255):
            final_array[i] = 255

    new_img = np.zeros(img.shape)
    for i in range(0, x_axis):
        for j in range(0, y_axis):
            for value in range(0, 255):
                if (image[i, j] == value):
                    new_img[i, j] = final_array[value]
                    break
    #cv2.imwrite('aaaa.png', new_img)
    return new_img


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





input_image = cv2.imread('dgu_night_color.png', cv2.IMREAD_COLOR)
hisy = rgb_to_ycrbr(input_image)
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
cv2.imwrite('Hdfdfdfdf.png', merge)
cv2.waitKey(0)
cv2.destroyAllWindows()












"""

ior = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
iog = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
iob = np.empty([input_image.shape[0],input_image.shape[1]], np.uint8)
"""