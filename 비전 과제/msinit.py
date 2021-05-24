import cv2
import numpy as np
import math

black = (0,0,0)
img = cv2.imread('shifttest.png', cv2.COLOR_BGR2GRAY)
draw = cv2.imread('shifttest.png', cv2.IMREAD_COLOR)
height,width,c = img.shape
print(height,width , c)

img = cv2.resize(img, (864 ,496 )) 
draw = cv2.resize(draw, (864 ,496 )) 

height,width,c = img.shape
print(height,width , c)
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#Z= np.pad(gray, pad_width=10, mode='constant', constant_values=0)



def euclidean_dist(pointA, pointB):
    if(len(pointA) != len(pointB)):
        raise Exception("point dimensionality is not matched!")
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension] - pointB[dimension])**2
    dist = math.sqrt(total)
    return dist




def gaussian_kernel(distance, bandwidth):
    euclidean_distance = np.sqrt(((distance)**2).sum(axis=1))
    print("dd", euclidean_distance)
    gaussian_val = (1/(bandwidth*math.sqrt(2*math.pi))) * np.exp(-0.5*((euclidean_distance / bandwidth))**2)
    return gaussian_val

def gaussian_k (x_point, y_point, h):  #x점(좌표 아님), y중심 점(좌표 아님), 커널의 크기
    e= math.pi
    l2 = abs((x_point - y_point)/h)
    #print ("l2는", l2)
    if (l2/h) <=1:
        return e**(-l2)
    else :
        return 0





def multivariate_gaussian_kernel(distances, bandwidths):
    # Number of dimensions of the multivariate gaussian
    dim = len(bandwidths)

    # Covariance matrix
    cov = np.multiply(np.power(bandwidths, 2), np.eye(dim))

    # Compute Multivariate gaussian (vectorized implementation)
    exponent = -0.5 * np.sum(np.multiply(np.dot(distances, np.linalg.inv(cov)), distances), axis=1)
    multi_gaussian_val = (1 / np.power((2 * math.pi), (dim/2)) * np.power(np.linalg.det(cov), 0.5)) * np.exp(exponent)

    return multi_gaussian_val


######################테스트####################
print("정상적으로 출력되는지 확인")
arr = np.zeros((5,5), float)
#print(gaussian_kernel(arr,2))
#print(euclidean_dist([0,0], [3,4]))
print(gaussian_k(2,5,2))
print(gaussian_k(1,3,5))
arr = np.ones((10,10), int)
arr2 = np.ones((10,10), int)
print(img[10][10])
################################################

#######xside h 는 반지름이라고 생각하면 될듯
sumx = 0
x= []
y= []
h = 10
former1 = 0
former2 = 0
yt1 = 10000
yt2 = 10000
cnt = 0
for i in range(1, height-h-1):
    for j in range(1, width-h-1):
        former1 = 0
        former2 = 0
        yt1 = 10000
        yt2 = 10000
        #print("img[][]", img[i][j])
        if img[i][j] != 255:
            y1 = img[i][j]
            yt1 = j
            yt2 = i
            formerlist = [yt1, yt2]
            while(True):
                former1 = yt1
                former2 = yt2
                formerlist = [yt1, yt2]
                """
                if euclidean_dist(formerlist, [yt1, yt2]) <1:
                    x.append(yt1)
                    y.append(yt2)
                    #print("통과")
                    cv2.circle(draw, (yt1, yt2), 1, black , 1)
                    cv2.imwrite( "im/frame%d.png"%cnt, draw)
                    cnt= cnt +1
                    break
                """
                upsumx = 0
                downsumx = 0
                upsumy = 0
                downsumy = 0
                for l in range (-10, 11):
                    for z in range (-10, 11):
                        if img[i-l][j-z] != 255 :
                            upsumx = upsumx + (j-z)* gaussian_k(j-z,j,3) #x, y, h
                            downsumx = downsumx + gaussian_k(j-z,j,3)
                            upsumy = upsumy + (i-l)* gaussian_k(i-1,i,3) #x, y, h
                            downsumy = downsumy + gaussian_k(i-1,i,3)
                yt1 = upsumx / downsumx
                yt2 = upsumy / downsumy
                if euclidean_dist(formerlist, [yt1, yt2]) <1:
                    x.append(yt1)
                    y.append(yt2)
                    #print("통과")
                    cv2.circle(draw, (int(yt1), int(yt2)), 1, black , 1)
                    cv2.imwrite( "im/frame%d.png"%cnt, draw)
                    cnt= cnt +1
                    break
        
        
        #print(i , j ,yt1, yt2)
        #print("=============================")

                

                        
print("=============================") 
print("=============================")                  
print(x)
print("=============================")
print("=============================")
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

