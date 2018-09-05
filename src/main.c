/*
*  isbench
*  bmain.c
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

#include "platform.h"

#include "bench/result.h"
#include "bench/rand.h"
#include "bench/wc.h"
#include "bench/crc32.h"
#include "bench/rle.h"

#define ISBENCH_VERSION "1.0.0"

#define BENCH_TIME 5.0 /* benchmark time of one test in seconds */

#define NUMBER_STRING_SIZE 128 /* maximum size of score string */

typedef enum {
    BENCH_TYPE_RAND = 0,
    BENCH_TYPE_WC,
    BENCH_TYPE_CRC32,
    BENCH_TYPE_RLE,

    BENCH_TYPE_MAX
} bench_type;

static void format_score_number(long number, char* result, unsigned result_size) {
    /* divide number until to at least k */
    double new_value = number;
    int multiplier = 0;
    const int limit = 3; /* billions at most */

    while(new_value > 1000.0 && multiplier <= limit) {
        new_value /= 1000.0;
        multiplier++;
    } 

    /* format value properly */
    char size_postfix;
    
    switch (multiplier) {
        case 1:
            size_postfix = 'k';
            break;
        
        case 2:
           size_postfix = 'M';
           break;

        case 3:
            size_postfix = 'G';
            break;

        default:
            size_postfix = 0;
            break;
    }

    bench_snprintf(result, result_size, "%.1f%c", new_value, size_postfix);
}

static void print_results(bench_type type, long iterations[BENCH_TYPE_MAX], bench_result_t results[BENCH_TYPE_MAX]) {
    char results_string[NUMBER_STRING_SIZE] = { 0 };
    long result = iterations[type];
    format_score_number(result, results_string, NUMBER_STRING_SIZE);

    switch(type) {
        case BENCH_TYPE_RAND: bench_printf("Random numbers (%.2f):\t\t%s\n", results[type].double_value, results_string); break;
        case BENCH_TYPE_WC: bench_printf("Word Count (%d):\t\t\t%s\n", results[type].int_value, results_string); break;
        case BENCH_TYPE_CRC32: bench_printf("CRC32 (0x%X):\t\t\t%s\n", results[type].uint32_value, results_string); break;
        case BENCH_TYPE_RLE: bench_printf("RLE (%d):\t\t\t\t%s\n", results[type].uint32_value, results_string); break;

        default: bench_printf("???: \t\t\t%s\n", results_string); break;
    }
}

int bench_main(int argc, char const *argv[]) {
    bench_printf("Incredibly Simple Benchmark! %s (%d seconds per test) \n\n", ISBENCH_VERSION, (int)BENCH_TIME);

    /* start benchmarking */
    static long iterations[BENCH_TYPE_MAX] = { 0 };
    static bench_result_t results[BENCH_TYPE_MAX] = { 0.0 };

    int i;
    double start;
    double current, elapsed_time, time_remainder;
    for(i=0; i<BENCH_TYPE_MAX; ++i) {
        start = bench_get_time();
        do {
            /* perform specific benchmark */
            if(i == BENCH_TYPE_RAND) {
                results[i] = bench_random_numbers();
            } 
            
            if(i == BENCH_TYPE_WC) {
                results[i] = bench_word_count();
            }

            if(i == BENCH_TYPE_CRC32) {
                results[i] = bench_crc32_hashes();
            }

            if(i == BENCH_TYPE_RLE) {
                results[i] = bench_rle_compression();
            }

            iterations[i]++;

            current = bench_get_time();
            elapsed_time = current - start;
        } while(elapsed_time <= BENCH_TIME);

        /* print results for current benchmark */
        print_results(i, iterations, results);
    }

    /* include time remainder and modify results accordingly */
    time_remainder = BENCH_TIME - elapsed_time;
    
    int j;
    for(j=0; j<BENCH_TYPE_MAX; ++j) {
        iterations[j] += (iterations[j] * (time_remainder / BENCH_TIME));
    }

    return 0;
}
