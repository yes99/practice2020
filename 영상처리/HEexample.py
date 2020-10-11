import cv2 as cv
import numpy as np


bins = np.arange(256).reshape(256,1)


def draw_histogram(img):

    h = np.zeros((img.shape[0], 256), dtype=np.uint8)

    hist_item = cv.calcHist([img],[0],None,[256],[0,256])
    cv.normalize(hist_item,hist_item,0,255,cv.NORM_MINMAX)
    hist=np.int32(np.around(hist_item))
    for x,y in enumerate(hist):
        cv.line(h,(x,0+10),(x,y+10),(255,255,255))

    cv.line(h, (0, 0 + 10), (0, 5), (255, 255, 255) )
    cv.line(h, (255, 0 + 10), (255, 5), (255, 255, 255))
    y = np.flipud(h)

    return y


img = cv.imread('cat.jpg', cv.IMREAD_COLOR)
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)


line =  draw_histogram(gray)
result1 = np.hstack((gray, line))
cv.imshow('result1', result1)


cv.waitKey(0)
cv.destroyAllWindows()