import cv2
 
capture = cv2.VideoCapture('ffff.mp4')
 
while capture.isOpened():
    run, frame = capture.read()
    width = capture.get(cv2.CAP_PROP_FRAME_WIDTH)
    height = capture.get(cv2.CAP_PROP_FRAME_HEIGHT)
    print(width, height)
    if not run:
        print("[프레임 수신 불가] - 종료합니다")
        break
    img = cv2.cvtColor(frame, cv2.IMREAD_COLOR)
    cv2.imshow('video', frame)
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break
 
capture.release()
cv2.destroyAllWindows()