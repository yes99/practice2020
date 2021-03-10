import numpy as np
import cv2

def histogram_equalization(yi):
    height, width = yi.shape
    yo = np.empty([height, width], dtype=float)

    histogram = [0] * 256
    prob = [0] * 256
    cdf = [0] * 256
    s = [0] * 256
    output = [0] * 256

    for x in range(width) :
        for y in range(height) :
            histogram[round(yi[y][x])] += 1

    for i in range(256) :
        prob[i] = histogram[i] / (height * width)
        cdf[i] = prob[i]

    for i in range(1,256) :
        cdf[i] += cdf[i-1]

    for i in range(256) :
        s[i] = round(cdf[i] * 255)
        output[s[i]] += histogram[i]

    for x in range(width) :
        for y in range(height) :
            yo[y][x] = s[round(yi[y][x])]

    return yo


def transform(img) :
    nimg = img.astype(dtype='int64')
    height, width, color = nimg.shape

    io = nimg

    # yi : Y, yo : Y를 히스토그램 평활화 한 결과
    yi = np.empty([height, width], dtype = float)
    yo = np.empty([height, width], dtype = float)

    # io 의 rgb 영역
    nb = np.zeros((height, width), dtype = float)
    ng = np.zeros((height, width), dtype = float)
    nr = np.zeros((height, width), dtype = float)

    #이미지 RGB 분리
    b,g,r = cv2.split(nimg)

    # Y 계산
    for x in range(width):
        for y in range(height):
            yi[y][x] = (0.257) * (r[y,x]) + (0.504) * (g[y,x]) + (0.098) * (b[y,x]) + 16
    print("네놈이냐? 범인은")
    print(yi)
    # Yi를 히스토그램 평활화
    yo = histogram_equalization(yi)


    ss = 0.5 # 0.0 ~ 1.0 사이의 값
    for x in range(width) :
        for y in range(height) :
            for z in range(color) :
                io[y][x][z] = round(yo[y][x] *((img[y][x][z] / yi[y][x]) ** ss))


    for x in range(width) :
        for y in range(height) :
            nb[y][x] = io[y][x][0]
            ng[y][x] = io[y][x][1]
            nr[y][x] = io[y][x][2]
            if nb[y][x] < 0:
                nb[y][x] = 0
            elif nb[y][x] > 255:
                nb[y][x] = 255
            if ng[y][x] < 0:
                ng[y][x] = 0
            elif ng[y][x] > 255:
                ng[y][x] = 255
            if nr[y][x] < 0:
                nr[y][x] = 0
            elif nr[y][x] > 255:
                nr[y][x] = 255

    print("yi")
    print(yi)
    print("yo")
    print(yo)
    print()

    print("nr")
    print(nr)
    print()

    print("ng")
    print(ng)
    print()

    print("nb")
    print(nb)
    print()

    io = cv2.merge((nb, ng, nr))
    print("*** check done ***")
    return io


if __name__ == "__main__" :
    in_image = cv2.imread('dgu_night_color.png', cv2.IMREAD_COLOR)
    #in_image = cv2.imread('test3.png', cv2.IMREAD_COLOR)
    out_image = transform(in_image)

    cv2.imshow('Input Image', in_image)
    cv2.imshow('Result Image', out_image)

    cv2.imwrite('dgu_night_color_histogram.png', out_image)

    cv2.waitKey(0)

    cv2.destroyAllWindows()
