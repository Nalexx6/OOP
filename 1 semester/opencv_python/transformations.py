import cv2 as cv
import numpy as np

img = cv.imread('Photos/park.jpg')
cv.imshow('Park', img)

# Translation
def translate(img, x, y):
    trans_mat = np.float32([[1,0,x],[0,1,y]])
    dimensions = (img.shape[1], img.shape[0])
    return cv.warpAffine(img, trans_mat, dimensions)

# -x --> left
# -y --> up
# x --> right
# y --> down

translated = translate(img, -100, 100)
cv.imshow('Translated', translated)

# Rotation
def rotate(img, angle, rot_point = None):
    (height, width) = img.shape[:2]

    if rot_point is None:
        rot_point = (width//2, height//2)
        
        rot_mat = cv.getRotationMatrix2D(rot_point, angle, 1.0)
        dimensions = (width, height)

        return cv.warpAffine(img, rot_mat, dimensions)

rotated = rotate(img, 45)
cv.imshow('Rotated', rotated)

rotated_rotated = rotate(img, 90)
cv.imshow('Rotated', rotated_rotated)

# Flipping
flip = cv.flip(img, -1)
cv.imshow('Flip', flip)

cv.waitKey(0)