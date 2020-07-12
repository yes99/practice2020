print("***숫자맞추기 게임***")
print("컴퓨터: 숫자 하나를 선택하셨습니다.")
com = 10
print("당신이 맞춰보세요")

while True:
    i = int(input("맞출 숫자는?"))
    if i == com:
        print("축하합니다. 정답입니다")
        break
    print("틀렸습니다. ", end="")
    if i < com:
        print(i, "보다 큰 숫자입니다")
    else:
        print(i, "보다 작은 숫자입니다.")