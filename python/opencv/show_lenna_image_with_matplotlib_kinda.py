import cv2
import numpy as np
import math
import matplotlib.pyplot as plt
src = cv2.imread('../Lenna_(test_image).png')
img = cv2.cvtColor(src, cv2.COLOR_BGR2RGB)
plt.figure(figsize=(8, 5))
plt.axis("off")
plt.imshow(img)
plt.show()
# plt.pause(1)