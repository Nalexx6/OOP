import cv2 as cv
import numpy as np

haystack_img = cv.imread("albion_farm.jpg", cv.IMREAD_UNCHANGED)
needle_img = cv.imread("albion_cabbage.jpg", cv.IMREAD_UNCHANGED)

needle_w = needle_img.shape[1]
needle_h = needle_img.shape[0]

result = cv.matchTemplate(haystack_img, needle_img, cv.TM_SQDIFF_NORMED)

threshold = 0.17
locations = np.where(result <= threshold)
locations = list(zip(*locations[::-1]))

# creating the list of rectangles(x, y, w, h)
rectangles = []
for loc in locations:
    rect = [int(loc[0]), int(loc[1]), needle_w, needle_h]
    rectangles.append(rect)
    rectangles.append(rect) # need to do it twice because cv.groupRectangles make rectangle to disappear if
                            # there are no other overlapping rectangles



rectangles, weights = cv.groupRectangles(rectangles, 1, 0.5)
print(rectangles)


if len(rectangles):
    print("Found needle")

    line_color = (0, 255, 0)
    line_type = cv.LINE_4

    # need to loop over the locations and draw their rectangle
    for (x, y, w, h) in rectangles:

        top_left = (x, y)
        bottom_right = (x + w, y + h)

        cv.rectangle(haystack_img, top_left, bottom_right, line_color, line_type)


    cv.imshow("Matches", haystack_img)
    cv.waitKey()

else:
    print("Needle not found")