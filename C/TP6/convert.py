from ctypes import *
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math

c_type = cdll.LoadLibrary("./image_process.so")

size_pixel = 512
Pixel_c = c_ubyte * 4
img_line = Pixel_c * size_pixel
Img_C = img_line * size_pixel


class Convert:
    def __init__(self, img):
        self.img = Image.open(img)
        self.bitmap = self.img.load()
        self.imgC = Img_C()

    def convert_bitmap_to_c(self):
        for i in range(512):
            for j in range(512):
                for k in range(4):
                    self.imgC[i][j][k] = self.bitmap[i, j][k]

    def toPython(self):

        for i in range(size_pixel):
            for j in range(size_pixel):
                self.bitmap[i, j] = (self.imgC[i][j][0], self.imgC[i][j][1], self.imgC[i][j][2], self.imgC[i][j][3])

    

    def show(self):
        self.toPython()
        self.img.show()

    def close(self):
        self.img.close()

    def invert_color(self):
        self.convert_bitmap_to_c()
        c_type.invert_color(self.imgC)

    def average_grey_level(self):
        self.convert_bitmap_to_c()
        c_type.average_grey_level(self.imgC)

    def grey_clarity_level(self):
        self.convert_bitmap_to_c()
        c_type.grey_clarity_level(self.imgC)

    def grey_luminance_level(self):
        self.convert_bitmap_to_c()
        c_type.grey_luminance_level(self.imgC)

    def black_white_thresholding(self):
        self.convert_bitmap_to_c()
        c_type.black_white_thresholding(self.imgC)
    
    def to_red(self):
        self.convert_bitmap_to_c()
        c_type.to_red(self.imgC)   

    def to_green(self):
        self.convert_bitmap_to_c()
        c_type.to_green(self.imgC)

    def average(self, other):
        self.convert_bitmap_to_c()
        c_type.average(self.imgC, other.imgC)

    def red_blue_degraded_img(self):
        self.convert_bitmap_to_c()
        c_type.red_blue_degraded_img(self.imgC)
        






