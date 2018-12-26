/*
*  isbench
*  utils.c
*
*  Common utility functions used by benchmark code.
*  Many of them are just reimplementation of standard library functions.
*  They are implemented here to avoid standard-library dependency on performance.
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

void isb_strzero(char* dst, size_t size) {
    while(--size > 0) {
        *dst = '\0';
    }
}

unsigned isb_strlen(const char* text) {
    unsigned len = 0;
    int i = 0;

    for(i=0; text[i] != 0; ++i) {
        len++;
    }

    return len;
}

bool isb_iswhitespace(char c) {
    if(c == '\n' || c == ' ' || c == '\t' || c == '\r') {
        return TRUE;
    } else {
        return FALSE;
    }
}

char* isb_strcat(char* dst, const char* txt) {
    char* save_dst = dst;

    /* find end of string */
    while(*dst != '\0') {
        ++dst;
    } 

    /* add our source text */
    while((*dst++ = *txt++) != '\0');

    return save_dst;
}