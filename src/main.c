/*
*  isbench
*  main.c
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
#include "utils.h"
#include "bench.h"

#define ISBENCH_VERSION "1.0.0"

#define BENCH_TIME 5.0 /* benchmark time of one test in seconds */

#define NUMBER_STRING_SIZE 128 /* maximum size of score string */

typedef enum {
    BENCH_TYPE_RAND = 0,
    BENCH_TYPE_WC,
    BENCH_TYPE_CRC32,
    BENCH_TYPE_RLE,
    BENCH_TYPE_QSORT,

    BENCH_TYPE_MAX
} bench_type;

static void format_score_number(int64_t number, char* result, unsigned result_size) {
    double new_value = (double)number;
    int multiplier = 0;
    const int limit = 3; /* billions at most */
    char size_postfix;

    /* divide number until to at least k */
    while(new_value > 1000.0 && multiplier <= limit) {
        new_value /= 1000.0;
        multiplier++;
    } 

    /* format value properly */
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

static void print_results(bench_type type, int64_t iterations[BENCH_TYPE_MAX], bench_result_t results[BENCH_TYPE_MAX]) {
    char results_string[NUMBER_STRING_SIZE] = { 0 };
    long result = (long)iterations[type];
    format_score_number(result, results_string, NUMBER_STRING_SIZE);

    switch(type) {
        case BENCH_TYPE_RAND: bench_printf("Random numbers (%.2f):\t\t%s / s\n", results[type].double_value, results_string); break;
        case BENCH_TYPE_WC: bench_printf("Word Count (%d):\t\t\t%s / s\n", results[type].int_value, results_string); break;
        case BENCH_TYPE_CRC32: bench_printf("CRC32 (0x%X):\t\t\t%s / s\n", results[type].uint32_value, results_string); break;
        case BENCH_TYPE_RLE: bench_printf("RLE (%.2f%%):\t\t\t\t%s / s\n", results[type].double_value, results_string); break;
        case BENCH_TYPE_QSORT: bench_printf("Sort (%d):\t\t\t\t%s / s\n", results[type].uint32_value, results_string); break;

        default: bench_printf("???: \t\t\t%s\n", results_string); break;
    }
}

static void print_score(int64_t iterations[BENCH_TYPE_MAX]) {
    double points_sum = 0.0, points = 0.0;
    int type;

    /* baseline results for i486DX4 100Mhz on Windows NT 3.5 */
    static int64_t baseline[BENCH_TYPE_MAX] = {
        1500000, /* random numbers */
        6800, /* word count */
        6700, /* CRC32 */
        3500, /* RLE */
        8700 /* QuickSort */
    };

    for(type=0; type<BENCH_TYPE_MAX; ++type) {
        points_sum += (((double)iterations[type] / (double)baseline[type]) * 100.0);
    }

    points = points_sum / BENCH_TYPE_MAX;

    bench_printf("\nScore: %.2fpts\n", points);
}

int bench_main(int argc, char const *argv[]) {
    static int64_t iterations[BENCH_TYPE_MAX] = { 0 };
    static bench_result_t results[BENCH_TYPE_MAX] = { 0.0 };

    int type;
    uint32_t number_of_iterations;
    double start;
    double current, elapsed_time, time_remainder;

    /* start benchmarking */
    bench_printf("Incredibly Simple Benchmark! %s (%d seconds per test) \n\n", ISBENCH_VERSION, (int)BENCH_TIME);
    
    for(type=0; type<BENCH_TYPE_MAX; ++type) {
        start = bench_get_time();
        do {
            number_of_iterations = 1;
            switch(type) {
                case BENCH_TYPE_RAND: 
                    results[type] = bench_random_numbers(); 
                    number_of_iterations = BENCH_RND_ITERATIONS;
                    break;

                case BENCH_TYPE_WC: 
                    results[type] = bench_word_count();
                    number_of_iterations = BENCH_WC_ITERATIONS;
                    break;

                case BENCH_TYPE_CRC32: 
                    results[type] = bench_crc32_hashes(); 
                    number_of_iterations = BENCH_CRC32_ITERATIONS;
                    break;

                case BENCH_TYPE_RLE: 
                    results[type] = bench_rle_compression(); 
                    number_of_iterations = BENCH_RLE_ITERATIONS;
                    break;

                case BENCH_TYPE_QSORT: 
                    results[type] = bench_quick_sort();
                    number_of_iterations = BENCH_QSORT_ITERATIONS;
                    break;
            }

            iterations[type] += (int64_t)(number_of_iterations / BENCH_TIME);

            current = bench_get_time();
            elapsed_time = current - start;
        } while(elapsed_time <= BENCH_TIME);

        /* include time remainder and modify results accordingly */
        time_remainder = BENCH_TIME - elapsed_time;
        iterations[type] += (int64_t)(iterations[type] * (time_remainder / BENCH_TIME));

        /* print results for current benchmark */
        print_results(type, iterations, results);
    }

    print_score(iterations);

    return 0;
}
