import cv2
import numpy as np
import math
import os

mode, drawing = True, False
# 마우스 눌렀을때 좌표
xi, yi = -1, -1
# 주황색
B = 0
G = 255
R = 0
# 마우스 뗐을 때 좌표
x_copy, y_copy = -1, -1


#surf 함수로 지정
def SURF():
    img1 = cv2.imread('query.jpg')
    img2 = cv2.imread('frame.jpg')
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

    # ORB, BF - Hamming 로 knnMatch-- - ①
    detector = cv2.xfeatures2d.SURF_create()
    kp1, desc1 = detector.detectAndCompute(gray1, None)
    kp2, desc2 = detector.detectAndCompute(gray2, None)
    matcher = cv2.BFMatcher(cv2.NORM_L2, crossCheck = True)
    matches = matcher.match(desc1, desc2)

    # 매칭 결과를 거리기준 오름차순으로 정렬-- - ③
    matches = sorted(matches, key = lambda x : x.distance)
    # 모든 매칭점 그리기-- - ④
    res1 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
        flags = cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)

    # 매칭점으로 원근 변환 및 영역 표시-- - ⑤
    src_pts = np.float32([kp1[m.queryIdx].pt for m in matches])
    dst_pts = np.float32([kp2[m.trainIdx].pt for m in matches])
    # RANSAC으로 변환 행렬 근사 계산-- - ⑥
    mtrx, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 55)
    h, w = img1.shape[:2]
    pts = np.float32([[[0, 0]], [[0, h - 1]], [[w - 1, h - 1]], [[w - 1, 0]] ] )
    dst = cv2.perspectiveTransform(pts, mtrx)
    img2 = cv2.polylines(img2, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)

    # 정상치 매칭만 그리기-- - ⑦
    matchesMask = mask.ravel().tolist()
    res2 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
        matchesMask = matchesMask,
        flags = cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    # 모든 매칭점과 정상치 비율-- - ⑧
    accuracy = float(mask.sum()) / mask.size
    print("accuracy: %d/%d(%.2f%%)" % (mask.sum(), mask.size, accuracy))

    cv2.imshow('Matching-All', res1)
    cv2.imshow('Matching-Inlier ', res2)
    cv2.waitKey()
    cv2.destroyAllWindows()

def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R
    #마우스 눌렀을때
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
        xi, yi=x, y
        print("마우스 누름 %f  %f" %(xi, yi))
    #마우스 뗏을때
    elif event==cv2.EVENT_LBUTTONUP:
        #print("마우스 땟음")
        drawing=False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy=x,y
            # 사각형그리기
            print("마우스 땟음 %f  %f" % (x_copy, y_copy))
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (B, G, R), -1)
        print("사각형은?")
        print("x %f y %f xc %f yc %f" % (xi, yi, x_copy, y_copy))
        cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (B, G, R), -1)


#콜백추가
def mouse_callback(event, x, y, flags, param):
    print("마우스 이벤트 발생, x:", x, "y:", y)



# psnr을 구하는 것을 딱히 미련을 갖지 말자, 대충 [수치를 따져서 앞이랑 전이랑 차이가 크게 나면] 멈춰! 가 나오는 거 정도로 알면된다.
# 발표할 상황이 생기면 내가 알아가서 교수님 앞에서 말하겠다.
# 이거랑 SSIM 이라는 기법이 있다.
def psnr(img1, img2):
    mse = np.mean((img1 - img2) ** 2)
    if mse == 0:
        return 100
    PIXEL_MAX = 255.0
    return 10 * math.log10(PIXEL_MAX / math.sqrt(mse))



video_file = "KAPPA.mp4"  # 동영상 파일 경로   #동영상을 뽑아와야겠지
cnt1 = 0#현재 프레임 표시용 변수
cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성  ---①

# 동영상 크기 설정이다, 나중에 정말로 필요하더라.
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

print("width = %d  height = %d" % (width, height))  # 디버깅 한번 해주고
blank_img = cv2.imread('white.png')  # 흰색 종이를 읽어왔다. # psnr을 앞뒤를 비교하는 거라서 처음에 초기화 할 거리가 필요함.

blank_img = cv2.resize(blank_img, dsize=(int(width), int(height)),
                       interpolation=cv2.INTER_AREA)  # 크기 안맞으면, 나중에 psnr 비교할때 뱉어내서 지금 흰종이 크기를, 맞춰준거임.

