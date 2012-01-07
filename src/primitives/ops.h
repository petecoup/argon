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


#ifndef ARGON_PRIMITIVES_OPS_H_
#define ARGON_PRIMITIVES_OPS_H_

#include <stdint.h>

void ar_vadd_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n);
void ar_vsub_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n);
void ar_vmul_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n);
void ar_vmax_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n);
void ar_vmin_u8(uint8_t* res, const uint8_t* a, const uint8_t* b, uint32_t n);
void ar_vabs_u8(uint8_t* res, const uint8_t* a, uint32_t n);
void ar_vnot_u8(uint8_t* res, const uint8_t* a, uint32_t n);

uint8_t ar_vmaxall_u8(const uint8_t* a, uint32_t n);
uint8_t ar_vminall_u8(const uint8_t* a, uint32_t n);
uint8_t ar_strided_vmaxall_u8(const uint8_t* a, uint32_t n);
uint8_t ar_strided_vminall_u8(const uint8_t* a, uint32_t n);

#endif

