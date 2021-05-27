import cv2
import numpy as np
import math
import time
import datetime
print(datetime.datetime.today())
black = (0,0,0)
blue = (255,0,0)


def euclidean_dist0(pointA, pointB):
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension] - pointB[dimension])**2
    dist = math.sqrt(total)
    return dist


def euc_d(pointA, pointB ,h):
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension]/h - pointB[dimension]/h)**2
    return total

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

########################################################################################################
def masking(img, width, pi , pj ):  #img  x*x , pi, pj 
    arr = np.ones((width,width),  np.float32)
    for i in range(-int(width/2), int(width/2)+1):
        for j in range(-int(width/2), int(width/2)+1):
            #arr[i][j] = img[pi + i][pj + j]
            #print(pi + i, pj + j, end="  ")
            #print(int(width/2) + i, int(width/2) + j, end="  ")
            arr[int(width/2) + i][int(width/2) + j] = img[pi + i][pj + j] 
        #print("\n")
    return arr
"""
-1 -1   -1 0  1 1
 0 -1     x y  x+1 y+0
 1 -1     1 0  1 1

"""
########################################################################################################
##   *********파라미터*************
## Meanshift parameters
h = 10  
hr = 50
spacial_euclid_threshold = 5
rgb_euclid_threshold     = 5
large_threshold          = 5
## Optical Flow parameters
mwidth = 3
move = 1
##   ******************************

img = cv2.imread( 'test1.png', cv2.IMREAD_COLOR)
draw = cv2.imread('test1.png', cv2.IMREAD_COLOR)
originheight,originwidth,c = img.shape #이미지 자체의 크기
print(originheight,originwidth)

