file = open("a.txt", 'w')
print(file)

if not(file.closed):
    file.write("아름다운 파이썬은 지랄\n")
    file.write("누군가가 사라져야 나라가 산다\n")
    file.close()
else:
    print("파일을 열수 없습니다")

try:
    file = open("d:\\a.txt", 'w')
    file.write("아름다운 파이썬\n")
    file.close()
except:
    print("파일을 열수 없습니다")