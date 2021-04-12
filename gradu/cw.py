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


# surf 함수로 지정
def SURF(frame):
    img1 = cv2.imread('query.jpg')
    img2 = frame
    gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    # gray1 = cv2.Canny(gray1, 100,255)
    # gray2 = cv2.Canny(gray2, 100, 255)

    # ORB, BF - Hamming 로 knnMatch-- - ①
    detector = cv2.xfeatures2d.SURF_create()
    kp1, desc1 = detector.detectAndCompute(gray1, None)
    kp2, desc2 = detector.detectAndCompute(gray2, None)
    matcher = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
    matches = matcher.match(desc1, desc2)

    # 매칭 결과를 거리기준 오름차순으로 정렬-- - ③
    matches = sorted(matches, key=lambda x: x.distance)
    # 모든 매칭점 그리기-- - ④
    res1 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                           flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)

    # 매칭점으로 원근 변환 및 영역 표시-- - ⑤
    src_pts = np.float32([kp1[m.queryIdx].pt for m in matches])
    dst_pts = np.float32([kp2[m.trainIdx].pt for m in matches])
    # RANSAC으로 변환 행렬 근사 계산-- - ⑥
    # findhomography 원근변환행렬(쿼리와 입력영상 간 매칭된 부분의 좌표를 대응시켜줌) 자체를 구해주는 부분
    mtrx, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 55)
    h, w = img1.shape[:2]
    pts = np.float32([[[0, 0]], [[0, h - 1]], [[w - 1, h - 1]], [[w - 1, 0]]])
    # perspectiveTransform 앞에서 구한 원근변환행렬로 원래의 좌표들을 변환해주는 함수
    dst = cv2.perspectiveTransform(pts, mtrx)

    x_min = min(dst[0][0][0], dst[1][0][0], dst[2][0][0], dst[3][0][0])
    x_max = max(dst[0][0][0], dst[1][0][0], dst[2][0][0], dst[3][0][0])
    y_min = min(dst[0][0][1], dst[1][0][1], dst[2][0][1], dst[3][0][1])
    y_max = max(dst[0][0][1], dst[1][0][1], dst[2][0][1], dst[3][0][1])

    new_pts = np.float32([[[x_min, y_min]], [[x_min, y_max]], [[x_max, y_max]], [[x_max, y_min]]])
    img2 = cv2.polylines(img2, [np.int32(new_pts)], True, 255, 3, cv2.LINE_AA)
    # img2 = cv2.polylines(img2, [np.int32(dst)], True, 255, 3, cv2.LINE_AA)

    # 정상치 매칭만 그리기-- - ⑦
    matchesMask = mask.ravel().tolist()
    res2 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, \
                           matchesMask=matchesMask,
                           flags=cv2.DRAW_MATCHES_FLAGS_NOT_DRAW_SINGLE_POINTS)
    # 모든 매칭점과 정상치 비율-- - ⑧
    accuracy = float(mask.sum()) / mask.size
    print("accuracy: %d/%d(%.2f%%)" % (mask.sum(), mask.size, accuracy))

    return res2


def onMouse(event, x, y, flags, frame):
    global xi, yi, drawing, mode, B, G, R

    cv2.namedWindow('image')
    cv2.imshow('image', frame)  # 화면에 표시  --- ③

    # 마우스 눌렀을때
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        global xi, yi
        xi, yi = x, y

        print("마우스 누름")
    # 마우스 뗏을때
    elif event == cv2.EVENT_LBUTTONUP:
        print("마우스 땟음")

        drawing = False
        if mode:
            global x_copy, y_copy
            x_copy, y_copy = x, y
            # 사각형그리기
            cv2.rectangle(frame, (xi, yi), (x_copy, y_copy), (0, 225, 0), 3)
            print(xi, yi, x_copy, y_copy)


# 콜백추가
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
cnt1 = 0  # 현재 프레임 표시용 변수
cap = cv2.VideoCapture(video_file)  # 동영상 캡쳐 객체 생성  ---①

# 동영상 크기 설정이다, 나중에 정말로 필요하더라.
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

print("width = %d  height = %d" % (width, height))  # 디버깅 한번 해주고

if cap.isOpened():  # 캡쳐 객체 초기화 확인
    while True:
        ret, img = cap.read()  # 다음 프레임 읽기      --- ②
        # cv2.imshow("첫장면", img)
        t0 = img
        t1 = img
        t2 = img
        t3 = img
        t4 = img
        break

imglist = [t0, t1, t2, t3, t4]

