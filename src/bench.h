/*
*  isbench
*  bench.h
*
*  Main entry point and user interface of the benchmark, relies on platform-defined 
*  functions. 
*
*  Copyright ©2018 Konrad Kołakowski
*
*  Permission is hereby granted, free of charge, to any person obtaining 
*  a copy of this software and associated documentation files (the "Software"),
*  to deal in the Software without restriction, including without limitation
*  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
*  and/or sell copies of the Software, and to permit persons to whom the Software
*  is furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included 
*  in all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
*  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
*  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*  DEALINGS IN THE SOFTWARE.
*/

#ifndef _BENCH_H
#define _BENCH_H

#include "platform.h"

#define BENCH_RND_ITERATIONS 1000
#define BENCH_WC_ITERATIONS 500
#define BENCH_CRC32_ITERATIONS 1000
#define BENCH_RLE_ITERATIONS 250
#define BENCH_QSORT_ITERATIONS 100

typedef union {
    double double_value;
    uint32_t uint32_value;
    int int_value;
} bench_result_t;

bench_result_t bench_random_numbers(void);
bench_result_t bench_word_count(void);
bench_result_t bench_crc32_hashes(void);
bench_result_t bench_rle_compression(void);
bench_result_t bench_quick_sort(void);

#endif
