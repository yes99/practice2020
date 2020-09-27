import cv2
import numpy as np


def transform(img, angle):  # forward transformation
    height, width = img.shape
    result = np.zeros((height, width), np.uint8)  # result image

    affine = np.array([[np.cos(np.radians(angle)), -np.sin(np.radians(angle)), 0],
                       [np.sin(np.radians(angle)), np.cos(np.radians(angle)), 0],
                       [0, 0, 1]])  # Affine transformation matrix

    for x in range(width):
        for y in range(height):
            p = affine.dot(np.array([x, y, 1]))

            xp = int(p[0])
            yp = int(p[1])

            if 0 <= yp < height and 0 <= xp < width:
                result[yp, xp] = img[y, x]
    return result



def transform2(img, angle):  # backward transformation
    height, width = img.shape
    result2 =  np.zeros((height, width), np.uint8) # result image

    affine = np.array([[np.cos(np.radians(angle)), np.sin(np.radians(angle)), 0],
                       [-np.sin(np.radians(angle)), np.cos(np.radians(angle)), 0],
                       [0, 0, 1]])  # Affine transformation matrix
    
    for x in range(width):
        for y in range(height):
            p = affine.dot(np.array([x, y, 1]))

            xp = int(p[0])
            yp = int(p[1])
            if 0 <= yp < height and 0 <= xp < width:
                result2[y, x] = img[yp, xp]

    return result2

def implement(img1, img2):
    height, width = img1.shape
    finalresult = np.zeros((height, width), np.uint8)
    for x in range(width):
        for y in range(height):
            if(img1[y, x] == 0):
                img1[y, x] = img2[y,x]
            if 0 <= y < height and 0 <= x < width:
                finalresult[y,x] = img1[y,x]
    return finalresult




in_image = cv2.imread('kei.png', 0)  # img2numpy
cv2.imshow('Input Image', in_image)
out_image = transform(in_image, 20)
imple_image = transform2(in_image,20)
#sample = transform(out_image,-20)

cv2.imshow('Result Image', out_image)
cv2.imshow('imple image', imple_image)

cv2.imwrite('Kei.png', out_image)  # save result img
cv2.waitKey()
