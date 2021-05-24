import cv2
import numpy as np
import math

black = (0,0,0)
img = cv2.imread('ms1.png', cv2.COLOR_BGR2GRAY)
draw = cv2.imread('ms1.png', cv2.IMREAD_COLOR)
height,width,c = img.shape
print(height,width , c)

img = cv2.resize(img, (400 ,200 )) 
draw = cv2.resize(draw, (400 ,200 )) 

height,width,c = img.shape
print(height,width , c)
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#Z= np.pad(gray, pad_width=10, mode='constant', constant_values=0)
f= open("spacelog.txt", 'w')


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


def gaussian_kernel(distance, bandwidth):
    euclidean_distance = np.sqrt(((distance)**2).sum(axis=1))
    print("dd", euclidean_distance)
    gaussian_val = (1/(bandwidth*math.sqrt(2*math.pi))) * np.exp(-0.5*((euclidean_distance / bandwidth))**2)
    return gaussian_val

def gaussian_k0 (x_point, y_point, h):  #x점(좌표 아님), y중심 점(좌표 아님), 커널의 크기
    e= math.pi
    l2 = abs((x_point - y_point)/h)
    #print ("l2는", l2)
    if (l2/h) <=1:
        return e**(-l2)
    else :
        return 0

def gaussian_k(l2):  #x점(좌표 아님), y중심 점(좌표 아님), 커널의 크기
    e= math.pi
    #print ("l2는", l2)
    if (l2) <=1:
        return e**(-l2)
    else:
        return 0



"""
def multivariate_gaussian_kernel(distances, bandwidths):
    # Number of dimensions of the multivariate gaussian
    dim = len(bandwidths)

    # Covariance matrix
    cov = np.multiply(np.power(bandwidths, 2), np.eye(dim))

    # Compute Multivariate gaussian (vectorized implementation)
    exponent = -0.5 * np.sum(np.multiply(np.dot(distances, np.linalg.inv(cov)), distances), axis=1)
    multi_gaussian_val = (1 / np.power((2 * math.pi), (dim/2)) * np.power(np.linalg.det(cov), 0.5)) * np.exp(exponent)

    return multi_gaussian_val
"""

######################테스트####################
print("정상적으로 출력되는지 확인")
arr = np.zeros((5,5), float)
#print(gaussian_kernel(arr,2))
#(0,0,0) (3,4,5) h=3
print("그냥",euc_d([0,0,0], [3,4,5] ,3 ))
#print((euc_d([0,0,0], [1/3,2/3,1/3], 1  )  ))
#print((euc_d([0,0,0], [1,2,1])/3, 1))
#print((euc_d([0,0,0], [1,2,1])/9))
print("exp",  gaussian_k(   euc_d([0,0,0], [1,2,1], 3) ) )



#print(gaussian_k(2,5,2))
#print(gaussian_k(1,3,5))
arr = np.ones((10,10), int)
arr2 = np.ones((10,10), int)
#print(img[10][10])
################################################

#######xside h 는 반지름이라고 생각하면 될듯
sumx = 0
x= []
y= []
h = 10
formeri = 10000
formerj = 10000
yt1 = 10000
yt2 = 10000
cnt = 0
for i in range(h, height-h-1):
    for j in range(h, width-h-1):
        former1 = 0
        former2 = 0
        y0i = i
        y0j = j
        upsumx   = 0
        downsumx = 0
        upsumy   = 0
        downsumy = 0
        log1 = "i = %d j = %d에서\n" %(i, j)
        f.write(log1)
        while(True):
              
            for l in range (-h, h+1):
                    for z in range (-h, h+1):
                        #print("exp",  gaussian_k(euc_d([0,0,0], [1,2,1], 3)))
                        k = gaussian_k( euc_d([i+l, j+z],[i , j],h) )

                        upsumx   = upsumx + (j+z) * k #x, y, h
                        downsumx = downsumx +  k
                        upsumy   = upsumy + (i+l)*  k #x, y, h  
                        downsumy = downsumy + k
            yi = round(upsumy/downsumy)
            yj = round(upsumx/downsumx)

            if(euclidean_dist0([yj,yi], [y0j, y0i]) < 1):
                x.append(y0j)
                y.append(y0i)
                log2 = "i = %d j = %d 결정\n" %(y0i, y0j)
                f.write(log2)
                break
            else:
                y0j = yj
                y0i = yi
                log3 = "i = %d j = %d 아직 더\n" %(y0i, y0j)
                f.write(log3)
                

print(x)
print(y)






                

"""
for i in range(1, len(x)):
    cv2.circle(draw, (x[i], y[i]), 1, black , 1)
print(len(x))
"""
#cv2.imshow('image1',gray1)
#cv2.imshow('image2',gray2)






cv2.imshow('img', draw)
cv2.imwrite('img.png', draw)

cv2.waitKey(0)
cv2.destroyAllWindows()

