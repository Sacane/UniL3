from os import path
from convert import Convert

def create_conversion_wrapper(path_img):
    converter = Convert(path_img)
    return converter

def show_conversion(path_img):
    valid = True
    convert = Convert(path_img)

    print("which function do you want to use ? ")
    print("1 : invert color\n2 : average grey level\n3 : grey clarity level")
    print("4 : grey luminance level\n5 : black and white tresholing\n6 : conversion to red\n7: conversion to green")
    print("8 : average of colors")
    print("9 : Red and blue degraded conversion")
    choice = input("Your choice : ")
    if choice == "1":
        convert.invert_color()
    elif choice == "2":
        convert.average_grey_level()
    elif choice == "3":
        convert.grey_clarity_level()
    elif choice == "4":
        convert.grey_luminance_level()
    elif choice == "5":
        convert.black_white_thresholding()
    elif choice == "6":
        convert.to_red()
    elif choice == "7":
        convert.to_green()
    elif choice == "8":
        path_img_to_convert = input("Insert the path to the image to average : ")
        img_to_compare = create_conversion_wrapper("")
        convert.average()
    elif choice == "9":
        convert.red_blue_degraded_img()
    else:
        valid = False
    
    if valid:
        convert.show()

show_conversion("panda.png")


