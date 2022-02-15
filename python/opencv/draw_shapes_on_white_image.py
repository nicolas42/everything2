import numpy as np
import cv2

height, width = 150, 200
img = np.zeros((height, width, 3), np.uint8)
img[:, :] = [255, 255, 255]

# Pixel position to draw at
row, col = 20, 100

# Draw a square with position 20, 100 as the top left corner
for i in range(row, 30):
    for j in range(col, 110):
        img[i, j] = [0, 0, 255]

# Will the following draw a circle at (20, 100)?
# Ans: No. It will draw at row index 100 and column index 20.
cv2.circle(img,(col, row), 5, (0,255,0), -1)
cv2.imshow('', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

