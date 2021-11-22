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
        self.imgC = self.toC()

    def toC(self):
        img_c = Img_C()
        for i in range(size_pixel):
            for j in range(size_pixel):
                for k in range(4):
                    self.imgC[i][j][k] = self.bitmap[i, j][k]
        return img_c

    def toPython(self):
        self.bitmap = self.img.load()
        for i in range(size_pixel):
            for j in range(size_pixel):
                self.bitmap[i, j] = (self.imgC[i][j][0], self.imgC[i][j][1], self.imgC[i][j][2], self.imgC[i][j][3])

    def show(self):
        self.img.show()

    def close(self):
        self.img.close()

    def invert_color(self):
        c_type.invert_color(self.imgC)
        self.toPython()


pic = Convert("Lenna.png")
pic.invert_color()
pic.show()
pic.close()
