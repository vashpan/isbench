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
#include "rand.h"
#include "utils.h"

#define RLE_TEST_DATA_SIZE 1024

static uint8_t test_data[RLE_TEST_DATA_SIZE] = { 0 };

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

static void rle_fill_test_data(uint8_t data[], size_t size) {
    size_t i, next_chunk_size;
    uint8_t next_chunk_value;

    next_chunk_size = 0;
    for(i = 0; i < size; ++i) {
        if(next_chunk_size == 0) {
            next_chunk_size = (size_t)rnd_get_int_range(1, 64);
            next_chunk_value = (uint8_t)rnd_get_int_range(0, 255);
        }

        data[i] = next_chunk_value;

        next_chunk_size--;
    }
}

bench_result_t bench_rle_compression() {
    const int iterations = BENCH_RLE_ITERATIONS;

    size_t data_size = RLE_TEST_DATA_SIZE;
    size_t compressed_size;
    uint8_t compressed_data[RLE_TEST_DATA_SIZE * 3]; /* compressed data is in worst case 3 times as big */

    double compression_factor_sum = 0.0;
    int i;

    bench_result_t result;

    rnd_init(8657332);

    for(i = 0; i < iterations; ++i) {
        rle_fill_test_data(test_data, RLE_TEST_DATA_SIZE);

        isb_strzero((char*)compressed_data, RLE_TEST_DATA_SIZE * 3); 
        compressed_size = 0;
        rle_compress((uint8_t*)test_data, data_size, compressed_data, &compressed_size);

        compression_factor_sum += ((double)compressed_size / (double)data_size);
    }

    result.double_value = (compression_factor_sum / iterations) * 100.0;
    
    return result;
}
