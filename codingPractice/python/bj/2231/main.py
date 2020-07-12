N = int (input())
strN = str(N)
strArray = list(strN)
digitsArray = []
for i in strArray:
    digitsArray.append(int(i))

sumOfDigits = sum(digitsArray)
print(sumOfDigits)