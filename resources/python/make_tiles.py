
from PIL import Image
import os
# print(dir(Image))


def make_tiles(image, size, level=0,  limit=30):

    width = image.size[0]
    height = image.size[1]
    if width < 1024 or level >= limit:
        return

    for y in range(0, int(height / size)+1):
        for x in range(0, int(width / size)+1):
            name = "level_%d__%d__%d.tif" % (level, x, y)
            x_start = x * size
            y_start = y * size

            x_end = x_start + size
            y_end = y_start + size

            print(x_end, width)
            if x_end > width:
                print("reached the end of image")
            cropped = image.crop((x_start, y_start, x_end, y_end))
            # print(cropped)
            cropped.save(os.path.join("tiles", name))

    if width > size:
        scaled = image.resize((int(image.size[0]/2), int(image.size[1]/2)))
        make_tiles(scaled, size, level+1)


src_file = 'D:/Natural Earth Data/NE1_HR_LC_SR_W_DR/NE1_HR_LC_SR_W_DR.tif'

with Image.open(scr_file) as full_image:

    make_tiles(full_image, 512)
