from PIL import Image

headerFile = open("./src/images.h", "w+")

headerFile.write("#include <VGAXUA.h>\n")
headerFile.write("\n")
headerFile.write(
    "const byte fullScreenImage[VGAX_HEIGHT*VGAX_BWIDTH] PROGMEM={\n")

image = Image.open("FullScreen.png")

for y in range(image.height):
    for x in range(int(image.width/4)):
        pixel0 = image.getpixel(((x*4)+0, y))
        pixel1 = image.getpixel(((x*4)+1, y))
        pixel2 = image.getpixel(((x*4)+2, y))
        pixel3 = image.getpixel(((x*4)+3, y))
        pixel = (pixel0 << 6) | (pixel1 << 4) | (pixel2 << 2) | (pixel3 << 0)
        headerFile.write("{:3d}".format(pixel)+",")
    headerFile.write("\n")

headerFile.write("};\n")

headerFile.close()
