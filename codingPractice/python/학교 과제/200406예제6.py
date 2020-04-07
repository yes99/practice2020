i = int(input("숫자1? "))
j = int(input("숫자2? "))

print(i, "+", j, "=", end="")
a1 =int(input("?"))

print(i, "-", j, "=", end="")
a2 =int(input("?"))

print(i, "*", j, "=", end="")
a3 =int(input("?"))


r1 = i+j
r2 = i-j
r3 = i*j

avg =0
if r1 == a1:
    avg=avg+1
if r2 == a2:
    avg=avg+1
if r3 == a3:
    avg=avg+1
    
print("당신의 점수는", avg/3*100, "입니다")


