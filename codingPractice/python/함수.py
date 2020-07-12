def print_star(star):
    for num in range(0, star, 1):
        print('*', end='')


print_star(5)
print_star(10)

def max(a,b):
    if a>=b:
        return a
    return b

print(max(50,100))