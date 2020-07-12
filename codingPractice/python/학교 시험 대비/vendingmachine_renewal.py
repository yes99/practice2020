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

fh = leftover//500
h = (leftover %500 ) // 100
t = (leftover % 100) // 10
o = (leftover % 10)


print(fh, h, t, o)