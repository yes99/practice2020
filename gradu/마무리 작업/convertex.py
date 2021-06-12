import re
path = "ims/2/a"
paths = [os.path.join(path , i ) for i in os.listdir(path) if re.search(".png$", i )]
## 정렬 작업
store1 = []
store2 = []
for i in paths :
    if len(i) == 19 :
        store2.append(i)
    else :
        store1.append(i)

paths = list(np.sort(store1)) + list(np.sort(store2))
#len('ims/2/a/2a.2710.png')



pathIn= './ims/2/'
pathOut = './ims/2/gan.mp4'
fps = 30
import cv2
frame_array = []
for idx , path in enumerate(paths) : 
    if (idx % 2 == 0) | (idx % 5 == 0) :
        continue
    img = cv2.imread(path)
    height, width, layers = img.shape
    size = (width,height)
    frame_array.append(img)
out = cv2.VideoWriter(pathOut,cv2.VideoWriter_fourcc(*'DIVX'), fps, size)
for i in range(len(frame_array)):
    # writing to a image array
    out.write(frame_array[i])
out.release()