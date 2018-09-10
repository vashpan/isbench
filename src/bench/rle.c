/*
*  isbench
*  rle.c
*
*  RLE simple compression benchmark
*
*  Copyright © 2018 Konrad Kołakowski
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

#include "rle.h"

#define BENCH_RLE_TEST_DATA_SIZE 100

static const uint8_t test_data[BENCH_RLE_TEST_DATA_SIZE] = { 
    1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
    0, 1, 1, 1, 0, 0, 1, 1, 1, 0,    
    0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
    1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 0, 1, 1
 };

static void rle_compress(uint8_t* input, size_t input_size, uint8_t* output, size_t* output_size) {
    size_t n, output_marker;
    uint16_t same_bytes_num;
    uint8_t last_byte, current_byte; 

    output_marker = 0;
    same_bytes_num = 1;
    last_byte = input[0];
    for(n = 1; n < input_size; ++n) {
        current_byte = input[n];
        if(current_byte == last_byte) {
            same_bytes_num++;
        } else {
            /* for single bytes, just copy them, for sequences, repeat value twice as a chain marker */
            if(same_bytes_num == 1) {
                output[output_marker++] = last_byte;
            } else {
                output[output_marker++] = last_byte;
                output[output_marker++] = last_byte;
                output[output_marker++] = (uint8_t)(same_bytes_num & 0xFF);
                output[output_marker++] = (uint8_t)(same_bytes_num >> 8);
            }
            
            same_bytes_num = 1;
        }

        last_byte = current_byte;
    }

    *output_size = output_marker;
}

bench_result_t bench_rle_compression() {
    const int iterations = BENCH_RLE_ITERATIONS;

    size_t initial_size = BENCH_RLE_TEST_DATA_SIZE;
    uint32_t sizes_sum = 0;
    int i;

    bench_result_t result;

    for(i = 0; i < iterations; ++i) {
        uint8_t compressed_data[BENCH_RLE_TEST_DATA_SIZE * 3] = { 0 }; /* compressed data is in worst case 3 times as big */
        size_t compressed_size = 0;

        rle_compress((uint8_t*)test_data, initial_size, compressed_data, &compressed_size);

        sizes_sum += compressed_size;
    }

    result.uint32_value = sizes_sum / iterations;
    
    return result;
}
