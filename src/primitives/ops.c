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

#ifdef ENABLE_NEON_OPTS
#include <arm_neon.h>
#endif

#include "argon/primitives/ops.h"

inline uint8_t ar_min_u8(uint8_t a, uint8_t b)
{
   if (a > b) {
      return b;
   }
   return a;
}

inline uint8_t ar_max_u8(uint8_t a, uint8_t b)
{
   if (a > b) {
      return a;
   }
   return b;
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vadd_u8_neon(uint8_t* res,
                     const uint8_t* a,
                     const uint8_t* b,
                     uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t b_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      b_loaded = vld1q_u8(&(b[i]));
      res_loaded = vaddq_u8(a_loaded, b_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif

void ar_vadd_u8_generic(uint8_t* res,
                        const uint8_t* a,
                        const uint8_t* b,
                        uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = a[i] + b[i];
   }
}


void ar_vadd_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vadd_u8_neon(res,a,b,n);
#else
   ar_vadd_u8_generic(res,a,b,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vsub_u8_neon(uint8_t* res,
                     const uint8_t* a,
                     const uint8_t* b,
                     uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t b_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      b_loaded = vld1q_u8(&(b[i]));
      res_loaded = vsubq_u8(a_loaded, b_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif

void ar_vsub_u8_generic(uint8_t* res,
                        const uint8_t* a,
                        const uint8_t* b,
                        uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = a[i] - b[i];
   }
}


void ar_vsub_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vsub_u8_neon(res,a,b,n);
#else
   ar_vsub_u8_generic(res,a,b,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vmul_u8_neon(uint8_t* res,
                     const uint8_t* a,
                     const uint8_t* b,
                     uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t b_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      b_loaded = vld1q_u8(&(b[i]));
      res_loaded = vmulq_u8(a_loaded, b_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif

void ar_vmul_u8_generic(uint8_t* res,
                        const uint8_t* a,
                        const uint8_t* b,
                        uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = a[i] * b[i];
   }
}


void ar_vmul_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vmul_u8_neon(res,a,b,n);
#else
   ar_vmul_u8_generic(res,a,b,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vmax_u8_neon(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t b_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      b_loaded = vld1q_u8(&(b[i]));
      res_loaded = vmaxq_u8(a_loaded, b_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif

void ar_vmax_u8_generic(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = ar_max_u8(a[i], b[i]);
   }
}

void ar_vmax_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vmax_u8_neon(res,a,b,n);
#else
   ar_vmax_u8_generic(res,a,b,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vmin_u8_neon(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t b_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      b_loaded = vld1q_u8(&(b[i]));
      res_loaded = vminq_u8(a_loaded, b_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif


void ar_vmin_u8_generic(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = ar_min_u8(a[i], b[i]);
   }
}

void ar_vmin_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vmin_u8_neon(res,a,b,n);
#else
   ar_vmin_u8_generic(res,a,b,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_vnot_u8_neon(uint8_t* res, const uint8_t* a, uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t res_loaded;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      res_loaded = vmvnq_u8(a_loaded);
      vst1q_u8(&(res[i]),res_loaded);
   }
}
#endif

void ar_vnot_u8_generic(uint8_t* res, const uint8_t* a, uint32_t n)
{
   for (uint32_t i = 0; i < n; i++) {
      res[i] = ~a[i];
   }
}

void ar_vnot_u8(uint8_t* res, const uint8_t* a, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   ar_vnot_u8_neon(res,a,n);
#else
   ar_vnot_u8_generic(res,a,n);
#endif
}


//----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
uint8_t ar_vmaxall_u8_neon(const uint8_t* a, uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t overall_max = vdupq_n_u8(0);
   uint8_t om_array[16];
   uint8_t themax = 0;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      overall_max = vmaxq_u8(a_loaded, overall_max);
   }

   vst1q_u8(om_array, overall_max);
   
   for (uint32_t i = 0; i < 16; i++) {
      themax = ar_max_u8(themax, om_array[i]);
   }

   return themax;
}
#endif

uint8_t ar_vmaxall_u8_generic(const uint8_t* a, uint32_t n)
{
   uint8_t maxall = 0;

   for (uint32_t i = 0; i < n; i++) {
      maxall = ar_max_u8(maxall, a[i]);
   }
   return maxall;
}

uint8_t ar_vmaxall_u8(const uint8_t* a, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   return ar_vmaxall_u8_neon(a,n);
#else
   return ar_vmaxall_u8_generic(a,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
uint8_t ar_vminall_u8_neon(const uint8_t* a, uint32_t n)
{
   uint8x16_t a_loaded;
   uint8x16_t overall_min = vdupq_n_u8(255);
   uint8_t om_array[16];
   uint8_t themin = 255;

   for (uint32_t i = 0; i < n; i += 16) {
      a_loaded = vld1q_u8(&(a[i]));
      overall_min = vminq_u8(a_loaded, overall_min);
   }

   vst1q_u8(om_array, overall_min);
   
   for (uint32_t i = 0; i < 16; i++) {
      themin = ar_min_u8(themin, om_array[i]);
   }

   return themin;
}
#endif

uint8_t ar_vminall_u8_generic(const uint8_t* a, uint32_t n)
{
   uint8_t minall = 255;

   for (uint32_t i = 0; i < n; i++) {
      minall = ar_min_u8(minall, a[i]);
   }
   return minall;
}

uint8_t ar_vminall_u8(const uint8_t* a, uint32_t n)
{
#ifdef ENABLE_NEON_OPTS
   return ar_vminall_u8_neon(a,n);
#else
   return ar_vminall_u8_generic(a,n);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_stride2_vminall_u8_neon(const uint8_t* a,
                                uint32_t n,
                                uint8_t* line_results)
{
   uint8x16x2_t a_loaded;
   uint8x16_t line0_min = vdupq_n_u8(255);
   uint8x16_t line1_min = vdupq_n_u8(255);
   line_results[0] = 255;
   line_results[1] = 255;

   uint8_t line0_array[16];
   uint8_t line1_array[16];

   for (uint32_t i = 0; i < n; i += 32) {
      a_loaded = vld2q_u8(&(a[i]));
      line0_min = vminq_u8(a_loaded.val[0], line0_min);
      line1_min = vminq_u8(a_loaded.val[1], line1_min);
   }

   vst1q_u8(line0_array, line0_min);
   vst1q_u8(line1_array, line1_min);
   
   for (uint32_t i = 0; i < 16; i++) {
      line_results[0] = ar_min_u8(line_results[0], line0_array[i]);
      line_results[1] = ar_min_u8(line_results[1], line1_array[i]);
   }
}
#endif

void ar_stride2_vminall_u8_generic(const uint8_t* a,
                                   uint32_t n,
                                   uint8_t* line_results)
{
   line_results[0] = 255;
   line_results[1] = 255;

   for (uint32_t i = 0; i < n; i += 2) {
      line_results[0] = ar_min_u8(line_results[0], a[i]);
      line_results[1] = ar_min_u8(line_results[1], a[i+1]);
   }
}

void ar_stride2_vminall_u8(const uint8_t* a,
                           uint32_t n,
                           uint8_t* line_results)
{
#ifdef ENABLE_NEON_OPTS
   return ar_stride2_vminall_u8_neon(a,n,line_results);
#else
   return ar_stride2_vminall_u8_generic(a,n,line_results);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_stride2_vmaxall_u8_neon(const uint8_t* a,
                                uint32_t n,
                                uint8_t* line_results)
{
   uint8x16x2_t a_loaded;
   uint8x16_t line0_max = vdupq_n_u8(0);
   uint8x16_t line1_max = vdupq_n_u8(0);
   line_results[0] = 0;
   line_results[1] = 0;

   uint8_t line0_array[16];
   uint8_t line1_array[16];

   for (uint32_t i = 0; i < n; i += 32) {
      a_loaded = vld2q_u8(&(a[i]));
      line0_max = vmaxq_u8(a_loaded.val[0], line0_max);
      line1_max = vmaxq_u8(a_loaded.val[1], line1_max);
   }

   vst1q_u8(line0_array, line0_max);
   vst1q_u8(line1_array, line1_max);
   
   for (uint32_t i = 0; i < 16; i++) {
      line_results[0] = ar_max_u8(line_results[0], line0_array[i]);
      line_results[1] = ar_max_u8(line_results[1], line1_array[i]);
   }
}
#endif

void ar_stride2_vmaxall_u8_generic(const uint8_t* a,
                                   uint32_t n,
                                   uint8_t* line_results)
{
   line_results[0] = 0;
   line_results[1] = 0;

   for (uint32_t i = 0; i < n; i += 2) {
      line_results[0] = ar_max_u8(line_results[0], a[i]);
      line_results[1] = ar_max_u8(line_results[1], a[i+1]);
   }
}

void ar_stride2_vmaxall_u8(const uint8_t* a,
                           uint32_t n,
                           uint8_t* line_results)
{
#ifdef ENABLE_NEON_OPTS
   return ar_stride2_vmaxall_u8_neon(a,n,line_results);
#else
   return ar_stride2_vmaxall_u8_generic(a,n,line_results);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_stride3_vmaxall_u8_neon(const uint8_t* a,
                                uint32_t n,
                                uint8_t* line_results)
{
   uint8x16x3_t a_loaded;
   uint8x16_t line0_max = vdupq_n_u8(0);
   uint8x16_t line1_max = vdupq_n_u8(0);
   uint8x16_t line2_max = vdupq_n_u8(0);

   line_results[0] = 0;
   line_results[1] = 0;
   line_results[2] = 0;

   uint8_t line0_array[16];
   uint8_t line1_array[16];
   uint8_t line2_array[16];

   for (uint32_t i = 0; i < n; i += 48) {
      a_loaded = vld3q_u8(&(a[i]));
      line0_max = vmaxq_u8(a_loaded.val[0], line0_max);
      line1_max = vmaxq_u8(a_loaded.val[1], line1_max);
      line2_max = vmaxq_u8(a_loaded.val[2], line2_max);
   }

   vst1q_u8(line0_array, line0_max);
   vst1q_u8(line1_array, line1_max);
   vst1q_u8(line2_array, line2_max);

   for (uint32_t i = 0; i < 16; i++) {
      line_results[0] = ar_max_u8(line_results[0], line0_array[i]);
      line_results[1] = ar_max_u8(line_results[1], line1_array[i]);
      line_results[2] = ar_max_u8(line_results[2], line2_array[i]);
   }
}
#endif

void ar_stride3_vmaxall_u8_generic(const uint8_t* a,
                                   uint32_t n,
                                   uint8_t* line_results)
{
   line_results[0] = 0;
   line_results[1] = 0;
   line_results[2] = 0;

   for (uint32_t i = 0; i < n; i += 3) {
      line_results[0] = ar_max_u8(line_results[0], a[i]);
      line_results[1] = ar_max_u8(line_results[1], a[i+1]);
      line_results[2] = ar_max_u8(line_results[2], a[i+2]);
   }
}

void ar_stride3_vmaxall_u8(const uint8_t* a,
                           uint32_t n,
                           uint8_t* line_results)
{
#ifdef ENABLE_NEON_OPTS
   return ar_stride3_vmaxall_u8_neon(a,n,line_results);
#else
   return ar_stride3_vmaxall_u8_generic(a,n,line_results);
#endif
}

//-----------------------------------------------------------------------------
#ifdef ENABLE_NEON_OPTS
void ar_stride3_vminall_u8_neon(const uint8_t* a,
                                uint32_t n,
                                uint8_t* line_results)
{
   uint8x16x3_t a_loaded;
   uint8x16_t line0_min = vdupq_n_u8(255);
   uint8x16_t line1_min = vdupq_n_u8(255);
   uint8x16_t line2_min = vdupq_n_u8(255);

   line_results[0] = 255;
   line_results[1] = 255;
   line_results[2] = 255;

   uint8_t line0_array[16];
   uint8_t line1_array[16];
   uint8_t line2_array[16];

   for (uint32_t i = 0; i < n; i += 48) {
      a_loaded = vld3q_u8(&(a[i]));
      line0_min = vminq_u8(a_loaded.val[0], line0_min);
      line1_min = vminq_u8(a_loaded.val[1], line1_min);
      line2_min = vminq_u8(a_loaded.val[2], line2_min);
   }

   vst1q_u8(line0_array, line0_min);
   vst1q_u8(line1_array, line1_min);
   vst1q_u8(line2_array, line2_min);
   
   for (uint32_t i = 0; i < 16; i++) {
      line_results[0] = ar_min_u8(line_results[0], line0_array[i]);
      line_results[1] = ar_min_u8(line_results[1], line1_array[i]);
      line_results[2] = ar_min_u8(line_results[2], line2_array[i]);
   }
}
#endif

void ar_stride3_vminall_u8_generic(const uint8_t* a,
                                   uint32_t n,
                                   uint8_t* line_results)
{
   line_results[0] = 255;
   line_results[1] = 255;
   line_results[2] = 255;

   for (uint32_t i = 0; i < n; i += 3) {
      line_results[0] = ar_min_u8(line_results[0], a[i]);
      line_results[1] = ar_min_u8(line_results[1], a[i+1]);
      line_results[2] = ar_min_u8(line_results[2], a[i+2]);
   }
}

void ar_stride3_vminall_u8(const uint8_t* a,
                           uint32_t n,
                           uint8_t* line_results)
{
#ifdef ENABLE_NEON_OPTS
   return ar_stride3_vminall_u8_neon(a,n,line_results);
#else
   return ar_stride3_vminall_u8_generic(a,n,line_results);
#endif
}

