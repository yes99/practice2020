import numpy as np
import cv2
import math


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
    #cv2.imwrite('HEQ1_mandrill.png', new_img)
    return new_img


img = cv2.imread('dgu_night_color.png',cv2.IMREAD_COLOR)
img2 = cv2.imread('dgu_night_color.png',cv2.IMREAD_COLOR)

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
histogram_equalize(Y)
print("his Y")
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
