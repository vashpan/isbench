/*
*  isbench
*  bench.c
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

#include "utils.h"
#include "bench.h"

/********************************************************************************/
/******************************** RANDOM NUMBERS ********************************/
/********************************************************************************/

#define BENCH_RND_SEED 4345

static int rnd_state = 0;
static const int rnd_max = ((1U << 15) - 1);

static void rnd_init(int seed) {
    rnd_state = seed;
}

static int rnd_get_int() {
    rnd_state = (rnd_state * 214013 + 2531011) & rnd_max;
	return rnd_state;
}

static int rnd_get_int_range(int from, int to) {
    int range = to - from;

	return from + rnd_get_int() % range;
}

/********************************************************************************/
/********************************** WORD COUNT **********************************/
/********************************************************************************/

#define WC_TEST_WORDS_NUMBER 32
#define WC_MAX_TEST_DATA_SIZE 512 /* check if the longest word times max words number doesn't exceed this value! */

static const char* test_words[WC_TEST_WORDS_NUMBER] = {
    "lorem",
    "ipsum",
    "dolor",
    "sit", 
    "amet", 
    "consectetur", 
    "adipiscing", 
    "elit", 
    "sed", 
    "tristique", 
    "ante", 
    "libero", 
    "eu", 
    "sodales", 
    "arcu", 
    "euismod", 
    "sit", 
    "amet", 
    "duis",
    "nec",
    "consequat",
    "metus", 
    "donec", 
    "ut", 
    "lectus", 
    "vel", 
    "dui", 
    "blandit", 
    "blandit", 
    "nam", 
    "luctus", 
    "scelerisque"
};

static unsigned wc_count(const char* text) {
    char c;
    int i;
    unsigned count = 0;
    bool in_word = FALSE;
    
    if(text == 0) {
        return 0;
    }

    if(isb_strlen(text) == 0) {
        return 0;
    }

    for(i=0; text[i] != 0; ++i) {
        c = text[i];

        /* exit early if we have character zero */
        if(c == '\0') {
            /* if we were previously in word, increase word count */
            if(in_word) {
                count++;
            }

            break;
        }

        if(!isb_iswhitespace(c)) {
            in_word = TRUE;
        } else {
            /* if we were previously in word, increase word count */
            if(in_word) {
                count++;
            }

            in_word = FALSE;
        }
    }

    return count;
}

static void wc_create_test_text(char* text, int number_of_words, size_t max_size) {
    const char* current_word;

    /* zero test text */
    isb_strzero(text, max_size);

    /* add random words */
    while(--number_of_words > 0) {
        current_word = test_words[rnd_get_int_range(0, WC_TEST_WORDS_NUMBER)];
        text = isb_strcat(text, current_word);

        /* don't append space to the last one */
        if(number_of_words >= 1) {
            text = isb_strcat(text, " ");
        }
    }
}

/********************************************************************************/
/************************************ CRC32 *************************************/
/********************************************************************************/

#define CRC32_TEST_DATA_SIZE 128

static char test_crc32_data[CRC32_TEST_DATA_SIZE] = { 0 };

static uint32_t crc32_for_byte(uint32_t r) {
	int j;
    for(j = 0; j < 8; ++j) {
        r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
    }

    return r ^ (uint32_t)0xFF000000L;
}

static void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
    static uint32_t table[0x100] = { 0 };
    size_t i;

    if(!*table) {
        for(i = 0; i < 0x100; ++i) {
            table[i] = crc32_for_byte((uint32_t)i);
        }
    }

    *crc = 0;
    for(i = 0; i < n_bytes; ++i) {
        *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
    }
}

static void crc32_fill_test_data(char array[], size_t size) {
    size_t i;

    for(i = 0; i < size; ++i) {
        array[i] = (char)rnd_get_int_range(32, 126);
    }
}

/********************************************************************************/
/******************************* RLE COMPRESSION ********************************/
/********************************************************************************/

#define RLE_TEST_DATA_SIZE 1024

static uint8_t test_rle_data[RLE_TEST_DATA_SIZE] = { 0 };

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
    size_t i, next_chunk_size = 0;
    uint8_t next_chunk_value = 0;

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

