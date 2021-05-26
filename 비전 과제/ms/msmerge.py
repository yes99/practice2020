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

def largesearch0(y,x, center, h, recnt ):
    ch ,cw = center.shape

    #print("********현재 위치", y,x)
    #print("배열 길이",ch, cw)
    c = np.zeros((h,h), dtype=np.uint8)
    #if(y+h >ch or x+h > cw):
        #print("펑, 리턴은", y,x)
        #return y,x
        #print("리턴함?")
    max = 0
    ti = -1
    tj = -1
    for i in range (0, h):
        for j in range (0, h):
            c[i][j] = center[y+i][x+j]
            if c[i][j] >= max:
                ti = i
                tj = j
                max = c[i][j]
    #print("지금 돌고 있는 어레이")
    #print(c)
    #print("max : ", max)
    #print("여기서 제일 큰 i j는 ",ti,tj)

    if(ti == 0 and tj ==0):
        #print("리턴 좌표1= ",ti+y, tj+x)
        return [ti+y, tj+x]
        #print("리턴함?")
    elif recnt ==0:
        #print("리턴 좌표2= ",ti+y, tj+x)
        return [ti+y, tj+x]
        #print("리턴함?")
    else:
        #print("한번 더",ti+y,tj+x )
        if(ti+y+h > ch or tj+x+h >cw):
            #print("펑")
            #print(ti+y, tj+x)
            return [ti+y, tj+x]
        recnt = recnt -1
        largesearch0(ti+y,tj+x, center, h, recnt) 


def largesearch1(y,x, center, h ):
    c = np.zeros((h,h), dtype=np.uint8)
    max = 0
    ti = -1
    tj = -1
    for i in range (0, h):
        for j in range (0, h):
            c[i][j] = center[y+i][x+j]
            if c[i][j] > max:
                ti = i
                tj = j
                max = c[i][j]
    if(ti == 0 and tj ==0):
        return ti+y, tj+x, 1
    else:
        return ti+y, tj+x, 0


def largesearch(y,x, center, h ):
    c = np.zeros((h,h), dtype=np.uint8)
    max = 0
    ti = -1
    tj = -1
    for i in range (0, h):
        for j in range (0, h):
            c[i][j] = center[y+i][x+j]
            if c[i][j] > max:
                ti = i
                tj = j
                max = c[i][j]
    return ti+y, tj+x


                


########################################################################################################


black = (0,0,0)
img = cv2.imread( 'ms1.png', cv2.IMREAD_COLOR)
draw = cv2.imread('ms1.png', cv2.IMREAD_COLOR)
originheight,originwidth,c = img.shape
print(originheight,originwidth)

#img = cv2.resize(img, (864 ,496 )) 
#draw = cv2.resize(draw, (864 ,496 )) 
#img = cv2.resize(img, (432 ,248 )) 
#draw = cv2.resize(draw, (432 ,248 )) 

(B, G, R) = cv2.split(draw)
(dB, dG, dR) = cv2.split(draw)
merged = cv2.merge([B, G, R])
f = open("spacelog.txt", 'w')
status = "height %d width %d channel %d\n" %(originheight,originwidth ,c )

f.write(status)
h = 10

#dB, dG, dR
R= np.pad(R, pad_width=h, mode='constant', constant_values=0)
G= np.pad(G, pad_width=h, mode='constant', constant_values=0)
B= np.pad(B, pad_width=h, mode='constant', constant_values=0)
q,w = R.shape
print("원본 크기 출력",q,w)


dR= np.pad(dR, pad_width=h, mode='constant', constant_values=0)
dG= np.pad(dG, pad_width=h, mode='constant', constant_values=0)
dB= np.pad(dB, pad_width=h, mode='constant', constant_values=0)
q,w = dR.shape
height,width = dB.shape
print("그리기용 크기 출력",q,w)
status = "height %d width %d channel %d\n" %(height,width ,c )

f.write(status)

dR = np.zeros((q,w), dtype=np.uint8)
dG = np.zeros((q,w), dtype=np.uint8)
dB = np.zeros((q,w), dtype=np.uint8)

ddraw = np.zeros((originheight,originwidth,5), dtype=np.uint8)
pointcnt = np.zeros((originheight+10,originwidth+10), dtype=np.uint8)

########################################################################


time0 = time.time()           # 코드 시작 시간: time0

