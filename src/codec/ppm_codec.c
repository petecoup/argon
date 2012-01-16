#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "argon/rgb_bitmap.h"
#include "argon/ppm_codec.h"

bool
is_eof(FILE* f)
{
   return (feof(f) != 0);
}

char
ar_peek(FILE* f)
{
   char c = fgetc(f);
   int retval = fseek(f,-1,SEEK_CUR);

   if (retval == 0) {
      printf("Peeked: %d\n", c);
      return c;
   } else {
      printf("Peek error.\n");
      return -1;
   }
}

void
scan_to_eol(FILE* f)
{
   char c;

   while (!is_eof(f) && ((c = ar_peek(f)) != -1 && (c != '\n'))) {
      c = fgetc(f);
   }
}

void
scan_comment(FILE* f)
{
   //Read to the end of the line, and ignore the contents.
   scan_to_eol(f);
}

void
scan_past_whitespace(FILE* f)
{
   char c;

   while (!is_eof(f) && ((c = ar_peek(f)) != -1 && (isspace(c) || c == '#'))) {
      if (c == '#') {
         scan_comment(f);
      } else {
         c = fgetc(f);
         printf("Scanned whitespace: %d\n", c);
      }
   }
}

arRGBBitmap*
ar_read_ppm_file(const char* filename)
{
   FILE* f = fopen(filename, "rb");
   arRGBBitmap* bitmap;

   char buf[16];
   uint32_t width, height;

   //Read the first 2 bytes in the file.  We only support P6 files.

   size_t read_res = fread(buf, 1, 2, f);
   int scan_res;

   if (read_res != 2 || buf[0] != 'P' || buf[1] != '6') {
      printf("Magic error.\n");
      return 0;
   }
   scan_past_whitespace(f);

   //Next, should be the width
   scan_res = fscanf(f, "%s", buf);
   if (scan_res == 0 || scan_res == EOF) {
      printf("Width: Scan/Read error.\n");
      return 0;
   }

   printf("Scanned width: %u\n", atoi(buf));
   width = atoi(buf);
   if (width == 0) {
      printf("Width: 0 is an invalid width.\n");
      return 0;
   }
   scan_past_whitespace(f);
   
   //Next, should be the height
   scan_res = fscanf(f, "%s", buf);
   if (scan_res == 0 || scan_res == EOF) {
      printf("Height: Scan/Read error.\n");
      return 0;
   }

   printf("Scanned height: %u\n", atoi(buf));
   height = atoi(buf);
   if (height == 0) {
      printf("Height: 0 is an invalid height.\n");
      return 0;
   }

   scan_past_whitespace(f);

   //Next, should be the maxvalue.
   scan_res = fscanf(f, "%s", buf);
   if (scan_res == 0 || scan_res == EOF) {
      printf("MaxColor: Scan/Read error.\n");
      return 0;
   }

   printf("Max color value: %u\n", atoi(buf));

   if (atoi(buf) == 0 || atoi(buf) > 255) {
      printf("Max color value %s out of range (1,255)\n", buf);
      return 0;
   }

   scan_past_whitespace(f);
   //Next, should be the rest of the data.
   bitmap = ar_create_bitmap(width, height);

   //Now, scan the values directly into the bitmap.
   read_res = fread(bitmap->data_, 1, 3*width*height, f);

   if (read_res != 3*width*height) {
      printf("Read error: read %u bytes, expected %u bytes\n", (unsigned)read_res, 3*width*height);
   }
   return bitmap;
}

void
ar_write_ppm_file(const arRGBBitmap* bitmap, const char* filename)
{
   FILE* out = fopen(filename, "wb");
   size_t written;
   char buf[32];

   sprintf(buf, "P6\n%u %u\n255\n", bitmap->width_, bitmap->height_);
   
   written = fwrite(buf, 1, strlen(buf), out);

   if (written != strlen(buf)) {
      printf("Write error: wrote %u bytes, expected %u.\n", (unsigned)written, (unsigned)strlen(buf));
      return;
   }
   
   //Now, write the massive block of data.

   written = fwrite(bitmap->data_, 1, 3*bitmap->width_*bitmap->height_, out);

   if (written != 3*bitmap->width_*bitmap->height_) {
      printf("Write error: wrote %u bytes, expected %u.\n", (unsigned)written, 3*bitmap->width_*bitmap->height_);
      return;
   }
}

