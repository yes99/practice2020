print("**자판기 프로그램**")
price=int(input("물건 값을 입력하시오"))

print("자판기에 넣은 돈은?")
a = int (input("1000원 지폐개수:"))
b = int (input("500원 지폐개수:"))
c = int (input("100원 지폐개수:"))

thousand = a * 1000
f_hundred = b * 500
hundred = c * 100
sum = thousand + f_hundred + hundred

leftover = sum - price

fhc=0
hc =0
tc = 0
oc = 0

while True:
    if leftover < 500:
        break
    leftover = leftover - 500
    fhc= fhc + 1

while True:
    if leftover< 100:
        break
    leftover = leftover - 100
    hc= hc+1
while True:
    if leftover< 10:
        break
    leftover = leftover - 10
    tc= tc+1

oc = leftover

print("거스름돈:")
print("500원 =", fhc, "100원 = ", hc, "10원 = ", tc, "1원 = ", oc)