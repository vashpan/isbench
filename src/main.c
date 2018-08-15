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
#include "bench/rand.h"

#define ISBENCH_VERSION "1.0.0"

#define BENCH_TIME 5.0 /* total benchmark time in seconds */

#define NUMBER_STRING_SIZE 128 /* maximum size of score string */

enum bench_type {
    BENCH_TYPE_RAND = 0,

    BENCH_TYPE_MAX
};

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

static void print_results(long iterations[BENCH_TYPE_MAX]) {
    bench_printf("\n");

    int i;
    for(i=0; i<BENCH_TYPE_MAX; ++i) {
        if(i == BENCH_TYPE_RAND) {
            char number_string[NUMBER_STRING_SIZE] = { 0 };
            long result = iterations[i];
            format_score_number(result, number_string, NUMBER_STRING_SIZE);
            
            bench_printf("Linear Congruential RNG:\t\t%s\n", number_string);
        }
    }
}

int bench_main(int argc, char const *argv[]) {
    bench_printf("Incredibly Simple Benchmark! %s \n", ISBENCH_VERSION);

    /* start benchmarking */
    static long iterations[BENCH_TYPE_MAX] = { 0 };

    double start = bench_get_time();
    double current, elapsed_time, time_remainder;
    do {
        /* perform one iteration of benchmarks */
        bench_random_numbers();
        iterations[BENCH_TYPE_RAND]++;

        current = bench_get_time();
        elapsed_time = current - start;
    } while(elapsed_time <= BENCH_TIME);

    /* include time remainder and modify results accordingly */
    time_remainder = BENCH_TIME - elapsed_time;
    
    int i;
    for(i=0; i<BENCH_TYPE_MAX; ++i) {
        iterations[i] += (iterations[i] * (time_remainder / BENCH_TIME));
    }

    /* printing results */
    print_results(iterations);

    return 0;
}
