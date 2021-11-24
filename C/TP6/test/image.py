#! /usr/bin/python3

from ctypes import *
import timeit
from PIL import Image

# Fonction inversant les couleurs des pixels dans une image 512x512
def invert_color_on_image(img):
    bitmap = img.load()
    
    for i in range(512):
        for j in range(512):
            (r,g,b,a) = bitmap[i,j]
            bitmap[i,j] = (255 - r, 255 - g, 255 - b, a)


img = Image.open("panda.png")

invert_color_on_image(img)

setup = "from __main__ import invert_color_on_image, img"
print("TEMPS POUR INVERSER LES COULEURS AVEC PYTHON :")
print(timeit.timeit("invert_color_on_image(img)", setup=setup, number=100)/100, "secondes")

# image_libc = cdll.LoadLibrary("/home/nborie/Enseignements/Marne_2018_2019/L3_C_avance/tp/tp_python_C/basic_image_process.so")
image_libc = cdll.LoadLibrary("./basic_image_process.so")
print(image_libc.invert_color)


Pix_c = c_ubyte * 4
Img_c_line = Pix_c * 512
Img_c = Img_c_line * 512

def convert_bitmap_to_c(img):
    img_c = Img_c()
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            for k in range(4):
                img_c[i][j][k] = bitmap[i, j][k]
    return img_c

def rebuild_image(img_c, img):
    bitmap = img.load()
    for i in range(512):
        for j in range(512):
            bitmap[i, j] = (img_c[i][j][0], img_c[i][j][1], img_c[i][j][2], img_c[i][j][3])

img_c = convert_bitmap_to_c(img)

setup = "from __main__ import image_libc, img_c"
print("TEMPS POUR INVERSER LES COULEURS AVEC C :")
print(timeit.timeit("image_libc.invert_color(img_c)", setup=setup, number=101)/101, "secondes")

img.show()

rebuild_image(img_c, img)

img.show()

img.close()


