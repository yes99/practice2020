print("*****순차 합을 구하는 프로그램******")
k = int(input("어디부터의 합을 구할가요?"))
l = int(input("어디까지의 합을 구할까요?"))


add = 0
for i in range (k ,l+1):
    add = add + i

print(k,"부터", l, "까지의 합은", add, "입니다")