import cv2
import numpy as np
import math

black = (0,0,0)
blue = (255,0,0)

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
#img = cv2.resize(img, (w//2 ,h//2 )) 
#img2 = cv2.resize(img2, (w//2 ,h//2)) 
#draw = cv2.resize(draw, (w//2 ,h//2))
#img = cv2.resize(img, (43 ,24 )) 
#img2 = cv2.resize(img2, (43 ,24)) 
#draw = cv2.resize(draw, (43 ,24))


#그레이로 바꿔줌 img->gray
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

mwidth = 3
move = 1

#패딩 한번 해준다 gray->Z
Z= np.pad(gray, pad_width=mwidth//2, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=mwidth//2, mode='constant', constant_values=0)
Zdraw= np.pad(draw, pad_width=mwidth//2, mode='constant', constant_values=0)

#다시 크기 정의해준다
h,w,c = img.shape
h2,w2,c2 = img2.shape


#print("함수테스트")
#masking(img, 5, 12,13)
########################
"""
f = open("./a.txt", 'w')
f0 = open("./a1.txt", 'w')

f1 = open("./b.txt", 'w')
f2 = open("./c.txt", 'w')

for i in range(0,h+2):
    for j in range(0, w+2):
        data = "%03d "%Z[i][j]
        f.write(data)
        data = "%03d "%Z2[i][j]
        f0.write(data)
    enter = "\n"
    f.write(enter)
    f0.write(enter)
f.close()
"""
########################



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
        '''
        f2.write("%d %d\n"%(y,x))
        f2.write("arr\n", arr)
        f2.write("arrt\n", arrt)
        f2.write("arrx\n", arrx)
        f2.write("arry\n", arry)
        f2.write("dx\n", dx)
        f2.write("dy\n", dy)
        f2.write("dt\n", dt)
        '''
                   
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
            if(y % 5 == 0 and x %5 ==0):
                #draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 2)
                draw = cv2.line(draw, (x,y) , (x+round(vu[1,0]), y+round(vu[0,0])), black, 2)
            """
            #print(vu)
            if( round(vu[0,0]) !=0 or  round(vu[1,0]) != 0 ):
                #if(round(vu[0,0]) <3 and round(vu[1,0]) <mwidth):
                #print("그리기 시작")
                #draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 1)
                #draw = cv2.circle(draw, (x,y), 1, black  )
                #draw = cv2.circle(draw , ((x+(round(vu[1,0]))*5), y+(round(vu[0,0])*5)), 1, blue  )
                #draw = cv2.arrowedLine(draw, (x,y) , (x+(round(vu[1,0])*5), y+(round(vu[0,0])*5)), black, 2)
                #cv2.imwrite('./imim/%d.PNG'%cnt ,draw )               
                vulist.append(vu.tolist())
            #print(cnt)
            """
            cnt = cnt+1
           # print("1")
        
        else:                                                            #역함수는 만들수가 없겠지
            vu = np.zeros((2,1), int)
            if(y % 5 == 0 and x %5 ==0):
                draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 2)
            #print(int (vu[1,0]), int (vu[1,0]))
            #vulist.append(vu.tolist())
            #print("vu",vu)
            #print(cnt)
            cnt = cnt+1
            #print("2")
            #print(vu)
        
        #print("cycle end")

print("정보수집 완료")

"""
for y in range(mwidth//2 ,h-(move-1)):     # 1~h까지 3*3이니까
    for x in range(mwidth//2, w -(move-1)): # 1~w까지 3*3이니까
        if(y % 5 == 0 and x %5 ==0):
            draw = cv2.line(draw, (x,y) , (x+round(vu[0,0]), y+round(vu[1,0])), black, 1)
"""


cv2.imshow('draw', draw)
cv2.imshow('img', img)
cv2.imwrite('draw.png', draw)


cv2.waitKey(0)
cv2.destroyAllWindows()

