import cv2
from cvzone.HandTrackingModule import HandDetector
import socket

cap =cv2.VideoCapture(0)
det = HandDetector(detectionCon=0.8, maxHands=1)

##esp32_ip = ""
##port = 5005
##sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    success, img = cap.read()
    hands, img = det.findHands(img)

    if hands:
        hands1 = hands[0]
        fingers = det.fingersUp(hands1)
        count = sum(fingers)

        ##sock.sendto(str(count).encode(), (esp32_ip, port))

        cv2.putText(img, f'Fingers: {count}', (50,50), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 3)

    cv2.imshow("Hand Tracker", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
