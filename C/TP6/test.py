
# ! /usr/bin/python3

from ctypes import *
from PIL import Image

# Fonction inversant les couleurs des pixels dans une image 512x512
def invert_color_on_image(img):
    bitmap = img.load()

    for i in range(512):
        for j in range(512):
            (r, g, b, a) = bitmap[i, j]
            bitmap[i, j] = (255 - r, 255 - g, 255 - b, a)


img = Image.open("Lenna.png")


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
            for k in range(2):
                img_c[i][j][k] = bitmap[i, j][k]
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
