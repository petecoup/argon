from PIL import Image
import sys

def compare_image(file1, file2):
    im1 = Image.open(file1)
    im2 = Image.open(file2)

    if im1.size != im2.size:
        print("[%s,%s]: Size Mismatch: %s != %s" % (file1, file2, im1.size, im2.size))
        return False

    for x in range(im1.size[0]):
        for y in range(im1.size[1]):
            if im1.getpixel((x,y)) != im2.getpixel((x,y)):
                print("[%s,%s]: Pixel mismatch at (%s,%s): %s != %s" % (file1, file2, x, y, im1.getpixel((x,y)), im2.getpixel((x,y))))
                return False
    return True

if __name__=='__main__':
    file1 = sys.argv[1]
    file2 = sys.argv[2]

    if compare_image(file1, file2):
        print("Images are the same.")
    else:
        print("Images are different.")

