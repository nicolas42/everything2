import cv2
import numpy as np
import time

filename = "/Users/Nick/bitwise/data/GH040007.mp4"
cap = cv2.VideoCapture(filename)
success,img = cap.read()
height, width, channels = img.shape
successive_failures = 0
total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT)) # opencv3

# out = cv2.VideoWriter('output.avi',cv2.VideoWriter_fourcc(*"XVID"), 20.0, (width,height))


frame_count = 0
paused = False
while successive_failures < 50:

    # respond to keyboard input
    key = cv2.waitKey(33) 
    # print(key)
    if key in [ 27, 113 ]: # escape, q
        break
    elif key == 32: # space
        paused = not paused

    if paused:
        time.sleep(0.1)
        continue

    # read frame
    success,img = cap.read()
    if not success:
        successive_failures += 1
        print('bad frame ¯\_(ツ)_/¯')
        continue
    else:
        successive_failures = 0

    frame_count += 1
    # print on one line with carriage return
    print('frame ' + str(frame_count) + ' / ' + str(total_frames) + '\r', end="")

    # resize img
    scale = 0.5
    if scale != 1:
        width = int(img.shape[1] * scale)
        height = int(img.shape[0] * scale)
        img = cv2.resize(img, (width, height), interpolation = cv2.INTER_AREA)


    #   cv2.imwrite("frame%d.jpg" % frame_count, img)     # save frame as JPEG file
    cv2.imshow('output',img)

    # out.write(img)
        



cap.release()
cv2.destroyAllWindows()
