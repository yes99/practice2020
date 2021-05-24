import cv2
import numpy as np
import math

black = (0,0,0)

def masking(img, width, pi , pj ):  #img  x*x , pi, pj 
    arr = np.ones((width,width), int)
    for i in range(-int(width/2), int(width/2)+1):
        for j in range(-int(width/2), int(width/2)+1):
            #arr[i][j] = img[pi + i][pj + j]
            #print(pi + i, pj + j, end="  ")
            #print(int(width/2) + i, int(width/2) + j, end="  ")
            arr[int(width/2) + i][int(width/2) + j] = img[pi + i][pj + j] 
        #print("\n")
    return arr



#읽어오자   img 
img = cv2.imread('circle.png', cv2.COLOR_BGR2GRAY)
img2 = cv2.imread('circle2.png', cv2.COLOR_BGR2GRAY)
h,w,c = img.shape
h2,w2,c2 = img2.shape
#읽어온 이미지 크기 확인
print(h , w , c)
print(h2 , w2 , c2)

#작게 리사이즈 img ->img
img = cv2.resize(img, (432 ,248 )) 
img2 = cv2.resize(img2, (432 ,248)) 


#그레이로 바꿔줌 img->gray
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)


#패딩 한번 해준다 gray->Z
Z= np.pad(gray, pad_width=1, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=1, mode='constant', constant_values=0)

#다시 크기 정의해준다
h,w,c = img.shape
h2,w2,c2 = img2.shape


#print("함수테스트")
#masking(img, 5, 12,13)


#현재는 3*3 마스크로 해줄꺼다

#제일 기본 마스크
arr = np.ones((3,3), int)

#그래디언트를 위한 마스크
arrt = np.ones((3,3), int)
arrx = np.ones((3,3), int)
arry = np.ones((3,3), int)

#기본과 그래디언트 차이 델타값구하기
dx = np.ones((3,3), int)
dy = np.ones((3,3), int)
dt = np.ones((3,3), int)


#후계산 처리 과정
A = np.ones((9,2), int)

#A의 트랜스 t
At= np.ones((2,9), int)
AtA = np.ones((2,2), int)
#역함수
R = np.ones((2,2), float)
#A들 전체 계산 (AtA)rAt
As = np.ones((2,9), float)
#B값
B = np.ones((9,1), int)
#도출된 vu
vu = np.ones((2,1), float)

cnt = 0

for y in range(1 ,h-1):     # 1~h까지 3*3이니까
    for x in range(1, w-1): # 1~w까지 3*3이니까
        arr = masking(Z, 3, y,x)
        arrt  = masking(Z2, 3, y,x)
        arrx  = masking(Z, 3, y,x+1)
        arry  = masking(Z, 3, y+1,x)
        dx = arrx - arr
        dy = arry - arr
        dt = arrt -arr
        """
        print("arr\n", arr)
        print("arrt\n", arrt)
        print("arrx\n", arrx)
        print("arry\n", arry)
        print("dx\n", dx)
        print("dy\n", dy)
        print("dt\n", dt)
        """            
        c = 0
        for i in range(3):
            for j in range(3):
                A[c][0] = dx[i][j]
                A[c][1] = dy[i][j]
                B[c][0] = -dt[i][j]
                c = c+1

        print("B\n",B)
        At = At = np.transpose(A)
        AtA = AtA = np.dot(At, A)

        print("At\n",At)
        print("A\n",A)
        print("AtA\n",AtA)
        if (AtA[0][0] * AtA[1][1]) - (AtA[1][0] * AtA[0][1]) != 0 :   
            print("통과")
            R = np.linalg.inv(AtA)
            print("R\n", R)
            As = np.dot(R, At)
            print("ATAR\n",As)
            vu = np.dot(As, B)
            print(vu[0][0], vu[1][0])
            print(vu)
            print(int (vu[1,0]), int (vu[1,0]))
            vu[0,0] = round(vu[0,0])
            vu[1,0] = round(vu[1,0])
            print(vu)
            if( int(vu[0,0]) !=0 or  int(vu[1,0]) != 0 ):
                print("그리기 시작")
                img = cv2.line(img, (y,x) , (y+int(vu[0,0]), x+int(vu[1,0])), black, 2) 
     
            #print("vu",vu)
            #print(cnt)
            cnt = cnt+1
            #print("1")
            #print(vu)
            
        break
    break
    """ 
        else:
            vu = np.zeros((2,1), int)
            #print(int (vu[1,0]), int (vu[1,0]))
            
            #print("vu",vu)
            vulist.append(vu)
            #print(cnt)
            cnt = cnt+1
            #print("2")
            #print(vu)
        #print("cycle end")
        #print(y+1, x+1)
        #print(arr)
        #savearr1[i][j] = arr
    """

cv2.imshow('img', img)

cv2.waitKey(0)
cv2.destroyAllWindows()

