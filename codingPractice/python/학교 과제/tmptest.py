f=open("memo.txt", "r")
while True:
     readText=f.readline() # 다른 일기함수: read(), readlines()
     if readText=="": # readText 에 읽은 내용이 없을경우
          break            # if readText=="" 혹은  if not readText: 사용
     print(readText)
f.close()
