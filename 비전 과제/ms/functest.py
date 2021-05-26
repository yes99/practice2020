import cv2
import numpy as np
import math
import time

def euclidean_dist0(pointA, pointB):
    if(len(pointA) != len(pointB)):
        raise Exception("point dimensionality is not matched!")
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension] - pointB[dimension])**2
    dist = math.sqrt(total)
    return dist


def euc_d(pointA, pointB ,h):
    if(len(pointA) != len(pointB)):
        raise Exception("point dimensionality is not matched!")
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension]/h - pointB[dimension]/h)**2
    return total


def gaussian_k0 (x_point, y_point, h):  #x점(좌표 아님), y중심 점(좌표 아님), 커널의 크기
    e= math.pi
    l2 = abs((x_point - y_point)/h)
    #print ("l2는", l2)
    if (l2/h) <=1:
        return e**(-l2)
    else :
        return 0


def gaussian_k(l2):
    e= math.pi
    #print ("l2는", l2)
    if math.sqrt(l2) <=1:
        return e**(-l2)
    else:
        return 0


print("============================================")

# 찐 거리 루트까지  euclidean_dist0
# 거리 제곱         euc_d
print(euc_d([0,1,3], [2,3,4], 1))
print(euc_d([0,1,3], [2,3,4], 5))
print("============================================")
print(math.sqrt(euc_d([0,1,3], [2,3,4], 1)))
print(math.sqrt(euc_d([0,1,3], [2,3,4], 5)))
print("============================================")
print(gaussian_k(euc_d([0,1,3], [2,3,4], 1)))
print(gaussian_k(euc_d([0,1,3], [2,3,4], 5)))
print("============================================")
print(euclidean_dist0([0,1], [2,3]))
print(euclidean_dist0([0/5,1/5], [2/5,3/5]))
print("============================================")



a = [ [1,2,3,4,5],[6,7,8,9,10] ,[11,12,13,14,15],]
b= []
print(a[0][0])
print(a[1][1])
print(a[2][3])
b.append(100)
b.append(101)
b.append(102)
b.append(103)
b.append(104)
a.append(b)
print(a[3][0])
print(a[3][1])
print(a[3][2])