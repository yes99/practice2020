print("***** 간단한 구구단 프로그램 *****")
print("몇 단을 할가요?", end="")
dan=int(input())
print("몇 까지 곱셈을 할가요? ", end="")
to=int(input())
for n in range(1, to +1 ):
    print(dan,"*",n,"=",dan*n,end="")
    if n % 5 == 0:
        print()
 #   if n==to:
  #      print()
        # \n 하기 위해서
    else:
        print(", ", end="")