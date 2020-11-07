import cv2
import numpy as np

def nothing(x):
    pass

cap = cv2.VideoCapture(0)

cv2.namedWindow("Trackbars")
cv2.createTrackbar("L - H","Trackbars",0,179,nothing)
cv2.createTrackbar("L - s","Trackbars",0,255,nothing)
cv2.createTrackbar("L - v","Trackbars",0,255,nothing)
cv2.createTrackbar("U - H","Trackbars",0,179,nothing)
cv2.createTrackbar("U - S","Trackbars",0,255,nothing)
cv2.createTrackbar("U - V","Trackbars",0,255,nothing)
while True:
    _,frame = cap.read()
    
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    l_h = cv2.getTrackbarPos("L - H","Trackbars")
    l_s = cv2.getTrackbarPos("L - S","Trackbars")
    l_v = cv2.getTrackbarPos("L - V","Trackbars")
    u_h = cv2.getTrackbarPos("U - H","Trackbars")
    u_s = cv2.getTrackbarPos("U - S","Trackbars")
    u_v = cv2.getTrackbarPos("U - V","Trackbars")

    
    lower_blue=np.array([l_h,l_s,l_v])
    upper_blue= np.array([u_h,u_s,u_v])
    
    mask = cv2.inRange(hsv,lower_blue,upper_blue)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
    
    
    
    
    

    contours, _ = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
   
    cv2.drawContours(frame, contours, -1, (0,255,0), 3)
    cv2.imshow("frame",frame)
    cv2.imshow("mask",mask)
##    for cnt in contours:
##        approx = cv2.approxPolyDP(cnt, .03 * cv2.arcLength(cnt, True), True)
        
        
            

    
    
    
    key = cv2.waitKey(1)
    if key ==27:
        break

cap.release()
cv2.destroyAllWindows()
