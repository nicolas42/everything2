# draw a wave with a changing frequency.  dynamically loads config.py so the output can be changed while the program is running
import cv2 
import sys
import math
import numpy as np
import importlib
import config
import json
import colorsys

def hsv2rgb(h,s,v):
    """colorsys.hsv_to_rgb takes and returns normalized values, i.e. 0..1
    This function takes 0..1 values and returns the 0..255 values typically
    found in the fields of a pixel.
    source: https://stackoverflow.com/questions/24852345/hsv-to-rgb-color-conversion
    """
    return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h,s,v))


def draw_wave_at_frequency(image, frequency):

    sine_wave = []
    for i in range(config.samples + 1):
        x = config.periods * 2 * math.pi * i / config.samples
        sine_wave.append( (x, math.sin(frequency * x)) )
    # print(sine_wave)

    for xy in sine_wave:

        if config.rainbow_color:
            max_x = sine_wave[-1][0]
            config.color = hsv2rgb(xy[0] / max_x, 1, 1)
        
        center_coordinates = ( int( config.offset[0] + xy[0] * config.scaler[0] ), int( config.offset[1] - xy[1] * config.scaler[1] ) )
        # print(center_coordinates)
        cv2.circle(image, center_coordinates, config.radius, config.color, config.thickness, lineType=cv2.LINE_AA)

    return image


i = 0
paused = False
while True:

    importlib.reload(config)

    image = np.zeros((config.height, config.width, 3), np.uint8)
    image[:, :] = config.background_color

    key = cv2.waitKey(config.key_wait) 
    if key in config.escape_keys:
        break
    elif key == config.pause_key: # space
        paused = not paused
    elif key == config.reset_key:
        i = 0

    if not paused:
        i += 1
        frequency = 1 + i * config.frequency_increment
        image = draw_wave_at_frequency(image, frequency)
        cv2.imshow('Controls: r to reset, spacebar to pause, q or escape to exit', image) 



cv2.destroyAllWindows()


