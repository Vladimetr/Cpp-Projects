# детектирование знака Кирпич: границы + выбор цветового порога
# *добавить проверку на красный оттенок > 15 %
import cv2 as cv
import numpy as np
import time
# White Treshold
MIN_THRESHOLD = 50 
PERCENT_AREA = 0.75
threshold = 0
alpha = 0.2     # transparency

# 0 - web - Camera
# 1 - USB - Camera
cam = cv.VideoCapture(0)	
time.sleep(1)

while cv.waitKey(1) != 27:
    check, frame = cam.read()
    if not check:
        print("Cam ERROR...")
        break;
    
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    gray = cv.GaussianBlur(gray, (5, 5), 0)
    edges = cv.Canny(gray, 30, 150)         # can change!!!

    # find contours
    contours, _ = cv.findContours(edges, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

    # Try to detect Edges
    edgesDetect = False
    if contours:
        contours = sorted(contours, key=cv.contourArea, reverse = True)
        for contr in contours:
            (x,y,w,h) = cv.boundingRect(contr)
            if w / h > 2.5 and w/h < 4.6:   
                area = cv.contourArea(contr)
                percent_area = area / (w*h)

                if percent_area > PERCENT_AREA:
                    gray2 = gray.copy()
                    gray2 = gray2[y:y+h, x:x+w]
                    hist = cv.calcHist([gray2],[0],None,[256],[0,256])
                    value = np.argmax(hist) - 10;                       # new threshold

                    # ROI SIGN
                    x_center = x + w//2;     y_center = y + h//2
                    point0 = (x_center - int(1.5*w/2), y_center - int(1.5*w/2))
                    point1 = (x_center + int(1.5*w/2), y_center + int(1.5*w/2))

                    if value > MIN_THRESHOLD:
                        threshold = value
                        overlay = frame.copy()
                        cv.rectangle(overlay, point0, point1, (0, 255, 0), -1)   # Green
                        cv.addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame)
                        cv.rectangle(frame, point0, point1, (0, 255, 0), 2)        # Green
                        edgesDetect = True
    
    # Detect with Color Threshold
    if edgesDetect == False and threshold != 0:
        mask = np.zeros_like(gray)
        mask[gray > threshold] = 255
        contours, _ = cv.findContours(mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

        if contours:
            contours = sorted(contours, key=cv.contourArea, reverse = True)
            for contr in contours:
                (x,y,w,h) = cv.boundingRect(contr)
                if w / h > 2.5 and w/h < 4.6:   
                    area = cv.contourArea(contr)
                    percent_area = area / (w*h)

                    if percent_area > 0.75:
                        # ROI SIGN
                        x_center = x + w//2;     y_center = y + h//2
                        point0 = (x_center - int(1.5*w/2), y_center - int(1.5*w/2))
                        point1 = (x_center + int(1.5*w/2), y_center + int(1.5*w/2))

                        overlay = frame.copy()
                        cv.rectangle(overlay, point0, point1, (0, 255, 0), -1)              # Green
                        cv.addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame)
                        cv.rectangle(frame, point0, point1, (0, 255, 0), 2)                   # Green 
    
    cv.imshow("cam", frame)

cam.release()
cv.destroyAllWindows()