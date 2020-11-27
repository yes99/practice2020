import cv2
import numpy as np
import math

def rgb_to_ycrbr(image):
    img = (image.astype(float)/255)
    YCbCr_img = np.empty((img.shape[0], img.shape[1], 3), float)
    Y = np.empty([img.shape[0],img.shape[1]], dtype = float)
    Cb = np.empty([img.shape[0],img.shape[1]], dtype = float)
    Cr = np.empty([img.shape[0],img.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            Y[i,j] = (0.299)*(img[i,j][2]) + (0.587)*(img[i,j][1]) + (0.114)*(img[i,j][0])
            Cb[i,j] = (-0.1687)*(img[i,j][2]) + (-0.3313)*(img[i,j][1]) + (0.5)*(img[i,j][0])
            Cr[i,j] = (0.5)*(img[i,j][2]) + (-0.4187)*(img[i,j][1]) + (-0.0813)*(img[i,j][0])
    Y = histogram_equalize(Y*255)
    YCbCr_img[...,0] = Cr*255
    YCbCr_img[...,1] = Cb*255
    YCbCr_img[...,2] = Y
    return YCbCr_img

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
    cv2.imwrite('HEQ1_mandrill.png', new_img)
    return new_img

def ycrbr_to_rgb(image):
    img = (image.astype(float)/255)
    RGB_img = np.empty((img.shape[0], img.shape[1], 3), float)
    r = np.empty([img.shape[0],img.shape[1]], dtype = float)
    g = np.empty([img.shape[0],img.shape[1]], dtype = float)
    b = np.empty([img.shape[0],img.shape[1]], dtype = float)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            r[i,j] = (1)*(img[i,j][2]) + (0)*(img[i,j][1]) + (1.402)*(img[i,j][0])
            g[i,j] = (1)*(img[i,j][2]) + (-0.34414)*(img[i,j][1]) + (-0.71414)*(img[i,j][0])
            b[i,j] = (1)*(img[i,j][2]) + (1.772)*(img[i,j][1]) + (0)*(img[i,j][0])
    #img_new = cv2.merge((b*255, g*255, r*255))
    RGB_img[...,0] = b*255
    RGB_img[...,1] = g*255
    RGB_img[...,2] = r*255
    return RGB_img

input_image = cv2.imread('dgu_night_color.png', 1)
ycrbr = rgb_to_ycrbr(input_image)
cv2.imwrite('HEQ_YCrBr_mandrill.png', ycrbr)
out_image = np.zeros((input_image.shape[0], input_image.shape[1], 3), float)
out_image = ycrbr_to_rgb(ycrbr)

cv2.imwrite('HEQ2_mandrill.png', out_image)