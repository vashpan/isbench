/*
*  platform.h
*  isbench
*
*  Platform dependend interface, for modern Unix systems like Linux, macOS, FreeBSD, NetBSD etc.
*  Probably could be used also on other Unix-like systems, also the older one. List will be
*  expanded in the future.
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

#ifdef __linux__ 
#define _POSIX_C_SOURCE 199309L /* to tell Linux Glibc to use proper POSIX standard */
#endif

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "platform.h"

void bench_printf(const char *format, ...) {
    va_list arglist;

    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);
}

void bench_snprintf(char* str, unsigned len, const char* format, ...) {
    va_list arglist;

    va_start(arglist, format);
    vsnprintf(str, len, format, arglist);
    va_end(arglist);
}

double bench_get_time() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);

    return (double)(tp.tv_sec + (tp.tv_nsec / 1E9));
}
