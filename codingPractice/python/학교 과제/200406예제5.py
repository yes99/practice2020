i = int(input("숫자1? "))
j = int(input("숫자2? "))

print(i, "+", j, "=", end="")
answer =int(input("?"))

if answer == i + j:
    print("정답입니다")
else:
    print("틀렸습니다")
