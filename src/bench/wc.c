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

#include "wc.h"
#include "rand.h"
#include "utils.h"

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
