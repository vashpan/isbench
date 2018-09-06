/*
*  isbench
*  qsort.c
*
*  QuickSort simple sort benchmark.
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

#include "qsort.h"
#include "rand.h"

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

bench_result_t bench_quick_sort() {
    const int iterations = BENCH_QSORT_TEST_DATA_SIZE;
    
    size_t i;
    uint32_t sum = 0;

    rnd_init(8657332);
    for(i = 0; i < iterations; ++i) {
        qsort_fill_test_data(test_array, BENCH_QSORT_TEST_DATA_SIZE);

        qsort(test_array, 0, BENCH_QSORT_TEST_DATA_SIZE-1);
        sum += qsort_array_sum(test_array, BENCH_QSORT_TEST_DATA_SIZE);
    }

    bench_result_t result;
    result.uint32_value = sum;

    return result;
}