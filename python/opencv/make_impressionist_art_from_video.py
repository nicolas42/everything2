# https://stackoverflow.com/questions/29317262/opencv-video-saving-in-python
# https://stackoverflow.com/questions/44505504/how-to-make-a-circular-kernel
# https://subscription.packtpub.com/book/application_development/9781785283932/2/ch02lvl1sec24/erosion-and-dilation
# https://www.tutorialkart.com/opencv/python/opencv-python-resize-image/

import cv2
import numpy as np
import sys
import time

def doit(video_filename = 'a.mp4', do_rotate = False, output_video_filename = 'output.avi', scale = 0.5, rotation_value = 0, paused = False):

  
  """
  print(sys.argv)
  video_filename = sys.argv[1]
  do_rotate = sys.argv[2]
  """

  if "s3://" == video_filename[:5]:
      from download_from_s3 import download_from_s3
      download_from_s3(video_filename, 'tmp.mp4')
      video_filename = 'tmp.mp4'

  cap = cv2.VideoCapture(video_filename)
  # scale = 0.5
  width  = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH) * scale)
  height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT) * scale)
  fourcc = cv2.VideoWriter_fourcc(*'XVID')
  out = cv2.VideoWriter(output_video_filename, fourcc, 20.0, (width,height))

  total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
  frame_number = 0
  #frame_number = int(0.99 * total_frames)
  cap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)

  while(cap.isOpened() and frame_number < total_frames):


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

    success, img = cap.read()
    if not success:
        continue
    frame_number += 1
    print(str(frame_number) +'/'+ str(total_frames), end='\r')

    img = cv2.rotate(img, rotation_value) #cv2.ROTATE_180)
    img = cv2.resize(img, (width, height), interpolation = cv2.INTER_AREA)

    kernel = np.ones((10,10), np.uint8)
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(10,10))

    img_erosion = cv2.erode(img, kernel, iterations=1)
    img_dilation = cv2.dilate(img, kernel, iterations=1)
    out.write(img_dilation)

    #   cv2.imwrite("frame%d.jpg" % frame_number, img)     # save frame as JPEG file
    cv2.imshow('output',img_dilation)

  cap.release()
  out.release()
  print('destroying all windows')
  cv2.destroyAllWindows()
  cv2.waitKey(1)


    # cv2.waitKey(1)

    # try:
    #     cv2.imshow('output',img)
    # except:
    #     print('opencv thinks this is a sad frame')
    
#    if cv2.waitKey(10) == 27:                     # exit if Escape is hit
#        break


  


if __name__ == "__main__":
  import argparse
  parser = argparse.ArgumentParser(description='')
  parser.add_argument(
      '-i', '--video_filename', type=str, help='', default='a.mp4')
  parser.add_argument(
      '-o', '--output_video_filename', required=False, type=str, default='output.avi', help='')
  parser.add_argument(
      '-r', '--do_rotate', required=False, type=bool, default=False, help='')
  parser.add_argument(
      '-s', '--scale', required=False, type=float, default=0.5, help='')
  parser.add_argument(
      '-rv', '--rotation_value', required=False, type=int, choices=[90,180,270], default=180, help='clockwise rotation')
  args = parser.parse_args()


  video_filename = args.video_filename
  do_rotate = args.do_rotate
  output_video_filename = args.output_video_filename
  scale = args.scale
  rotation_value = args.rotation_value

  rotation_value =  int(rotation_value / 90 - 1) # [ cv2.ROTATE_90_CLOCKWISE, cv2.ROTATE_180, cv2.ROTATE_90_COUNTERCLOCKWISE ].index( rotation_value / 90 )

  doit(video_filename, do_rotate, output_video_filename, scale, rotation_value)




  """
  cv2.ROTATE_90_CLOCKWISE
  cv2.ROTATE_90_COUNTERCLOCKWISE
  cv2.ROTATE_180

  #    if frame_number == 300:
  #        frame_number = int(0.999 * total_frames)
  #        cap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)

  """

