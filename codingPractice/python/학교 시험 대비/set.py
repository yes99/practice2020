#세트의 항목간에는 순서 존재 x
numbers = {2, 1, 3}
print(numbers)
len(numbers)
print(len(numbers))

if 1 in numbers:
	print("집합 안에 1이 있습니다.")

for x in numbers:
	print(x, end=" ")

numbers.add(4)
print(numbers)