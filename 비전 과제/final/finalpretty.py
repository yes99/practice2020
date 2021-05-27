import cv2
import numpy as np
import math
import time
import datetime
print(datetime.datetime.today())
black = (0,0,0)
blue = (255,0,0)

# Meanshift 에서 쓰이는 함수
# 실제 유클리드 거리. 
# yt yi의 spacial한 거리와 rgb값들의 차이를 확인할때 쓴다
def euclidean_dist0(pointA, pointB):         
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension] - pointB[dimension])**2
    dist = math.sqrt(total)
    return dist

# 유클리드 거리의 제곱 합
# 가우시안 커널을 구할때 들어가는 -||x||^2 값을 넣기 위해서 썼다. 
# h값도 파라미터로 받아서, 연산 중에 나눠서 제곱값을 구하게 했다.

def euc_d(pointA, pointB ,h):
    total = float(0)
    for dimension in range(0, len(pointA)):
        total += (pointA[dimension]/h - pointB[dimension]/h)**2
    return total

# 가우시안 커널을 구한다. 
# 위에서 구한 유클리드 거리의 제곱을 그대로 여기에 넣는다. 
# l2파라미터 값이 1을 넘어가면 범위에 없다고 가정하고 0을 넣는다. 
#  -> spacial한 정보를 구할때는 그럴일이 없지만 RGB값을 구할때는 적절한 h값을 구해야한다.
def gaussian_k(l2):
    e= math.pi
    #print ("l2는", l2)
    if math.sqrt(l2) <=1:
        return e**(-l2)
    else:
        return 0
# V1 찾아가는 과정
# 전체 과정에서 mean shift를 해서 중심점이 몰리는 부분중에서 가장 수치가 높은 의미있는 점을 찾는다.  
# recnt를 따로 세서, 만약 같은 자리에서 돌면 적절할때 리턴해주도록 한다.
def largesearch0(y,x, center, h, recnt ): #y, x , 중심점을 기록한 array, 재귀 횟수
    ch ,cw = center.shape
    c = np.zeros((h,h), dtype=np.uint8)
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

    if(ti == 0 and tj ==0):
        return [ti+y, tj+x]
    elif recnt ==0:
        return [ti+y, tj+x]
    else:
        if(ti+y+h > ch or tj+x+h >cw):  #만약 지정된 array의 axis0 1 을 넘어가게 되면 그 자리에서 리턴한다.
            return [ti+y, tj+x]
        recnt = recnt -1
        largesearch0(ti+y,tj+x, center, h, recnt) 

########################################################################################################
# optical flow에서 쓰이는 함수
"""
-1 -1   -1 0  1 1
 0 -1    x y  1 0
 1 -1    1 0  1 1

"""
# 위와 같은 패치를 만들수 있는 함수이다. width 파라미터로 크기 조절 가능하다
def masking(img, width, pi , pj ):  #img  x*x , pi, pj 
    arr = np.ones((width,width),  np.float32)
    for i in range(-int(width/2), int(width/2)+1):
        for j in range(-int(width/2), int(width/2)+1):
            arr[int(width/2) + i][int(width/2) + j] = img[pi + i][pj + j] 
        #print("\n")
    return arr

########################################################################################################
##   *********파라미터*************
## Meanshift parameters
h = 10   #h spacial -> 패치의 반지름이라고 보면 된다
hr = 50  #h rgb -> rgb패치를 나누는 h역할을 한다.
spacial_euclid_threshold = 5 # threshold, yt yi 거리를 잡아준다. 
rgb_euclid_threshold     = 5 # threshold, yt yi 거리를 잡아준다.
large_threshold          = 5 # threshold, yt yi 거리를 잡아준다.
patch = 3                    #largesearch 에 쓰이는 패치 크기
## Optical Flow parameters
mwidth = 3                   # optical flow에서 쓸 패치의 변 길이
move = 1                     # gradiant 움직인 길이
sizedivide = 5
##   ******************************

