/*
*  platform.h
*  isbench
*
*  Platform dependend interface, for Win32 systems like Windows NT, Windows 9x and modern Windows.
*  Including modern 64-bit versions of Windows.
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

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

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
    vsprintf(str, format, arglist);
    va_end(arglist);
}

double bench_get_time() {
    LARGE_INTEGER freq, cycles;
    
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&cycles);

    return (double)cycles.QuadPart / (double)freq.QuadPart;
}

