try:
    file = open("a.txt", 'rt')
    buff = file.readline()

    while buff !='':
        print(buff.strip())
        buff=file.readline()

    file close()
except:
    print("파일을 열수 없습니다.")

    