print("라인 수?", end="")
num=int(input())
cnt = 0
for k in range(1, num):
    for j  in range (1, cnt):
        print(" ", end="")
    for l in range(1, num-cnt):
        print("*")

        