img = cv2.imread( 'test1.png', cv2.IMREAD_COLOR)
img2 = cv2.imread('test2.png', cv2.COLOR_BGR2GRAY)
draw = cv2.imread('test1.png', cv2.IMREAD_COLOR)
originheight,originwidth,c = img.shape #이미지 자체의 크기
print(originheight,originwidth)

# 연산이 너무 오래 걸려서 나눴다...
img = cv2.resize(img,   (originwidth//sizedivide,originheight//sizedivide))
img2 = cv2.resize(img2, (originwidth//sizedivide,originheight//sizedivide))
draw = cv2.resize(draw, (originwidth//sizedivide,originheight//sizedivide)) 

originheight,originwidth,c = img.shape #이미지 자체의 크기
print(originheight,originwidth)

(B, G, R) = cv2.split(draw)
(dB, dG, dR) = cv2.split(draw)
merged = cv2.merge([B, G, R])
#dB, dG, dR
R= np.pad(R, pad_width=h, mode='constant', constant_values=0)
G= np.pad(G, pad_width=h, mode='constant', constant_values=0)
B= np.pad(B, pad_width=h, mode='constant', constant_values=0)
padh, padw = R.shape
print("원본 크기 출력",padh, padw)

# 패딩
dR= np.pad(dR, pad_width=h, mode='constant', constant_values=0)
dG= np.pad(dG, pad_width=h, mode='constant', constant_values=0)
dB= np.pad(dB, pad_width=h, mode='constant', constant_values=0)
padh, padw = dR.shape
print("그리기용 크기 출력", padh, padw)

#패딩한것과 같은 크기의 array
dR = np.zeros((padh, padw), dtype=np.uint8)
dG = np.zeros((padh, padw), dtype=np.uint8)
dB = np.zeros((padh, padw), dtype=np.uint8)

# array에 5*1 벡터들 모두 저장
ddraw = np.zeros((originheight,originwidth,5), dtype=np.uint8)  
# 해당좌표로 이동된 점의 갯수를 기록하는 array
pointcnt = np.zeros((originheight+10,originwidth+10), dtype=np.uint8)
#각각의 점이 어디로 마지막으로 meanshift되었는지 기록하는 리스트
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
                pointcnt[ty-h][tx-h] +=1
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
                if i+h >= padh or j+h>=padw:
                    pointcnt[ty-h][tx-h] +=1
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

##[y,x,r,g,b]

# centerlist 에는 우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다. 
# meanshift 해서 큰 모든 중심들이 모인 점
centerlist = []  
samplelist = []  ##리스트에 리스트를 넣기 위한 리스트


#우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다.

for i in range(0, originheight - patch):
    for j in range(0, originwidth - patch):
        if pointcnt[i][j] > large_threshold: 
            samplelist = largesearch0(i,j, pointcnt, patch,5)
            centerlist.append(samplelist)
            


merged = cv2.merge([dB, dG, dR])

cv2.imshow('img', draw)
cv2.imwrite('img.png', draw)
cv2.imshow('merged', merged)
cv2.imwrite('drawimg.png', merged)








print("**********민시프트 완료************************")
#######################################################여기까지가 민시프트


#그레이로 바꿔줌 img->gray
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)


#패딩 한번 해준다 gray->Z
Z= np.pad(gray, pad_width=mwidth//2, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=mwidth//2, mode='constant', constant_values=0)
Zdraw= np.pad(draw, pad_width=mwidth//2, mode='constant', constant_values=0)
# v u  저장하기 위한 배열
varray = np.zeros((originheight+10, originwidth+10), np.float32)
uarray= np.zeros((originheight+10, originwidth+10), np.float32)
#originheight, originwidth

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

for y in range(mwidth//2 ,originheight-(move-1)):     # 1~h까지 3*3이니까
    for x in range(mwidth//2, originwidth -(move-1)): # 1~w까지 3*3이니까
        # 위에서 구한 arr에 해당 이미지의 grayscale 값들을 넣어준다.
        arr = masking(Z, mwidth, y,x)
        arrt  = masking(Z2, mwidth, y,x)
        arrx  = masking(Z, mwidth, y,x+move)
        arry  = masking(Z, mwidth, y+move,x)
        # 그래디언트
        dx = arrx - arr
        dy = arry - arr
        dt = arrt -arr
                   
        c = 0
        # mwidth^2 *2 로 만드는 과정
        for i in range(mwidth):
            for j in range(mwidth):
                A[c][0] = dx[i][j]
                A[c][1] = dy[i][j]
                B[c][0] = -(dt[i][j])
                c = c+1

        #print("B\n",B)
        At = np.transpose(A)
        AtA = np.dot(At, A)

        #역함수는 만들수 있을지 판별
        if (AtA[0][0] * AtA[1][1]) - (AtA[1][0] * AtA[0][1]) != 0 :    
            R = np.linalg.inv(AtA)
            As = np.dot(R, At)
            vu = np.dot(As, B)
            vu[0,0] = round(vu[0,0]) #v
            vu[1,0] = round(vu[1,0]) #u
            varray[y -mwidth//2][x- mwidth//2]  = int(vu[0,0] )
            uarray[y -mwidth//2][x- mwidth//2] = int(vu[1,0] )
            vulist.append([y+10, x+10, vu[0,0], vu[1,0]])#[(내y좌표, 내 x좌표) , (v만큼 움직인 거리, u만큼 움직인 거리 )]
            if(y % 5 == 0 and x %5 ==0):
                draw = cv2.line(draw, (x,y) , (x+round(vu[1,0]), y+round(vu[0,0])), black, 2)
           
            cnt = cnt+1
           
        else:             #역함수는 만들수 없다
            vu = np.zeros((2,1), int)
            if(y % 5 == 0 and x %5 ==0):
                draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 2)
            vulist.append([y+10, x+10, 0, 0]) 
            cnt = cnt+1
            

print("정보수집 완료")
# vulist ([y+10, x+10, vu[0,0], vu[1,0]]) #(y좌표, 내 x좌표) , (v만큼 움직인 거리, u만큼 움직인 거리 )
# pointtouv ([i,j,ty,tx])                 #(내y좌표, 내 x좌표) , (yt의 y좌표, yt의 x좌표)
# centerlist 에는 우리가 구한 포인트 점들중에서 값이 큰 값을 찾아내서 간추린다. 
# 즉 무게 중심점이라는 이야기이다. 여기로 모이는 점들을 찾아야한다. (yt의 y좌표, yt의 x좌표)

for i in range(0, len(centerlist)):
    for j in range (0, len(vulist)):
        sumv = 0
        sumu = 0
        cnt = 0
        if centerlist[i] is not None:
            #  centerlist에 저장된 yt와 vulist yt 좌표가 일치하는지 확인 
            if(centerlist[i][0] == vulist[j][0] and centerlist[i][1] == vulist[j][1]): 
                print(centerlist[i])
                for k in range(0, len(pointtouv)):
                    # yt좌표가 되기전의 원래 점의 y x 좌표들의 u v값을 모두 더하고 평균으로 나눈다.
                    if(pointtouv[k][2]== vulist[j][0] and pointtouv[k][3]== vulist[j][1]):
                        print("*", end='')
                        sumv = sumv + varray[pointtouv[k][0]][pointtouv[k][1]]
                        sumu = sumu + uarray[pointtouv[k][0]][pointtouv[k][1]]
                        cnt = cnt+1
                print(sumv, sumu, cnt)
                v = round(sumv/cnt)
                u = round(sumu/cnt)
                # segment의 평균 이동점 그림에 그린다
                merged = cv2.line(merged, (vulist[j][1],vulist[j][0]) , ((vulist[j][1]+v), (vulist[j][0]+u)), blue, 1)

print(time.time() - time0)    # (현재 시간 - 코드 시작 시간) 출력


cv2.imshow('final', merged)
cv2.imwrite('finaldraw.png', merged)

cv2.imshow('draw', draw)
cv2.imshow('img', img)
cv2.imwrite('draw.png', draw)

cv2.waitKey(0)
cv2.destroyAllWindows()
