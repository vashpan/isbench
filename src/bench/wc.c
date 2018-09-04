/*
*  isbench
*  wc.c
*
*  Word count benchmark
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

#include "utils.h"

#define BENCH_WC_ITERATIONS 500

static const char* test_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tristique ante libero, eu sodales arcu euismod sit amet. Duis nec consequat metus. Donec ut lectus vel dui blandit blandit. Nam luctus scelerisque.";

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

double bench_word_count() {
    const int iterations = BENCH_WC_ITERATIONS;

    int total = 0;
    int i;

    for(i = 0; i < iterations; ++i) { 
        total += wc_count(test_text);
    }

    return (double)(total / iterations);
}