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

#cv2.imshow("Red", R)
#cv2.imshow("Green", G)
#cv2.imshow("Blue", B)


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
    #print(x_point, y_point, h)

    l2 = abs((x_point - y_point)/h)
    #print("gogo")
    #print ("l2는", l2)
    if l2 <=1:
        return e**l2
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
f = open("log.txt", 'w')



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
print(height-h-2)
print(width-h-2)

for i in range(1, height-h-2):
    for j in range(1, width-h-2):
        #print("img[][]", img[i][j])
        y1 = img[i][j]
        yt1 = j  #y
        yt2 = i  #x
        ytr = R[i][j] 
        ytg = G[i][j]
        ytb = B[i][j]
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
            ###좌표
            upsumx = 0
            downsumx = 0
            upsumy = 0
            downsumy = 0
            ### RGB
            upsumr = 0
            downsumr = 0
            upsumg = 0
            downsumg = 0
            upsumb = 0
            downsumb = 0
            for l in range (-10, 11):
                for z in range (-10, 11):
                    ###  좌표
                    upsumx = upsumx + (j-z)* gaussian_k(j-z,j,3) #x, y, h
                    downsumx = downsumx + gaussian_k(j-z,j,3)
                    upsumy = upsumy + (i-l)* gaussian_k(i-1,i,3) #x, y, h
                    downsumy = downsumy + gaussian_k(i-1,i,3)
                    ###  RGB
                    upsumr = upsumr + R[i-l][j-z]* gaussian_k(R[i-l][j-z],R[i,j],3) #x, y, h
                    downsumr = downsumr + gaussian_k(R[i-l][j-z],R[i,j],3)
                    upsumg = upsumg + G[i-l][j-z]* gaussian_k(G[i-l][j-z],G[i,j],3) #x, y, h
                    downsumg = downsumg + gaussian_k(G[i-l][j-z],G[i,j],3)
                    upsumb = upsumb + B[i-l][j-z]* gaussian_k(B[i-l][j-z],B[i,j],3) #x, y, h
                    downsumb = downsumb + gaussian_k(B[i-l][j-z],B[i,j],3)
            yt1 = upsumx / downsumx
            yt2 = upsumy / downsumy
            ytr = upsumr / downsumr
            ytg = upsumg / downsumg
            ytb = upsumb / downsumb
            #print("yt1",yt1)
            #print("yt2",yt2)
            #print("ytr",ytr)
            #print("ytg",ytg)
            #print("ytb",ytb)
            #print(round(yt1),round(yt2),round(ytr),round(ytg),round(ytb))
            #
            ##print( round(yt1),round(yt2),round(ytg) , round(ytr) , round(\nytb))
            #print(i , j)
            log1 = "i %d, j %d, yt1 %d, yt2 %d, ytr %d, ytg %d, ytb%d\n" %( i, j ,round(yt1),round(yt2),round(ytg) , round(ytr) , round(ytb) )
            f.write(log1)
            if euclidean_dist(formerlist, [yt1, yt2]) <1:
                #x.append(yt1)
                #y.append(yt2)
                #print("통과")
                fpass = "통과\n"
                f.write(fpass)
                #cv2.circle(draw, (int(yt1), int(yt2)), 1, black , 1)
               #dG[round(yt2)][round(yt1)] = round(ytg)
               #dR[round(yt2)][round(yt1)] = round(ytr)
               #dB[round(yt2)][round(yt1)] = round(ytb)
                dG[i][j] = round(ytg)
                dR[i][j] = round(ytr)
                dB[i][j] = round(ytb)
                #cv2.imwrite( "im/frame%d.png"%cnt, draw)
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
cv2.imshow("Red", dR)
cv2.imshow("Green", dG)
cv2.imshow("Blue", dB)

merged = cv2.merge([dB, dG, dR])




cv2.imshow('mergeimg', merged)
cv2.imwrite('mergeimg.png', merged)

cv2.imshow('img', draw)
cv2.imwrite('img.png', draw)

cv2.waitKey(0)
cv2.destroyAllWindows()

