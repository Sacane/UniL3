#! /usr/bin/python3

from ctypes import *
import timeit
from PIL import Image


img = Image.open("Lenna.png")


# image_libc = cdll.LoadLibrary("/home/nborie/Enseignements/Marne_2018_2019/L3_C_avance/tp/tp_python_C/basic_image_process.so")
image_libc = cdll.LoadLibrary("./image_process.so")
print(image_libc.invert_color)

Pix_c = c_ubyte * 4
Img_c_line = Pix_c * 512
Img_c = Img_c_line * 512


def convert_bitmap_to_c(img):
    img_c = Img_c()
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            print(img_c[i][j])
    return img_c


def rebuild_image(img_c, img):
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            bitmap[i, j] = (img_c[i][j][0], img_c[i][j][1], img_c[i][j][2], img_c[i][j][3])


img_c = convert_bitmap_to_c(img)


img.show()

rebuild_image(img_c, img)

img.show()

img.close()