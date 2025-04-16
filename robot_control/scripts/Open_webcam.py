import cv2

cap=cv2.VideoCapture(0)
#Checking if the webcam is open correctly or not

if not cap.isOpened():
    raise IOError("Sorry! Cannot is not Openning")
while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame,None,fx=0.8, fy=0.8, interpolation=cv2.INTER_AREA)
    cv2.imshow('Window_Webcame', frame)
    c=cv2.waitKey(1)
    if c== 27:
        break
cap.release()
cv2.destroyAllWindows()