string = input("문자열 입력해보세요")
l = len(string)
for i in range(l,0,-1):
    print(string[i-1], end="")

print()

for i in range (0, l):
    print(string[l-i-1], end = "")