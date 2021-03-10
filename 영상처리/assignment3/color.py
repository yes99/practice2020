import numpy as np
import cv2


img = cv2.imread('dgu_night_color.png',cv2.IMREAD_COLOR)
cv2.imshow("color", img)
img_b,img_g,img_r = cv2.split(img)

height,width, channel=img.shape

zeros = np.zeros((img.shape[0],img.shape[1]),dtype="uint8")
img_b = cv2.merge([img_b,zeros,zeros])
img_g = cv2.merge([zeros,img_g,zeros])
img_r = cv2.merge([zeros,zeros,img_r])

cv2.imshow("color", img)
cv2.imshow("b",img_b)
cv2.imshow("g", img_g)
cv2.imshow("r", img_r)
print(height)
print(width)

for i in range(width):
    for j in range(height):
        



cv2.waitKey(0)

cv2.destroyAllWindows()
