
# import template_matching as tm
# import cv2 as cv
# from time import time
# from cascade_utils import generate_negative_description_file
#
# generate_negative_description_file()
#
# points = tm.findClickPositions('albion_cabbage.jpg', 'albion_farm.jpg', debug_mode='points')
# print(points)
# points = tm.findClickPositions('albion_turnip.jpg', 'albion_farm.jpg',
#                            threshold=0.70, debug_mode='rectangles')
# print(points)
# print('Done.')

import cv2 as cv
import numpy as np
from time import time
from windowcapture import WindowCapture
from vision import Vision
from PIL import ImageGrab



# initialize the WindowCapture class
wincap = WindowCapture('Task Manager')
# initialize the Vision class
# vision_limestone = Vision('albion_limestone.jpg')


loop_time = time()
while(True):

    # get an updated image of the game

    screenshot = wincap.get_screenshot()
    # screenshot = ImageGrab.grab()
    # screenshot = np.array(screenshot)
    # screenshot = cv.cvtColor(screenshot, cv.COLOR_RGB2BGR)

    cv.imshow('Computer Vision', screenshot)

    # display the processed image
    # points = vision_limestone.find(screenshot, 0.5, 'rectangles')
    #points = vision_gunsnbottle.find(screenshot, 0.7, 'points')

    # debug the loop rate
    print('FPS {}'.format(1 / (time() - loop_time)))
    loop_time = time()

    # press 'q' with the output window focused to exit.
    # waits 1 ms every loop to process key presses
    if cv.waitKey(1) == 27:
        cv.destroyAllWindows()
        break

print('Done.')

