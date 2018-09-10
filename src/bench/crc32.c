/*
*  isbench
*  crc32.c
*
*  CRC32 checksum benchmark.
*  Code used from: http://home.thep.lu.se/~bjorn/crc/
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

#include "crc32.h"
#include "utils.h"

static const char* test_data = "UORHDtOXVBF0BzSF c7MTtHDLhZXtwMgi Je4SupV53NBXOU0N 6Kw6eIOxL0KbHMCM zHHVvQUQVkkjGhSS 2WT3UTbloTxqrj4M";

static uint32_t crc32_for_byte(uint32_t r) {
	int j;
    for(j = 0; j < 8; ++j) {
        r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
    }

    return r ^ (uint32_t)0xFF000000L;
}

static void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
    static uint32_t table[0x100];
    size_t i;

    if(!*table) {
        for(i = 0; i < 0x100; ++i) {
            table[i] = crc32_for_byte(i);
        }
    }

    for(i = 0; i < n_bytes; ++i) {
        *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
    }
}

bench_result_t bench_crc32_hashes() {
    const int iterations = BENCH_CRC32_ITERATIONS;

    size_t bytes_num = isb_strlen(test_data);
    uint32_t crc32num;
    uint32_t result_hash = 0;
    int i;

    bench_result_t result;

    for(i = 0; i < iterations; ++i) {
        crc32(test_data, bytes_num, &crc32num); /* do not include nul character at the end of the string */
        result_hash ^= crc32num;
    }

    result.uint32_value = result_hash;
    
    return result;
}
