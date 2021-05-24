import cv2
import numpy as np
import math


def mask(img, mask, width, pi, pj):
    arr = np.ones((3,3), int)
    pi = pi-width
    pj = pj-width
    for i in range(width*(-1), width+1):
        for j in range(width*(-1), width+1):
            
            







black = (0,0,0)
blue = (255,0,0)
img = cv2.imread('circle.png', cv2.COLOR_BGR2GRAY)
img2 = cv2.imread('circle3.png', cv2.COLOR_BGR2GRAY)
#img = cv2.imread('meantest.png', cv2.COLOR_BGR2GRAY)
#img2 = cv2.imread('meantest2.png', cv2.COLOR_BGR2GRAY)
h,w,c = img.shape
h2,w2,c2 = img2.shape

print(h , w , c)
print(h2 , w2 , c2)


#img = cv2.resize(img, (432 ,248 )) 
#img2 = cv2.resize(img2, (432 ,248)) 

#img = cv2.resize(img, (43 ,24 )) 
#img2 = cv2.resize(img2, (43 ,24)) 




h,w,c = img.shape
h2,w2,c2 = img2.shape

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)


Z= np.pad(gray, pad_width=1, mode='constant', constant_values=0)
Z2= np.pad(gray2, pad_width=1, mode='constant', constant_values=0)



h,w,c = img.shape
h2,w2,c2 = img2.shape








#정상적으로 출력되는지 확인



########################

f = open("./a.txt", 'w')
for i in range(0,h+2):
    for j in range(0, w+2):
        data = "%3d "%Z[i][j]
        f.write(data)
    enter = "\n"
    f.write(enter)

f.close()

########################


#cv2.imshow('image1',gray1)
#cv2.imshow('image2',gray2)

'''
for i in range(0,3):
    for j in range (0,3):
        print(i, j, end= '  ')
    print("\n")
'''
arr = np.ones((3,3), int)
arr2 = np.ones((3,3), int)
arr2x = np.ones((3,3), int)
arr2y = np.ones((3,3), int)
dx = np.ones((3,3), int)
dy = np.ones((3,3), int)
dt = np.ones((3,3), int)

A = np.ones((9,2), int)
B = np.ones((9,1), int)
At= np.ones((2,9), int)
AtA = np.ones((2,2), int)
As = np.ones((2,9), float)
R = np.ones((2,2), float)
uv = np.ones((2,1), float)

uvlist = []
savearr1 = np.empty((h, w))
savearr2 = np.empty((h, w))

cnt = 0

for y in range(0 ,h-3):
    for x in range(0, w-3):

        for i in range (0, 3):
            for j in range(0, 3):        
                arr[i][j] = Z[y+i][x+j]
                arr2x[i][j] = Z[y+i][x+j+3]
                arr2y[i][j] = Z[y+i+3][x+j]
                arr2[i][j] = Z2[y+i][x+j]
        #print(arr)
        #print(arr2x)
        #print(arr2y)      
        '''
        for i in range (0, 3):
            for j in range(0, 3):        
                dx[i][j] = arr2x[i][j] - arr[i][j]
                dy[i][j] = arr2y[i][j] - arr[i][j]
                dt[i][j] = arr2[i][j] - arr[i][j]
        '''
        dx = arr2x - arr
        dy = arr2y - arr
        dt = arr2 - arr
        c = 0
        for i in range(3):
            for j in range(3):
                A[c][0] = dx[i][j]
                A[c][1] = dy[i][j]
                B[c][0] = -(dt[i][j])
                c = c+1
        #print(A)
        #print(B)
        At = np.transpose(A)
        #print("At", At)
        
        
        AtA = np.dot(At, A)
        #print("AtA",AtA)

        if abs((AtA[0][0] * AtA[1][1]) - (AtA[1][0] * AtA[0][1])) > 0.0001 :      
            R = np.linalg.inv(AtA)
            #print("R", R)
            As = np.dot(R, At)
            #print("ATAR",As)
            uv = np.dot(As, B)
            #print(uv[0][0], uv[1][0])
            #print(int (uv[1,0]), int (uv[1,0]))
            if( round(uv[0,0]) !=0 or  round(uv[1,0]) != 0 ):
                #img = cv2.arrowedLine(img, (y,x) , (y+round(uv[1,0]), x+round(uv[0,0])), black, 1) 
                #img = cv2.circle(img, (y+round(uv[1,0]), x+round(uv[0,0])), 1, black  )
                #img = cv2.circle(img, (y, x), 1, blue  )
                print(round(uv[0,0]),round(uv[1,0]) )
                img = cv2.circle(img, (y+round(uv[1,0]), x+round(uv[0,0])), 1, black  )
                img = cv2.circle(img, (y, x), 1, blue  )
        
            #print("uv",uv)
            uvlist.append(uv)
            #print(cnt)
            cnt = cnt+1
            #print("1")
            #print(uv)
        else:
            uv = np.zeros((2,1), int)
            #print(int (uv[1,0]), int (uv[1,0]))
            
            #print("uv",uv)
            uvlist.append(uv)
            #print(cnt)
            cnt = cnt+1
            #print("2")
            #print(uv)
        #print("cycle end")
        #print(y+1, x+1)
        #print(arr)
        #savearr1[i][j] = arr
        
        '''
        if cnt ==2:
            flag = 1
            break
    if flag ==1:
        break
        '''
    
'''
int(uvlist[0][0])
print(int(uvlist[0][0]))
print(int(uvlist[0][1]))
#print(uvlist[0])
print((uvlist[1][0]))
print((uvlist[1][1]))
'''
#print(uvlist)
#print(int(uvlist[1][0,0]))
#print(int(uvlist[1][1,0]))
'''
for i in range(0, len(uvlist)):
        print(int(uvlist[i][0,0]))
        print(int(uvlist[i][1,0]))
'''


'''
for i in range(0, len(uvlist)):
    if int(uvlist[i][0,0]) != 0 or int(uvlist[i][0,0]) != 0:
        print("hello")
        print(i)
        print((uvlist[i][1,0]), (uvlist[i][1,0]))
'''      




'''

for y in range(1 ,h):
    for x in range(1, w):
        
        for i in range (0, 3):
            for j in range(0, 3):        
                arr[i][j] = Z2[y+i][x+j] 
        #print(y+1, x+1)
        #print(arr)
        savearr2[i][j] = arr
'''

cv2.imshow('img', img)
cv2.imwrite('img.png', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

