from PIL import Image
from PIL import ImageOps
import sys

def invert_image(src, target):
    im = Image.open(src)
    im2 = ImageOps.invert(im)
    im2.save(target, "PPM")

if __name__=='__main__':
    src_file = sys.argv[1]
    target_file = sys.argv[2]
    invert_image(src_file, target_file)

