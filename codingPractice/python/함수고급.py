def print_star(*star): #*star뭐야? C언어의 가변형? 여러개의 매개변수?
    for star_num in star: #그래서 난  스타넘을 정의한적이 없다고요
        for num in range(0, star_num, 1):
            print('*', end='')
        print('')

print_star(1,2,3)
print_star(1,3,5,7,9)
