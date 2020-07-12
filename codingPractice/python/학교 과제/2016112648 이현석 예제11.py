import random

print("***덧셈 연산 프로그램***")
print("-1을 입력하면 종료")


cnt =0
correct = 0
while True:
    i = random.randint(1,21)
    j= random.randint(1,21)
    print(i, "+", j, "=", end="")
    q =int(input("?"))
    if q == -1:
        break
    if q == i + j:
        print("맞았습니다.")
        cnt = cnt +1
        correct = correct + 1

    else:
        print("틀렸습니다")
        cnt = cnt +1
   
print("총", cnt, "문제 중", correct,"문제 맞힘")
print(correct/cnt*100,"점")