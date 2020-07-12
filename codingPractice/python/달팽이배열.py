# 입력 받기
number = int(input("정사각형의 크기: "))

# 이 부분은 파이썬의 반올림 함수의 특징 때문에 0.1을 더했음.
# https://wikidocs.net/21113 의 '사사오입 원칙' 참고
MAX_CYCLE = round(number/2 + 0.1)
print("반복해야 하는 횟수: " + str(MAX_CYCLE))

# 정사각행렬 만들기
array = [[0] * number for x in range(number)]

# 변수 선언해둔다
count = 0
current_number = 0
x_offset, y_offset = 0, 0

while count < MAX_CYCLE:
    # 현재 마지막 사이클이면서, number가 홀수이면 가운데에 하나만 들어가면 된다.
    if number%2 == 1 and count == MAX_CYCLE-1:
        array[y_offset][x_offset] = current_number
        break
    # 그 외에는 전부 4번씩 하는 것처럼 카운트 가능
    else:
        current_cycle_length = number - 1 - 2 * count
        # 위쪽줄의 숫자를 채운다
        for i in range(current_cycle_length):
            array[y_offset][x_offset + i] = current_number
            current_number += 1

        # 오른쪽줄의 숫자를 채운다
        for i in range(current_cycle_length):
            array[y_offset + i][x_offset + current_cycle_length] = current_number
            current_number += 1

        # 아랫쪽줄의 숫자를 채운다
        for i in range(current_cycle_length):
            array[y_offset + current_cycle_length][x_offset + current_cycle_length - i] = current_number
            current_number += 1

        # 왼쪽줄의 숫자를 채운다
        for i in range(current_cycle_length):
            array[y_offset + current_cycle_length - i][x_offset] = current_number
            current_number += 1
        x_offset, y_offset = x_offset + 1, y_offset + 1

    count += 1

print("정사각행렬 결과")
for line in array:
    string = ""
    for num in line:
        string = string + str(num) + " "
    print(string)
