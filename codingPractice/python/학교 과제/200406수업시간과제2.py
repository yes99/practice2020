i = int(input("숫자1? "))
j = int(input("숫자2? "))
cnt=0

a1 = int(input(i ,"+", j))
if a1 == i+j:
    cnt = cnt+1
else:
    pass
a2 = int(input(i ,"-" ,j))
if a1 == i-j:
    cnt = cnt+1
else:
    pass
a3 = int(input(i ,"*" ,j))
if a1 == i*j:
    cnt = cnt+1
else:
    pass

print("단신의 점수는", 100/cnt)