timg = blank_img
t = 0  # psnr 값 비교를 위한 초기화
fc = 0  # flag change의 약자임, 플래그로 두번 멈추는거 컨트롤 하려고 만들었음

mouseflag=0

if cap.isOpened():  # 캡쳐 객체 초기화 확인
    print("열림")
    while True:
        ret, img = cap.read()  # 다음 프레임 읽기
        #   --- ②
        psnrV = psnr(timg, img)  # psnr 함수 위에 나온거 쓰는거, 사실 psnr수치 자체가 , 파라미터로 들어간 두 이미지 사이 비교해서 보여주는 거긴 하다.
        # 일단 img는 비디오 프레임 읽어오는거고 t(emp)img 는 맨처음에 흰 종이.
        st = t - psnrV  # standard, 두가지 비교하려고 넣은 값임
        cnt1 = cnt1 + 1  # cnt1은 이미지 저장해서 나올때 이름 비교하려고 만들었음.
        print("abs1")
        st = abs(st)  # 터미널 상에서 차이가 몇이나 나오나 확인하려고 만들었음.
        text = "F: %d, psnr: %f" % (cnt1, psnrV)  # 화면에 해당 이미지의 프레임 넘버    psnr수치,
        #cv2.putText(img, text, (50, 100), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)
        text0 = "t : %f abs:%f" % (t, st)  # 해당 화면의 t 이전 프레임의 psnr 그리고 st는 앞과 뒤의 차이
        #cv2.putText(img, text0, (50, 200), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)

        print(st)
        if ret:  # 프레임 읽기 정상일 경우
            print(" 프레임 읽기 정상일 경우")
            cv2.namedWindow(video_file)
            cv2.setMouseCallback(video_file, onMouse, param=img)
            cv2.imshow(video_file, img)  # 화면에 표시  --- ③

            if (st > 4.6 and fc == 0):  # 해당 psnr 값의 앞 뒤 차이가 1보다 크고 플래그가 0일경우에는
                text3 = "stop here"  # 멈추게 한다.
                #cv2.putText(img, text3, (50, 400), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)
                cv2.imshow(video_file, img)  # 화면에 표시  --- ③

                fc = 1  # 한번 멈추면 분명 그 다음에 또 같은 이유로 멈춰서 플래그를 세워준다

                #cv2.namedWindow('image')
                newimg=img.copy
                #cv2.namedWindow('test')
                #cv2.imwrite('frame.jpg', img)
                #cv2.imshow('frame.jpg', img)
                #cv2.imshow('test', img)
                #cv2.setMouseCallback('frame.jpg', onMouse, param=img)

                print('여기')

                while True:
                    k = cv2.waitKey(1) & 0xFF
                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대
                    if k == 27:
                        # print("ESC키 눌러짐")
                        print("esc누름")
                        mouseflag = 1
                        break  # 키보드 while문 탈출
                    # 다시 영역지정
                    elif k == ord('r'):
                        print('r을 누름')
                        img = newimg.copy()
                        print('r을 누름22')
                        cv2.imshow('image', img)
                        cv2.setMouseCallback('image', onMouse, param=img)
                    # surf 시작
                    elif k == ord('s'):
                        print('s를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg)
                        break

            if mouseflag ==1:
                break
            elif (st > 4.6 and fc == 1):  # st가 1보다 크지만, 이전에 바로 멈춘 상태여서 fc가 1일경우에는 그냥 패스하게 해준다
                fc = 0  # 그리고 fc를 0으로 바꿔라
                text4 = "pass pass"
                #cv2.putText(img, text4, (50, 400), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)
                cv2.imshow(video_file, img)  # 화면에 표시  --- ③

            else:  # 그 외에는 그냥 넘겨
                cv2.waitKey(25)  # 25ms 지연(40fps로 가정)   --- ④

            SURF()


        else:  # 다음 프레임 읽을 수 없슴,
            break  # 재생 완료
        timg = img  # timg 는 일단 이제 그 다음 프레임의 이미지로 바꿔주고
        t = psnrV  # psnrV를 비교하기 위한 t는 현제 psnr 값으로 바꿔준다.

else:
    print("can't open video.")  # 캡쳐 객체 초기화 실패
cap.release()  # 캡쳐 자원 반납
cv2.destroyAllWindows()