import cv2
import numpy as np
import copy
import math
import time

def opticalFlow(img,img2):
    start = time.time()
    image = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    image2 = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
    image = cv2.resize(image, (image.shape[0]//4//4,image.shape[1]//4//4)) 
    image2 = cv2.resize(image2, (image.shape[0]//4//4,image.shape[1]//4//4)) 
    topCornerImg = copy.copy(img)
    k = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    ix = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    iy = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    ixx = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    ixy = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    iyy = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    it =  np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    ixt = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    iyt = np.zeros((image.shape[0]//4, image.shape[1]//4, 1), np.float32)
    u = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    v = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    theta = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    mag = np.zeros((image.shape[0]//4,image.shape[1]//4,1),np.float32)
    visualization = np.zeros((image.shape[0]//4,image.shape[1]//4,3),np.float32)
    visualizationx = np.zeros((image.shape[0]//4, image.shape[1]//4, 3), np.float32)
    visualizationy = np.zeros((image.shape[0]//4, image.shape[1]//4, 3), np.float32)
    arrows = np.zeros((image.shape[0]//4,image.shape[1]//4,3),np.float32)
    np.seterr(divide='ignore',invalid='ignore')
    end = time.time()




    print("Initialization time: ", end - start)



    start = time.time()
    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            if(j>0 and j<image.shape[1]//4-1):
                ix[i][j] = int(image[i][j-1]) - int(image[i][j+1])
    end = time.time()
    print("Ix time: ", end - start)
    start = time.time()

    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            if(i>0 and i<image.shape[0]//4-1):
                iy[i][j] = int(image[i-1][j]) - int(image[i+1][j])
    end = time.time()
    print("Iy time: ", end - start)
    start = time.time()

    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):

            ixx[i][j] = ix[i][j]*ix[i][j]
    end = time.time()
    print("Ixx time: ", end - start)
    start = time.time()





    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):

            iyy[i][j] = iy[i][j]*iy[i][j]
    end = time.time()
    print("Iyy time: ", end - start)
    start = time.time()





    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):

            ixy[i][j] = ix[i][j]*iy[i][j]
    end = time.time()
    print("Ixy time: ", end - start)
    start = time.time()

    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            it[i][j] = int(image2[i][j]) - int(image[i][j])
    end = time.time()
    print("It time: ", end - start)
    start = time.time()

    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            ixt[i][j] = ix[i][j] * it[i][j]
            iyt[i][j] = iy[i][j] * it[i][j]
    end = time.time()
    print("Ixt and Iyt time: ", end - start)
    maxMag = 0
    maxu = 0
    maxv = 0
    start = time.time()
    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            ixxsum = 0
            iyysum = 0
            ixysum = 0
            ixtsum = 0
            iytsum = 0
            for l in range(-6,7):
                for m in range(-6,7):
                    if((i+l>0 and i+l<image.shape[0]//4) and (j+m>0 and j+m<image.shape[1]//4)):

                        


                        ixxsum += ixx[i+l][j+m]
                        iyysum += iyy[i + l][j + m]
                        ixysum += ixy[i + l][j + m]
                        ixtsum += ixt[i+l][j+m]
                        iytsum += iyt[i+l][j+m]


            if((ixxsum*iyysum)-(ixysum*ixysum) == 0):
                u[i][j] = 0
                v[i][j] = 0
                theta[i][j] = 0
            else:

                u[i][j] = ((-iyysum*ixtsum) + ixysum*iytsum)/((ixxsum*iyysum)-(ixysum*ixysum))
                v[i][j] = ((ixysum*ixtsum) - (ixxsum*iytsum))/((ixxsum*iyysum)-(ixysum*ixysum))
                theta[i][j] = math.atan2(v[i][j], u[i][j])



            mag[i][j] = math.sqrt((u[i][j]**2) + (v[i][j]**2))
            if (mag[i][j] > maxMag):
                maxMag = mag[i][j]
            if (maxMag == 0):
                maxMag = 1

    print("연산완료")
    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            b = (255 / (2 * math.pi)) * (theta[i][j] + math.pi) * (mag[i][j])
            g = (255 + (-255 / (2 * math.pi)) * (theta[i][j] + math.pi)) * (mag[i][j])
            visualization[i][j][0] = b
            visualization[i][j][1] = g
    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            b = (255 / (2 * math.pi)) * (theta[i][j] + math.pi) * (u[i][j])
            g = (255 + (-255 / (2 * math.pi)) * (theta[i][j] + math.pi)) * (u[i][j])
            visualizationx[i][j][0] = b
            visualizationx[i][j][1] = g
    for i in range(image.shape[0]//4):
        for j in range(image.shape[1]//4):
            b = (255 / (2 * math.pi)) * (theta[i][j] + math.pi) * (v[i][j])
            g = (255 + (-255 / (2 * math.pi)) * (theta[i][j] + math.pi)) * (v[i][j])
            visualizationy[i][j][0] = b
            visualizationy[i][j][1] = g


    end = time.time()
    print("Max magnitude = ", maxMag)
    print("Summmations, magnitude, and angle time: ", end - start)
    start = time.time()

    for i in range(0,image.shape[0]//4,5):
        for j in range(0,image.shape[1]//4,5):
            scaleflow = 15*(mag[i][j] / maxMag)
            #print("u,v at i,j: ",i," ",j," ","u= ", u[i][j]," v = ",v[i][j], " Angle: ", math.atan2(scaleflow*v[i][j],scaleflow*u[i][j])*(180/math.pi))

            cv2.arrowedLine(arrows,(j,i),((int(((scaleflow*u[i][j]) + j))),(int((i+(scaleflow*v[i][j]))))),(0,255,0))
    end = time.time()
    print("arrows time: ", end - start)

    cv2.imshow("arrows",arrows/255)
    cv2.waitKey()
    cv2.waitKey()

    cv2.imshow("visual",visualization/255)
    cv2.waitKey()
    cv2.waitKey()


    cv2.imshow("visualx",visualizationx/255)
    cv2.waitKey()
    cv2.waitKey()

    cv2.imshow("visualy",visualizationy/255)
    cv2.waitKey()
    cv2.waitKey()








def main():


    image1 = cv2.imread("circle.png")
    image2 = cv2.imread("circle2.png")
    opticalFlow(image1,image2)











if __name__ == "__main__":
    main()