img = cv2.resize(img,   (originwidth//3,originheight//3)) 
draw = cv2.resize(draw, (originwidth//3,originheight//3)) 
#img = cv2.resize(img, (432 ,248 )) 
#draw = cv2.resize(draw, (432 ,248 )) 
originheight,originwidth,c = img.shape #이미지 자체의 크기
print(originheight,originwidth)

(B, G, R) = cv2.split(draw)
(dB, dG, dR) = cv2.split(draw)
merged = cv2.merge([B, G, R])
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


dR = np.zeros((q,w), dtype=np.uint8)
dG = np.zeros((q,w), dtype=np.uint8)
dB = np.zeros((q,w), dtype=np.uint8)

ddraw = np.zeros((originheight,originwidth,5), dtype=np.uint8)
pointcnt = np.zeros((originheight+10,originwidth+10), dtype=np.uint8)
pointtouv = []
########################################################################


time0 = time.time()           # 코드 시작 시간: time0

for i in range(h, originheight+h):
    for j in range(h, originwidth+h):
        origini = i
        originj = j
        log1 = "i = %d j = %d에서 원래 R = %d G = %d B = %d \n" %(i, j, R[i][j],G[i][j],B[i][j] )
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
                        kr = gaussian_k(  euc_d(  [R[i+l][j+z],G[i+l][j+z],B[i+l][j+z]] , [R[i][j],G[i][j],B[i][j]] ,hr) ) #색에 대한 K 정보
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
            if(euclidean_dist0([ty,tx], [i,j])<spacial_euclid_threshold  and euclidean_dist0([tr,tg,tb],[R[i][j],G[i][j],B[i][j]])<rgb_euclid_threshold):  
                #log2 = "############################이동한 i = %d j = %d r:%d g:%d b:%d  결정\n\n" %(ty,tx,tr,tg,tb)
                #f.write(log2) 
                #print(ty, tx)
                pointcnt[ty-h][tx-h] +=1
                #pointcnt[ty][tx] +=1
                i = origini
                j = originj
                pointtouv.append([i,j,ty-h,tx-h])
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
                pointtouv.append([i,j,ty-h,tx-h])
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
                    pointtouv.append([i,j,ty-h,tx-h])
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

#print(ddraw)  #모든 ms들이 도달하는 좌표와 색들이 모여있는 3차원

##[y,x,r,g,b]

centerlist = []  #모든 중심들이 모인 점
patch = 3
samplelist = []  ##리스트에 리스트를 너힉 위한 리스트


#우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다.

for i in range(0, originheight - patch):
    for j in range(0, originwidth - patch):
        if pointcnt[i][j] > large_threshold:  ####5도 파라미터
            samplelist = largesearch0(i,j, pointcnt, patch,5)
            centerlist.append(samplelist)
            


merged = cv2.merge([dB, dG, dR])

cv2.imshow('img', draw)
cv2.imwrite('img.png', draw)
cv2.imshow('merged', merged)
cv2.imwrite('drawimg.png', merged)
print(centerlist)
print(len(centerlist))
#centerlist 에는 우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다. 즉 무게 중심점이라는 이야기이다. 여기로 모이는 점들을 찾아야 한다. 








print("**********민시프트 완료************************")
#######################################################여기까지가 민시프트






#읽어오자   img 
#img = cv2.imread('test1.png', cv2.COLOR_BGR2GRAY)
#img2 = cv2.imread('test2.png', cv2.COLOR_BGR2GRAY)
#draw = cv2.imread('test1.png', cv2.COLOR_BGR2GRAY)
img = cv2.imread( 'test1.png', cv2.COLOR_BGR2GRAY)
img2 = cv2.imread('test2.png', cv2.COLOR_BGR2GRAY)
draw = cv2.imread('test1.png', cv2.COLOR_BGR2GRAY)


h,w,c = img.shape
h2,w2,c2 = img2.shape
#읽어온 이미지 크기 확인
print(h , w , c)
print(h2 , w2 , c2)

#작게 리사이즈 img ->img
img = cv2.resize(img,   (w//3 ,h//3 )) 
img2 = cv2.resize(img2, (w//3 ,h//3)) 
draw = cv2.resize(draw, (w//3 ,h//3))


#그레이로 바꿔줌 img->gray
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

mwidth = 3
move = 1

#패딩 한번 해준다 gray->Z
Z= np.pad(gray, pad_width=mwidth//2, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=mwidth//2, mode='constant', constant_values=0)
Zdraw= np.pad(draw, pad_width=mwidth//2, mode='constant', constant_values=0)
# v u  저장하기 위한 배열
varray = np.zeros((h,w), np.float32)
uarray= np.zeros((h,w), np.float32)


#다시 크기 정의해준다
h,w,c = img.shape
h2,w2,c2 = img2.shape


#print("함수테스트")
#masking(img, 5, 12,13)

#현재는 3*3 마스크로 해줄꺼다

#제일 기본 마스크
arr = np.ones((mwidth,mwidth), np.float32)

#그래디언트를 위한 마스크
arrt = np.ones((mwidth,mwidth), np.float32)
arrx = np.ones((mwidth,mwidth), np.float32)
arry = np.ones((mwidth,mwidth), np.float32)

#기본과 그래디언트 차이 델타값구하기
dx = np.ones((mwidth,mwidth), np.float32)
dy = np.ones((mwidth,mwidth), np.float32)
dt = np.ones((mwidth,mwidth), np.float32)


#후계산 처리 과정
A = np.ones((mwidth**2,2), np.float32)

#A의 트랜스 t
At= np.ones((2,mwidth**2), np.float32)
AtA = np.ones((2,2), np.float32)
#역함수
R = np.ones((2,2), np.float32)
#A들 전체 계산 (AtA)rAt
As = np.ones((2,mwidth**2), np.float32)
#B값
B = np.ones((mwidth**2,1), np.float32)
#도출된 vu
vu = np.ones((2,1), np.float32)
vulist = []
cnt = 0

for y in range(mwidth//2 ,h-(move-1)):     # 1~h까지 3*3이니까
    for x in range(mwidth//2, w -(move-1)): # 1~w까지 3*3이니까
        arr = masking(Z, mwidth, y,x)
        arrt  = masking(Z2, mwidth, y,x)
        arrx  = masking(Z, mwidth, y,x+move)
        arry  = masking(Z, mwidth, y+move,x)
        dx = arrx - arr
        dy = arry - arr
        dt = arrt -arr
                   
        c = 0
        for i in range(mwidth):
            for j in range(mwidth):
                A[c][0] = dx[i][j]
                A[c][1] = dy[i][j]
                B[c][0] = -(dt[i][j])
                c = c+1

        #print("B\n",B)
        At = At = np.transpose(A)
        AtA = AtA = np.dot(At, A)

        #print("At\n",At)
        #print("A\n",A)
        #print("AtA\n",AtA)
        if (AtA[0][0] * AtA[1][1]) - (AtA[1][0] * AtA[0][1]) != 0 :    #역함수는 만들수 있을까??
            #print("통과")
            R = np.linalg.inv(AtA)
           # print("R\n", R)
            As = np.dot(R, At)
            #print("ATAR\n",As)
            vu = np.dot(As, B)
            #print(vu[0][0], vu[1][0])
            #print(vu)
            #print(int (vu[1,0]), int (vu[1,0]))

            #data = "%3f %3f\n"%(vu[0,0], vu[1,0])
            #f1.write(data)
            
            vu[0,0] = round(vu[0,0]) #v
            vu[1,0] = round(vu[1,0]) #u
            varray[y -mwidth//2][x- mwidth//2]  = int(vu[0,0] )
            uarray[y -mwidth//2][x- mwidth//2] = int(vu[1,0] )
            vulist.append([y+10, x+10, vu[0,0], vu[1,0]])#(내y좌표, 내 x좌표) , (v만큼 움직인 거리, u만큼 움직인 거리 )
            if(y % 5 == 0 and x %5 ==0):
                #draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 2)
                draw = cv2.line(draw, (x,y) , (x+round(vu[1,0]), y+round(vu[0,0])), black, 2)
           
            cnt = cnt+1
           # print("1")
        
        else:                                                            #역함수는 만들수가 없겠지
            vu = np.zeros((2,1), int)
            if(y % 5 == 0 and x %5 ==0):
                draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 2)
            vulist.append([y+10, x+10, 0, 0]) 

            #print(int (vu[1,0]), int (vu[1,0]))
            #vulist.append(vu.tolist())
            #print("vu",vu)
            #print(cnt)
            cnt = cnt+1
            #print("2")
            #print(vu)
        
        #print("cycle end")


print("정보수집 완료")
print(vulist) # vulist ([y+10, x+10, vu[0,0], vu[1,0]])#(내y좌표, 내 x좌표) , (v만큼 움직인 거리, u만큼 움직인 거리 )
              # pointtouv ([i,j,ty,tx])                 #(내y좌표, 내 x좌표) , (y가 도달한 곳, x가 도달한 곳)
              # centerlist 에는 우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다. 즉 무게 중심점이라는 이야기이다. 여기로 모이는 점들을 찾아야 한다. (도달한 y좌표, 도달한 x좌표)

for i in range(0, len(centerlist)):
    for j in range (0, len(vulist)):
        sumv = 0
        sumu = 0
        cnt = 0
        if centerlist[i] is not None:
            if(centerlist[i][0] == vulist[j][0] and centerlist[i][1] == vulist[j][1]):  #텍스트에서 제일 큰애 좌표랑, vu리스트의 내 좌표랑 일치
                print(centerlist[i])
                for k in range(0, len(pointtouv)):
                    if(pointtouv[k][2]== vulist[j][0] and pointtouv[k][3]== vulist[j][1]):
                        print("*", end='')
                        sumv = sumv + varray[pointtouv[k][0]][pointtouv[k][1]]
                        sumu = sumu + uarray[pointtouv[k][0]][pointtouv[k][1]]
                        cnt = cnt+1
                print(sumv, sumu, cnt)
                v = round(sumv/cnt)
                u = round(sumu/cnt)
                merged = cv2.line(merged, (vulist[j][1],vulist[j][0]) , ((vulist[j][1]+v), (vulist[j][0]+u)), blue, 2)

#               merged = cv2.line(merged, (vulist[j][1],vulist[j][0]) , ((vulist[j][1]+round(vulist[j][2])), (vulist[j][0]+round(vulist[j][3]))), blue, 2)

print(time.time() - time0)    # (현재 시간 - 코드 시작 시간) 출력


cv2.imshow('final', merged)
cv2.imwrite('finaldraw.png', merged)

cv2.imshow('draw', draw)
cv2.imshow('img', img)
cv2.imwrite('draw.png', draw)

cv2.waitKey(0)
cv2.destroyAllWindows()
