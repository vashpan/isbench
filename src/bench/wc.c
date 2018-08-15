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

#define TRUE 1
#define FALSE 0

typedef unsigned char bool;

#define BENCH_WC_ITERATIONS 500

static const char* test_text = "Hello World! It's a very dark and not a helpful place. We like computers but do they like us?";

static unsigned wc_strlen(const char* text) {
    unsigned len = 0;
    int i = 0;

    for(i=0; text[i] != 0; ++i) {
        len++;
    }

    return len;
}

static bool wc_iswhitespace(char c) {
    if(c == '\n' || c == ' ' || c == '\t' || c == '\r') {
        return TRUE;
    } else {
        return FALSE;
    }
}

static unsigned wc_count(const char* text) {
    char c;
    int i;
    unsigned count = 0;
    bool in_word = FALSE;
    
    if(text == 0) {
        return 0;
    }

    if(wc_strlen(text) == 0) {
        return 0;
    }

    for(i=0; text[i] != 0; ++i) {
        c = text[i];
        if(!wc_iswhitespace(c)) {
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

void bench_word_count() {
    const int iterations = BENCH_WC_ITERATIONS;

    unsigned total = 0;
    int i;

    for(i = 0; i < iterations; ++i) { 
        total += wc_count(test_text);
    }
}