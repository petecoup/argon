#include <stdio.h>
#include <stdlib.h>
#include "argon/transform.h"
#include "argon/rgb_bitmap.h"
#include "argon/ppm_codec.h"


int main(int argc, char** argv)
{
   arRGBBitmap* bitmap = ar_read_ppm_file(argv[1]);

   if (bitmap) {
      printf("Bitmap creation succeeded.\n");
   } else {
      printf("Bitmap creation failed.\n");
      exit(-1);
   }

   ar_invert_transform(bitmap, bitmap);
   ar_write_ppm_file(bitmap, argv[2]);

   ar_release_bitmap(bitmap);
   return 0;
}

