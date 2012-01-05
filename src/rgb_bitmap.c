/*
 * Copyright (C) 2012 Peter Couperus
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <stdlib.h>

#include "argon/rgb_bitmap.h"

arRGBBitmap* ar_create_bitmap(uint32_t width, uint32_t height)
{
   arRGBBitmap* retbm = malloc(sizeof(arRGBBitmap));
   
   if (!retbm) {
      return retbm;
   }

   retbm->data_ = malloc(3*width*height*sizeof(uint8_t));
   retbm->width_ = width;
   retbm->height_ = height;

   return retbm;
}

void ar_release_bitmap(arRGBBitmap* bm)
{
   free(bm->data_);
   free(bm);
}

