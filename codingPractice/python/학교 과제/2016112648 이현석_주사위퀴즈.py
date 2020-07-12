#2016112648 이현석 퀴즈1

import math
import random

print("*** 주사위 평균 프로그램 ***")
print("주사위 2개를 몇번 굴릴까요?",end="")
throw=int(input())
sum = 0
total = 0
for k in range(1, throw):
    i = random.randint(1,6)
    j = random.randint(1,6)
    sum =  sum+ i + j
    total = total + i + j
    print(i, j, ", ", end="")
    if k % 10 ==0:
        print("평균", sum/10)
        print()
        sum = 0
totalavg = round(total/throw, 2)
print("\n총", throw,"회 평균 =", totalavg)



