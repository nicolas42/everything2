import cv2
import sys

def show_image(path):

    # Reading an image in default mode
    image = cv2.imread(path)

    # Window name in which image is displayed
    window_name = 'image'

    # Using cv2.imshow() method
    # Displaying the image
    cv2.imshow(window_name, image)

    #waits for user to press any key
    #(this is necessary to avoid Python kernel form crashing)
    cv2.waitKey(0)

    #closing all open windows
    cv2.destroyAllWindows()

if __name__ == "__main__":
    path = sys.argv[1]
    # filename = 'Lenna_(test_image).png'
    show_image(path)