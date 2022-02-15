import cv2
import json
import os, glob
import sys
import numpy as np

# example
# python extract-frames.py 'M16_SBL_C_02_RHS.MP4' True 1000

print(sys.argv)
config_video = sys.argv[1] 
config_rotate = bool(sys.argv[2])
config_start_frames = int(sys.argv[3])

every_n_frame = 5
frame_dir = config_video + '_frames'
if not os.path.exists(frame_dir):
    os.makedirs(frame_dir)

cap= cv2.VideoCapture(config_video)
total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
print('Total frames in {}: {}'.format(config_video, total_frames))

frameno = 0
while(cap.isOpened()):
    ret, frame = cap.read()

    if frameno == config_start_frames:
        frameno = int(total_frames - config_start_frames)
        cap.set(cv2.CAP_PROP_POS_FRAMES, frameno)


    if frameno >= total_frames-1:
        break
    elif ret is False or frameno%every_n_frame != 0:
        frameno+=1
        # print(frameno)
        continue
    elif frameno%every_n_frame == 0:
        # print(frameno)
        imagename = 'frame'+str(frameno)+'.jpg'
        framepath = os.path.join(frame_dir, imagename)

        if config_rotate:
            frame_rotate_180 = cv2.rotate(frame, cv2.ROTATE_180)
        else:
            frame_rotate_180 = frame

        print('write ' + framepath, end='\r')
        cv2.imwrite(framepath, frame_rotate_180)
        frameno+=1


print('')



