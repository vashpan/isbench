/*
*  platform.h
*  isbench
*
*  Platform dependend interface, for iOS
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
#include "platform_ios.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#import <UIKit/UIKit.h>

#define PRINT_BUFFER_SIZE 2048

UITextView* ios_terminal_text_view = nil;

void bench_printf(const char *format, ...) {
    char buffer[PRINT_BUFFER_SIZE] = { 0 };
    va_list arglist;
    
    va_start(arglist, format);
    vsnprintf(buffer, PRINT_BUFFER_SIZE, format, arglist);
    va_end(arglist);
    
    if(ios_terminal_text_view != nil) {
        NSString* formatted_string = [NSString stringWithUTF8String: buffer];
        dispatch_async(dispatch_get_main_queue(), ^{
            NSString* new_terminal_text = [ios_terminal_text_view.text stringByAppendingString: formatted_string];
            ios_terminal_text_view.text = new_terminal_text;
        });
    }
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
