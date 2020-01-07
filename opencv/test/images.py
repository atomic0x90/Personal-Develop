import numpy as np
import cv2

''' 
var = cv2.imread('Image path/~.extension', data)

data
cv2.IMREAD_COLOR : Loads a color image. Any transparency of image will be neglected. It is the default flag.
cv2.IMREAD_GRAYSCALE : Loads image in grayscale mode
cv2.IMREAD_UNCHANGED : Loads image as such including alpha channel

simple
 0 : gray
 1 : color
-1 : color + alpha channel

* alpha channel : Secondary data separated from the data of color representation for each pixel
'''
img = cv2.imread('tree.jpg', cv2.IMREAD_COLOR)

cv2.namedWindow('test',cv2.WINDOW_NORMAL)
cv2.imshow('test', img)

img1 = cv2.imread('tree.jpg', cv2.IMREAD_GRAYSCALE)

cv2.namedWindow('test1',cv2.WINDOW_NORMAL)
cv2.imshow('test1', img1)

img2 = cv2.imread('tree.jpg', cv2.IMREAD_UNCHANGED)

cv2.namedWindow('test2',cv2.WINDOW_NORMAL)
cv2.imshow('test2', img2)

cv2.waitKey(0)
cv2.destroyAllWindows()
