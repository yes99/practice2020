import numpy as np




def largesearch0(y,x, center, h, recnt ):
    ch ,cw = center.shape

    print("********현재 위치", y,x)
    print("배열 길이",ch, cw)
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
    print("지금 돌고 있는 어레이")
    print(c)
    print("max : ", max)
    print("여기서 제일 큰 i j는 ",ti,tj)

    if(ti == 0 and tj ==0):
        print("리턴 좌표1= ",ti+y, tj+x)
        return [ti+y, tj+x]
        print("리턴함?")
    elif recnt ==0:
        print("리턴 좌표2= ",ti+y, tj+x)
        return [ti+y, tj+x]
        print("리턴함?")
    else:
        print("한번 더",ti+y,tj+x )
        if(ti+y+h > ch or tj+x+h >cw):
            print("펑")
            print(ti+y, tj+x)
            return [ti+y, tj+x]
        recnt = recnt -1
        largesearch0(ti+y,tj+x, center, h, recnt) 



data1 = np.array([[1,2,3],
                  [4,5,6],
                  [7,8,9]])
print(data1)
data2 = np.array([  [0,0,0,1,1,1,0,0,1,0,0,1],
                    [8,5,3,0,6,2,2,8,3,0,0,0],
                    [2,2,4,6,9,5,16,18,2,0,0,0],
                    [5,4,5,4,8,7,7,3,0,0,0,0],
                    [1,1,2,2,1,10,8,5,1,0,0,0],
                    [2,3,3,3,2,1,3,3,3,3,2,0]  ])
h,w = data2.shape

print(data2)

print(h,w)

for i in range(0,h):
    for j in range(0, w):
        print(data2[i][j], end=' ')
    print("\n")


sh = 3
centerlist = []
sampplemlsit = []
for i in range(0,h-sh):
    for j in range(0, w-sh):
        if(data2[i][j] > 4):
            print("여기서는? ", i,j)
            sampplemlsit = largesearch0(i,j, data2, sh, 5)
            print(sampplemlsit)
            #print(a,b)
            centerlist.append(sampplemlsit)
            print("함수 성공")



print(centerlist)
print(len(centerlist))