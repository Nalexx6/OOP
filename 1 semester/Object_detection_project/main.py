
import template_matching as tm
import cv2 as cv
from time import time
from cascade_utils import generate_negative_description_file

generate_negative_description_file()

# points = tm.findClickPositions('albion_cabbage.jpg', 'albion_farm.jpg', debug_mode='points')
# print(points)
# points = tm.findClickPositions('albion_turnip.jpg', 'albion_farm.jpg',
#                            threshold=0.70, debug_mode='rectangles')
# print(points)
# print('Done.')

# wincap = WindowCapture("Chess")

# loop_time = time()
# while(True):

#     # get an updated image of the game
#     screenshot = wincap.get_screenshot()

#     cv.imshow("Computer Vision", screenshot)

#     # debug the loop rate
#     print('FPS {}'.format(1 / (time() - loop_time)))
#     loop_time = time()

#     # press ESC to exit.
#     if cv.waitKey(1) == 27:
#         cv.destroyAllWindows()
#         break

# print("Done")

