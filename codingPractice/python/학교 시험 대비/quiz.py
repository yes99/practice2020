# 정수값을 입력 한 다음 각 자릿수를 더한다

print("***모든 자리수의 합을 구하는 프로그램***")
print("정수는?",end="")
number=int(input())
a = 10
x = 1
sum = 0

while True:
    b = number % a
    answer = b // x 
    number = number - b 
    print(answer, end="")
    a = a * 10
    x = x * 10
    sum = sum + answer
    if number // b == 0 :
     break
    else:
        print("+",end="")
print("=",sum)