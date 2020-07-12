print("***** 간단한 구구단 프로그램 *****")
dan=int(input())
to=int(input())
for n in range(1, to +1 ):
    print(dan,"*",n,"=",dan*n,end="")
    if n==5:
        print()
    if n==to:
        print()
        # \n 하기 위해서
    else:
        print(",", end="")