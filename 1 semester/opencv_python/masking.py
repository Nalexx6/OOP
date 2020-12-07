import cv2 as cv
import numpy as np

img = cv.imread('Photos/cats 2.jpg')
cv.imshow('Cats', img)

blank = np.zeros(img.shape[:2], dtype='uint8')
cv.imshow('Blank Image', blank)

rectangle = cv.rectangle(blank.copy(), (30, 30), (370,370), 255, -1)

circle = cv.circle(blank, (img.shape[1]//2, img.shape[0]//2), 100, 255, -1)

weird_shape = cv.bitwise_and(circle, rectangle)

masked = cv.bitwise_and(img, img, mask=weird_shape)
cv.imshow('Weird shaped Masked', masked)

cv.waitKey(0)