t = 0  # psnr 값 비교를 위한 초기화
fc = 0  # flag change의 약자임, 플래그로 두번 멈추는거 컨트롤 하려고 만들었음

p = 0
cnt = 0  # 프레임 번호 세는 용도
tavg = 0.0  # 바로 전의 평균
mouseflag = 0
count = 1  # 사용하지 않는 변수
if cap.isOpened():  # 캡쳐 객체 초기화 확인
    print("열림")
    while True:
        # 동영상 한프레임씩 읽어오는중...아래부분에서 중복은 함수로 빼거나 해야될것같다
        ret, img = cap.read()  # 다음 프레임 읽기
        newimg = img.copy()
        #   --- ②
        psnrV0 = psnr(imglist[0], imglist[1])
        psnrV1 = psnr(imglist[1], imglist[2])
        psnrV2 = psnr(imglist[2], imglist[3])
        psnrV3 = psnr(imglist[3], imglist[4])
        psnrV4 = psnr(imglist[4], img)
        avg = (psnrV0 + psnrV1 + psnrV2 + psnrV3 + psnrV4) / 5
        cnt = cnt + 1
        print("%.2f  %.2f %.2f %.2f %.2f " % (psnrV0, psnrV1, psnrV2, psnrV3, psnrV4))
        print("평균값 %.2f %.2f" % (avg, tavg))
        # 현재평균 - 바로 전 평균
        sub = avg - tavg
        sub = abs(sub)
        sub1 = psnrV4 - psnrV3  # 현재 프레임과 바로전 프레임의 psnr 차이
        sub1 = abs(sub1)
        text = "avg: %.2f, sub: %.2f sub1 : %.2f" % (avg, sub, sub1)
        text1 = "psnr: %.2f, frame: %d" % (psnrV4, cnt)

        if ret:  # 프레임 읽기 정상일 경우
            print(" 프레임 읽기 정상일 경우")
            space = cv2.waitKey(1) & 0xFF

            if space == 32:
                cv2.namedWindow('image')
                print("space img")
                cv2.imshow('image', img)  # 화면에 표시  --- ③
                cv2.setMouseCallback('image', onMouse, param=img)
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
                        cv2.destroyAllWindows()
                        print("r img")
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
            if sub > 1 and sub1 > 1:
                print("sub 통과")
                cnt3 = "double stop"
                # cv2.putText(img, text3, (50, 400), cv2.FONT_HERSHEY_DUPLEX, 3, (0, 200, 0), 10)
                fc = 1  # 한번 멈추면 분명 그 다음에 또 같은 이유로 멈춰서 플래그를 세워준다
                cv2.namedWindow('image')
                print("sub img")
                cv2.imshow('image', img)  # 화면에 표시  --- ③
                cv2.setMouseCallback('image', onMouse, param=img)
                while True:

                    k = cv2.waitKey(1) & 0xFF

                    # 비트연산자 & 로 둘다 1인것만 1 운영체제가 64비트라 이런 과정을 해줘야된대

                    if k == 27:
                        # print("ESC키 눌러짐")
                        print("sub의 esc누름")
                        mouseflag = 1
                        break  # 키보드 while문 탈출
                    # 다시 영역지정
                    elif k == ord('r'):
                        print('r을 누름')

                        img = newimg.copy()
                        cv2.destroyAllWindows()
                        print("r img")
                        cv2.imshow('image', img)
                        cv2.setMouseCallback('image', onMouse, param=img)
                    # surf 시작
                    elif k == ord('s'):
                        print('s를 누름')
                        cv2.destroyAllWindows()
                        # query 저장
                        global cutimg2
                        try:
                            os.remove("query.jpg")
                        except:
                            pass
                        cutimg2 = img[yi:y_copy, xi:x_copy].copy()
                        cv2.imwrite('query.jpg', cutimg2)
                        break

            if mouseflag == 1:
                break


            else:  # 그 외에는 그냥 넘겨
                cv2.waitKey(25)  # 25ms 지연(40fps로 가정)   --- ④

            print("surf img")
            cv2.imshow('result', SURF(img))
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                exit()

        else:  # 다음 프레임 읽을 수 없슴,
            break  # 재생 완료
        tavg = avg
        imglist[0] = imglist[1]
        imglist[1] = imglist[2]
        imglist[2] = imglist[3]
        imglist[3] = imglist[4]
        imglist[4] = img


else:
    print("can't open video.")  # 캡쳐 객체 초기화 실패
cap.release()  # 캡쳐 자원 반납
cv2.destroyAllWindows()