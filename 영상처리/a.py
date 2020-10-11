import numpy as np
import cv2

def histogram():
    img = cv2.imread('kei.png', cv2.IMREAD_GRAYSCALE)

    hist, bins = np.histogram(img.ravel(), 256, [0, 256])
    print("hist\n")
    print(hist)
    print("\n\n\n\n")

    print("bins\n")
    print(bins)
    print("\n\n\n\n")


    cdf = hist.cumsum()
    print("cdf1 이때는 누적이 한번 됨\n")
    print(cdf)
    print("\n\n\n\n")
    
    cdf_m = np.ma.masked_equal(cdf,0)
    print("cdf_m1\n")
    print(cdf_m)
    print("\n\n\n\n")
    
    cdf_m = (cdf_m-cdf_m.min())*255/(cdf_m.max()-cdf_m.min())
    print("cdf_m.min()\n")
    print(cdf_m.min())
    print("\n\n")
    print("cdf_m.max()\n")
    print(cdf_m.max())

    print("cdf_m2\n")
    print(cdf_m)
    print("\n\n\n\n")
    print("cdf_m-cdf_m.min()")
 
    print(cdf_m-cdf_m.min())
    print("\n\n\n\n")


    cdf = np.ma.filled(cdf_m, 0).astype('uint8')
    print("cdf2\n")
    print(cdf)
    print("\n\n\n\n")

    img2 = cdf[img]
    


    cv2.imshow('aaa', img)



    cv2.imshow('HISTOGRAM EQUALIZATION' , img2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

histogram()