
import datetime

now=datetime.datetime.now()

print("** 파일저장 프로그램 **")
name = input("저장할 파일 이름:")

f = open(name, "a")
number = int(input("저장할 라인 수:"))

for i in range(1, number+1):
    print(i,end="")
    data = input(":")
    f.write("%02d:%02d:%02d "%(now.hour, now.minute, now.second)+data.replace(" ","_"))
    f.write("\n")
f.close()
print("저장완료")

f = open(name, "r")
while True:
    line = f.readline()
    if not line: break
    print(line,end="")
f.close()
