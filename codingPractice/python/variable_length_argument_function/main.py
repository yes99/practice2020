
def print_star(*star):
    print(star)

def print_nonstar(nonstar):
    print(nonstar)

print_star(1)
print_star(1,2,3)
print_star(1, 2, 3, 4, 5)

print_nonstar(1)
# print_nonstar(1,2,3) # not working
# print_nonstar(1, 2, 3, 4, 5) # not working

print("How 'Sum' function works:")

def sum(*args):
    sum = 0
    for i in args:
        sum += i
    return sum


print(sum(1))
print(sum(1, 2, 3))
print(sum(1, 2, 3, 4, 5))
