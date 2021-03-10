from __future__ import division
import cv2
import numpy as np

img1 = cv2.imread("kei.jpg")

img2 = cv2.cvtColor(img1,cv2.COLOR_BGR2YCR_CB)

y,cr,cb = cv2.split(img2)

    #y = cv2.equalizeHist(y)

x =y
height,width = y.shape

hist = [0]*256
pmf = [0]*256
cdf = [0]*256
levelBaru = [0]*256

cv2.imshow("y before",x)
cv2.waitKey(0)

for i in range(0,height):  
    for j in range(0,width):
        hist[y.item(i,j)] += 1 
        #hist[y[i,j]] += 1

for i in range(0,256):  
    #cari pmf
    pmf[i] = round(hist[i]/(height*width),4)

#print "pmf  done"

cdf[0] = pmf[0]

for i in range(1,256):              #cari cdf
    cdf[i] = cdf[i-1]+pmf[i]

for i in range(1,256):              #cari levelBaru
    levelBaru[i] = int(cdf[i]*255)

for i in range(0,height):           #baru
    for j in range(0,width):
        for k in range (0,256):
            if(y.item(i,j)==k):
                #print i," ",levelBaru[i]
                y.itemset((i,j),levelBaru[k])

img2 = cv2.merge((y,cr,cb))
img2 = cv2.cvtColor(img2,cv2.COLOR_YCR_CB2BGR) #supaya ga error pas di stack


    #cv2.namedWindow('result', cv2.WINDOW_NORMAL)
cv2.imshow('result',img2)

cv2.waitKey(0)
cv2.destroyAllWindows