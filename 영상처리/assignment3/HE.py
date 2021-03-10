import cv2
import numpy as np
import math


def histogram_equalize(img):
    image = np.asarray(img, dtype=float)

    # height, width : 세로, 가로 길이
    # ints_array는 histgoram 값을 저장하는 배열. 0~255 중 ints값에 해당하는 부분 +1
    ints_array = np.zeros(256)
    height, width = image.shape[:2]
    for i in range(0, height):
        for j in range(0, width):
            ints = (image[i, j]) #반올림 미리 해주자 , y값들은 일단 다 소수이기때문에
            ints = math.ceil(ints)
            image[i, j] = ints
            ints_array[ints] = ints_array[ints] + 1

    #MN = 0
    #for i in range(0, 256):
    #    MN = MN + ints_array[i]
    #print(MN)
    print(height*width)
    # 0~255 각 값이 이미지 내에 등장할 확률을 계산 (히스토그램값 / 전체넓이)
    array_pdf = ints_array / (height*width)

    # cdf의 초깃값은 array_pdf로 먼저 초기화 한 뒤 (cdf[1] = cdf[0] + cdf[1]) -> (cdf[2] = cdf[1] + cdf[2]) -> ...
    CDF = 0
    CDF_accu = np.zeros(256)
    for i in range(256):
        CDF = CDF + array_pdf[i]
        CDF_accu[i] = CDF

    # 결과 gray level을 구한다. => complete_his_array 
    complete_his_array = np.zeros(256)
    complete_his_array = (CDF_accu * 255)
    for i in range(256):
        complete_his_array[i] = math.ceil(complete_his_array[i])
        if (complete_his_array[i] > 255):
            complete_his_array[i] = 255

    # output histogram p(s) => finalimg(complete_his_array)
    finalimg = np.zeros(img.shape)
    for i in range(0, height):
        for j in range(0, width):
            for value in range(0, 255): #value를 한바뀌 쭉 돌면서 맞는거가 있나 찾는과정, 맞는거는 분명히 있게 설계된다
                if (image[i, j] == value):
                    finalimg[i, j] = complete_his_array[value]
                    break

    cv2.imwrite('histogram_equalize.png', finalimg)
    return finalimg


input_image = cv2.imread('kei.png', 0)
hisy = histogram_equalize(input_image)
#cv2.imwrite("histogram",hisy)
cv2.waitKey(0)
cv2.destroyAllWindows()