for i in range(h, originheight+h):
    for j in range(h, originwidth+h):
        origini = i
        originj = j
        log1 = "i = %d j = %d에서 원래 R = %d G = %d B = %d \n" %(i, j, R[i][j],G[i][j],B[i][j] )
        #upx = 0
        #upy = 0
        #upr = 0
        #upg = 0
        #upb = 0
        #down = 0
        repeatcnt = 0
        #f.write(log1)
        #print(i , j)
        while(True):
            #print(i , j)
            #print("사이클 끝")
            upx = 0
            upy = 0
            upr = 0
            upg = 0
            upb = 0
            down = 0
            for l in range (-h, h+1):
                    for z in range (-h, h+1):
                        #log4 = "[i+l, j+z]= [%d %d] ,[i,j]= [%d %d]\n" %(i+l, j+z, i,j)
                        #f.write(log4)
                        #print("디버깅용 중심::  도는데 ::",i, j ,i+l, j+z)
                        ks = gaussian_k(  euc_d([i+l, j+z] ,[i,j] ,h)  )   #좌표에 대한 K 정보
                        #log4 = "rgb 값 비교 r:%d g:%d b:%d  - r:%d g:%d b:%d\n" %(R[i+l][j+z],G[i+l][j+z],B[i+l][j+z],R[i][j],G[i][j],B[i][j])
                        #f.write(log4)
                        kr = gaussian_k(  euc_d(  [R[i+l][j+z],G[i+l][j+z],B[i+l][j+z]] , [R[i][j],G[i][j],B[i][j]] ,50) ) #색에 대한 K 정보
                        down = down + ks * kr
                        upx = upx + (j+z) * ks * kr
                        upy = upy + (i+l) * ks * kr
                        upr = upr + R[i+l][j+z] * ks * kr
                        upg = upg + G[i+l][j+z] * ks * kr
                        upb = upb + B[i+l][j+z] * ks * kr
            tx = round(upx/down)
            ty = round(upy/down)
            tr = round(upr/down)
            tg = round(upg/down)
            tb = round(upb/down)
            if(euclidean_dist0([ty,tx], [i,j])<5 and euclidean_dist0([tr,tg,tb],[R[i][j],G[i][j],B[i][j]])<5):
                #log2 = "############################이동한 i = %d j = %d r:%d g:%d b:%d  결정\n\n" %(ty,tx,tr,tg,tb)
                #f.write(log2) 
                #print(ty, tx)
                pointcnt[ty-h][tx-h] +=1
                #pointcnt[ty][tx] +=1
                i = origini
                j = originj
                repeatcnt = 0
                dR[i][j] = tr
                dG[i][j] = tg 
                dB[i][j] = tb
                ddraw[i-h][j-h][0] = ty
                ddraw[i-h][j-h][1] = tx
                ddraw[i-h][j-h][2] = tr
                ddraw[i-h][j-h][3] = tg
                ddraw[i-h][j-h][4] = tb
                break
            elif repeatcnt >10:
                #log2 = "############################이동한 i = %d j = %d r:%d g:%d b:%d  결정\n\n" %(ty,tx,tr,tg,tb)
                #f.write(log2)
                pointcnt[ty-h][tx-h] +=1
                #pointcnt[ty][tx] +=1
                    
                i = origini
                j = originj
                repeatcnt = 0
                dR[i][j] = tr
                dG[i][j] = tg
                dB[i][j] = tb
                ddraw[i-h][j-h][0] = ty
                ddraw[i-h][j-h][1] = tx
                ddraw[i-h][j-h][2] = tr
                ddraw[i-h][j-h][3] = tg
                ddraw[i-h][j-h][4] = tb
                break
            else:
                i = ty
                j = tx
                R[i][j] = tr
                G[i][j] = tg
                B[i][j] = tb
                repeatcnt = repeatcnt +1
                #log3 = "*********************아직 더 i = %d j = %d r:%d g:%d b:%d \n" %(i,j,tr,tg,tb)
                #f.write(log3)
                if i+h >= height or j+h>=width:
                    pointcnt[ty-h][tx-h] +=1
                    #pointcnt[ty][tx] +=1
                    i = origini
                    j = originj
                    repeatcnt = 0
                    dR[i][j] = tr
                    dG[i][j] = tg
                    dB[i][j] = tb
                    ddraw[i-h][j-h][0] = ty
                    ddraw[i-h][j-h][1] = tx
                    ddraw[i-h][j-h][2] = tr
                    ddraw[i-h][j-h][3] = tg
                    ddraw[i-h][j-h][4] = tb
                    break


print(time.time() - time0)    # (현재 시간 - 코드 시작 시간) 출력

print(ddraw)

#originheight,originwidth  ddraw[i+1][j][2],ddraw[i+1][j][3],ddraw[i+1][j][4]

cluster = np.zeros((originheight,originwidth), dtype=np.uint8)

##[y,x,r,g,b]

centerlist = []
patch = 3
samplelist = []
for i in range(0, originheight - patch):
    for j in range(0, originwidth - patch):
        if pointcnt[i][j] > 5:
            samplelist = largesearch0(i,j, pointcnt, patch,5)
            centerlist.append(samplelist)
            


#np.savetxt("save.txt", pointcnt, fmt='%d', delimiter=',')

merged = cv2.merge([dB, dG, dR])

cv2.imshow('img', draw)
cv2.imwrite('img.png', draw)
cv2.imshow('merged', merged)
cv2.imwrite('drawimg.png', merged)
print(centerlist)
print(len(centerlist))
cv2.waitKey(0)
cv2.destroyAllWindows()
