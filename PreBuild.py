from PIL import Image
import math


def Color(test):
    if not isinstance(test, tuple):
        return 8
    elif test[0] == 000 and test[1] == 000 and test[2] == 000 and test[3] == 000:
        return 8
    elif test[0] == 000 and test[1] == 000 and test[2] == 000 and test[3] == 255:
        return 0
    elif test[0] == 000 and test[1] == 255 and test[2] == 000 and test[3] == 255:
        return 1
    elif test[0] == 255 and test[1] == 000 and test[2] == 000 and test[3] == 255:
        return 2
    elif test[0] == 255 and test[1] == 255 and test[2] == 000 and test[3] == 255:
        return 3
    return 8


def WriteImage(file, name):
    image = Image.open(name+".png")

    file.write("#define IMG_{}_WIDTH {}\n".format(
        str(name).upper(),
        str(image.width)
    ))

    file.write("#define IMG_{}_BWIDTH {}\n".format(
        str(name).upper(),
        str(int(math.ceil(image.width/4)))
    ))

    file.write("#define IMG_{}_HEIGHT {}\n".format(
        str(name).upper(),
        str(image.height)
    ))

    file.write("\n")

    test = "const unsigned char img_{}_data[IMG_{}_HEIGHT][IMG_{}_BWIDTH] PROGMEM=".format(
        str(name).lower(),
        str(name).upper(),
        str(name).upper()
    )

    file.write(test+"{\n")

    for y in range(image.height):
        file.write("    {")
        for x in range(int(math.ceil(image.width/4))):
            pixel0 = 0 if (
                x*4)+0 >= image.width else Color(image.getpixel(((x*4)+0, y)))
            pixel1 = 0 if (
                x*4)+1 >= image.width else Color(image.getpixel(((x*4)+1, y)))
            pixel2 = 0 if (
                x*4)+2 >= image.width else Color(image.getpixel(((x*4)+2, y)))
            pixel3 = 0 if (
                x*4)+3 >= image.width else Color(image.getpixel(((x*4)+3, y)))
            pixel = (((pixel0 & 0b11) << 6) |
                     ((pixel1 & 0b11) << 4) |
                     ((pixel2 & 0b11) << 2) |
                     ((pixel3 & 0b11) << 0))
            file.write("0b{:08b}".format(pixel))
            if x != int(math.ceil(image.width/4))-1:
                file.write(",")
        file.write("},\n")
    file.write("};\n")

    file.write("\n")

    test = "const unsigned char img_{}_mask_data[IMG_{}_HEIGHT][IMG_{}_BWIDTH] PROGMEM=".format(
        str(name).lower(),
        str(name).upper(),
        str(name).upper()
    )

    file.write(test+"{\n")

    for y in range(image.height):
        file.write("    {")
        for x in range(int(math.ceil(image.width/4))):
            pixel0 = 0 if (
                x*4)+0 >= image.width else (0b11 if Color(image.getpixel(((x*4)+0, y))) == 8 else 0b00)
            pixel1 = 0 if (
                x*4)+1 >= image.width else (0b11 if Color(image.getpixel(((x*4)+1, y))) == 8 else 0b00)
            pixel2 = 0 if (
                x*4)+2 >= image.width else (0b11 if Color(image.getpixel(((x*4)+2, y))) == 8 else 0b00)
            pixel3 = 0 if (
                x*4)+3 >= image.width else (0b11 if Color(image.getpixel(((x*4)+3, y))) == 8 else 0b00)
            pixel = (((pixel0 & 0b11) << 6) |
                     ((pixel1 & 0b11) << 4) |
                     ((pixel2 & 0b11) << 2) |
                     ((pixel3 & 0b11) << 0))
            file.write("0b{:08b}".format(pixel))
            if x != int(math.ceil(image.width/4))-1:
                file.write(",")
        file.write("},\n")
    file.write("};\n")


headerFile = open("./src/sprites.h", "w+")

headerFile.write("#include <Arduino.h>\n")
headerFile.write("\n")
WriteImage(headerFile, "Bird")
headerFile.write("\n")

headerFile.close()
