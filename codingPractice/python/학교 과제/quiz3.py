print("라인 수?", end="")
num=int(input())


for k in range(num):
    for j  in range (k):
        print(" ", end="")
    for l in range(num-k):
        print("*", end="")
    print()   

        