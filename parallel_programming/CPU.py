def main():
    arr = [15 for i in range(20)]
    arr[0] = 14
    printArr(arr)
    addone(arr)
    printArr(arr)
    addone(arr)
    printArr(arr)
    addone(arr)
    printArr(arr)


def printArr(arr):
    lookUp = "0123456789ABCDEF"
    strArr = [lookUp[i] for i in arr]
    print(''.join(map(str, reversed(strArr))))

    #print('-'.join(map(str, reversed(arr))))


def toStringArr(arr):
    lookUp = "0123456789ABCDEF"
    strArr = [lookUp[i] for i in arr]
    return(''.join(map(str, reversed(strArr))))


def addone(arr):
    arr[0] += 1

    for i in range(len(arr)-1):
        if arr[i] == 16:
            arr[i] = 0
            arr[i+1] += 1
            if i == len(arr)-1:
                arr[i+1] = 0
        else:
            return


if __name__ == "__main__":
    main()

