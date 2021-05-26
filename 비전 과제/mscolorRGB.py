import cv2
import numpy as np
import math

black = (0,0,0)
img = cv2.imread( 'ms1.png', cv2.COLOR_BGR2GRAY)
draw = cv2.imread('ms1.png', cv2.IMREAD_COLOR)
height,width,c = img.shape
print(height,width , c)

#img = cv2.resize(img, (864 ,496 )) 
#draw = cv2.resize(draw, (864 ,496 )) 
#img = cv2.resize(img, (432 ,248 )) 
#draw = cv2.resize(draw, (432 ,248 )) 

height,width,c = img.shape
print(height,width , c)
#Z= np.pad(gray, pad_width=10, mode='constant', constant_values=0)
(B, G, R) = cv2.split(draw)
(dB, dG, dR) = cv2.split(draw)
merged = cv2.merge([B, G, R])
f = open("spacelog.txt", 'w')
status = "height %d width %d channel %d" %(height,width , c)


f.write(status)
#cv2.imshow("Red", R)
#cv2.imshow("Green", G)
#cv2.imshow("Blue", B)

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
def gaussian_krgb(a,b,h):  #x점(좌표 아님), y중심 점(좌표 아님), 커널의 크기
    e= math.pi
    l2 = abs((a-b)/h)
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
rr= []
gg= []
bb= []
h = 10
formeri = 10000
formerj = 10000
yt1 = 10000
yt2 = 10000
cnt = 0
arr = np.zeros((2*h+1,2*h+1), int)
hh = 2*h+1
repeatcnt = 0
#dB, dG, dR
R= np.pad(R, pad_width=10, mode='constant', constant_values=0)
G= np.pad(G, pad_width=10, mode='constant', constant_values=0)
B= np.pad(B, pad_width=10, mode='constant', constant_values=0)
q,w = R.shape
print("크기 출력",q,w)
#print(R[1], R[0])

dR= np.pad(dR, pad_width=10, mode='constant', constant_values=0)
dG= np.pad(dG, pad_width=10, mode='constant', constant_values=0)
dB= np.pad(dB, pad_width=10, mode='constant', constant_values=0)
q,w = dR.shape
print("크기 출력",q,w)
dR = np.zeros((q,w), int)
dG = np.zeros((q,w), int)
dB = np.zeros((q,w), int)

cv2.waitKey(0)

for i in range(h+1, height-h-1):
    for j in range(h+1, width-h-1):
        origini = i
        originj = j
        #R
        yt = R[i,j]
        upsumx   = 0
        downsumx = 0
        log1 = "i = %d j = %d에서 원래 R = %d\n" %(i, j, yt)
        f.write(log1)
        while(True):
            print(i , j)
            for l in range (-h, h+1):
                    for z in range (-h, h+1):
                        #print(i+l, j+z , i ,j)
                        k = gaussian_krgb(R[i+l][j+z],R[i][j],h)
                        upsumx   = upsumx + R[i+1][j+z] * k #x, y, h
                        downsumx = downsumx +  k
                        arr[l+h][z+h] = R[i+l][j+z]               
            yr = round(upsumx/downsumx)
            print("가운데 값", yt)
            print("이번에 구한 값", yr)
            #print(arr)
            #print("=====================================")
            arr = abs(arr - yr)
            #print(arr)
            y0i = i - h + np.argmin(arr) // hh 
            y0j = j - h + np.argmin(arr)%hh
            print("최소값 위치",i - h + np.argmin(arr) // hh, j - h +np.argmin(arr)%hh)
            
            if( abs(yt - yr) < 5 or repeatcnt > 5):
                log2 = "i = %d j = %d yt:%d yr:%d        RED 결정\n" %(y0i, y0j, yt, yr)
                f.write(log2)
                i = origini
                j = originj
                repeatcnt = 0
                break
            else:
                i = y0i
                j = y0j
                log3 = "i = %d j = %d 아직 더  yt:%d yr:%d\n" %(y0i, y0j, yt, yr)
                f.write(log3)
                repeatcnt += 1
        
        
        
        #G
        yt = G[i,j]
        upsumx   = 0
        downsumx = 0
        log1 = "i = %d j = %d에서 원래 G = %d\n" %(i, j, yt)
        f.write(log1)
        while(True):
            print(i , j)
            for l in range (-h, h+1):
                    for z in range (-h, h+1):
                        #print(i+l, j+z , i ,j)
                        k = gaussian_krgb(G[i+l][j+z],G[i][j],h)
                        upsumx   = upsumx + G[i+1][j+z] * k #x, y, h
                        downsumx = downsumx +  k
                        arr[l+h][z+h] = G[i+l][j+z]               
            yg = round(upsumx/downsumx)
            print("가운데 값", yt)
            print("이번에 구한 값", yg)
            #print(arr)
            #print("=====================================")
            arr = abs(arr - yg)
            #print(arr)
            y0i = i - h + np.argmin(arr) // hh 
            y0j = j - h + np.argmin(arr)%hh
            print("최소값 위치",i - h + np.argmin(arr) // hh, j - h +np.argmin(arr)%hh)
            
            if( abs(yt - yr) < 5 or repeatcnt > 5):
                log2 = "i = %d j = %d yt:%d yg:%d        GREEN 결정\n" %(y0i, y0j, yt, yg)
                f.write(log2)
                i = origini
                j = originj
                repeatcnt = 0
                break
            else:
                i = y0i
                j = y0j
                log3 = "i = %d j = %d 아직 더  yt:%d yr:%d\n" %(y0i, y0j, yt, yg)
                f.write(log3)
                repeatcnt += 1
        
        
        #B
        yt = B[i,j]
        upsumx   = 0
        downsumx = 0
        log1 = "i = %d j = %d에서 원래 B = %d\n" %(i, j, yt)
        f.write(log1)
        while(True):
            print(i , j)
            for l in range (-h, h+1):
                    for z in range (-h, h+1):
                        #print(i+l, j+z , i ,j)
                        k = gaussian_krgb(B[i+l][j+z],B[i][j],h)
                        upsumx   = upsumx + B[i+1][j+z] * k #x, y, h
                        downsumx = downsumx +  k
                        arr[l+h][z+h] = B[i+l][j+z]               
            yb = round(upsumx/downsumx)
            print("가운데 값", yt)
            print("이번에 구한 값", yb)
            #print(arr)
            #print("=====================================")
            arr = abs(arr - yb)
            #print(arr)
            y0i = i - h + np.argmin(arr) // hh 
            y0j = j - h + np.argmin(arr)%hh
            print("최소값 위치",i - h + np.argmin(arr) // hh, j - h +np.argmin(arr)%hh)
            
            if( abs(yt - yb) < 5 or repeatcnt > 5):
                log2 = "i = %d j = %d yt:%d yb:%d        BLUE 결정\n" %(y0i, y0j, yt, yb)
                f.write(log2)
                i = origini
                j = originj
                repeatcnt = 0
                break
            else:
                i = y0i
                j = y0j
                log3 = "i = %d j = %d 아직 더  yt:%d yb:%d\n" %(y0i, y0j, yt, yb)
                f.write(log3)
                repeatcnt += 1
            
                

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