/********************************************************************************/
/********************************** QUICK SORT **********************************/
/********************************************************************************/

#define BENCH_QSORT_TEST_DATA_SIZE 64

static int test_array[BENCH_QSORT_TEST_DATA_SIZE] = { 0 };

static void qsort_fill_test_data(int array[], size_t size) {
    size_t i;

    for(i = 0; i < size; ++i) {
        array[i] = rnd_get_int_range(0, 100);
    }
}

static uint32_t qsort_array_sum(int array[], size_t size) {
    uint32_t result = 0;

    size_t i;
    for(i = 0; i < size; ++i) {
        result += array[i];
    }

    return result;
}

static void qsort_swap(int array[], size_t i1, size_t i2) {
    int aux = array[i1];
    array[i1] = array[i2];
    array[i2] = aux;
}

static void qsort(int array[], int l, int r) {
    int i = l, j = r;
    int x = array[l + (r - l) / 2]; /* middle element */
    
    do {
        while(array[i] < x) ++i;
        while(array[j] > x) --j;

        if(i <= j) {
            qsort_swap(array, i, j);
            ++i; --j;
        }
    } while(i < j);

    if(l < j) qsort(array, l, j);
    if(r > i) qsort(array, i, r);
}

/********************************************************************************/
/******************************** BENCHMARKS API ********************************/
/********************************************************************************/

bench_result_t bench_random_numbers() {
    const int iterations = BENCH_RND_ITERATIONS;
    const int seed = BENCH_RND_SEED;
    
    int i = 0;
    double avg;
    
    bench_result_t result;

    rnd_init(seed);

    avg = 0.0;
    for(i = 0; i < iterations; ++i) {
        avg += rnd_get_int();
        avg /= 2.0;
    }

    result.double_value = avg;
    
    return result;
}

bench_result_t bench_word_count() {
    const int iterations = BENCH_WC_ITERATIONS;

    int number_of_words;
    char test_text[WC_MAX_TEST_DATA_SIZE] = { 0 };

    int total = 0;
    int i;
    
    bench_result_t result;

    rnd_init(8657332);

    for(i = 0; i < iterations; ++i) {
        number_of_words = rnd_get_int_range(16, 32);
        wc_create_test_text(test_text, number_of_words, WC_MAX_TEST_DATA_SIZE);

        total += wc_count(test_text);
    }

    result.int_value = total / iterations;
    
    return result;
}

bench_result_t bench_crc32_hashes() {
    const int iterations = BENCH_CRC32_ITERATIONS;

    uint32_t crc32num;
    uint32_t result_hash = 0;
    int i;

    bench_result_t result;

    rnd_init(8657332);

    for(i = 0; i < iterations; ++i) {
        crc32_fill_test_data(test_crc32_data, CRC32_TEST_DATA_SIZE);

        crc32(test_crc32_data, CRC32_TEST_DATA_SIZE, &crc32num); /* do not include nul character at the end of the string */
        result_hash ^= crc32num;
    }

    result.uint32_value = result_hash;
    
    return result;
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
        rle_fill_test_data(test_rle_data, RLE_TEST_DATA_SIZE);

        isb_strzero((char*)compressed_data, RLE_TEST_DATA_SIZE * 3); 
        compressed_size = 0;
        rle_compress((uint8_t*)test_rle_data, data_size, compressed_data, &compressed_size);

        compression_factor_sum += ((double)compressed_size / (double)data_size);
    }

    result.double_value = (compression_factor_sum / iterations) * 100.0;
    
    return result;
}

bench_result_t bench_quick_sort() {
    const size_t iterations = BENCH_QSORT_TEST_DATA_SIZE;
    
    size_t i;
    uint32_t sum = 0;
    bench_result_t result;
    
    rnd_init(8657332);
    
    for(i = 0; i < iterations; ++i) {
        qsort_fill_test_data(test_array, BENCH_QSORT_TEST_DATA_SIZE);

        qsort(test_array, 0, BENCH_QSORT_TEST_DATA_SIZE-1);
        sum += qsort_array_sum(test_array, BENCH_QSORT_TEST_DATA_SIZE);
    }

    result.uint32_value = sum;

    return result;
}
