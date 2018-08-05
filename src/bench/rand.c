/*
*  isbench
*  rand.c
*
*  Random number generator benchmark
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

#include "rand.h"

static int rnd_state = 0;
static const int rnd_max = ((1U << 15) - 1);

static void rnd_init(int seed) {
    rnd_state = seed;
}

static int rnd_get_int() {
    rnd_state = (rnd_state * 214013 + 2531011) & rnd_max;
	return rnd_state;
}

void bench_random_numbers() {
    const int iterations = BENCH_RND_ITERATIONS;
    const int seed = BENCH_RND_SEED;
    
    int i = 0;
    double avg;

    rnd_init(seed);

    avg = 0.0;
    for(i = 0; i < iterations; ++i) {
        avg += rnd_get_int();
        avg /= 2.0;
    }
}