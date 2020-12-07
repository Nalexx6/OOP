import cv2 as cv

# img = cv.imread('Photos/cat_large.jpg')
#
# cv.imshow('Cat', img)

# Reading videos
capture = cv.VideoCapture('Videos/dog.mp4')

while(True):
    isTrue, frame = capture.read()
    cv.imshow('Video', frame)

    if cv.waitKey(20) == 27:
        break

capture.release()
cv.destroyAllWindows()

cv.waitKey(0)