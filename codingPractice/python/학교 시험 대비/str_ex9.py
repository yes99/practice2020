print("***문자열 입력 프로그램***")
sentence = ""
while True:
    word = input("문자열을 입력하세요")
    sentence = sentence + word
    print(sentence)
    if word == "" :
        break
l=len(sentence)
count = 0
for i in range(0,l):
    if sentence[i] == 'a':
        count = count +1
print("종료! 문자 a는 총%d번 사용되었습니다"%count)