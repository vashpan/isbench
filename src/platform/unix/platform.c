/*
*  platform.h
*  isbench
*
*  Platform dependend interface, for modern Unix systems like Linux, macOS, FreeBSD, NetBSD etc.
*  Probably could be used also on other Unix-like systems, also the older one. List will be
*  expanded in the future.
*
*  isbench is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.
*
*  isbench is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with isbench. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdarg.h>

#include "platform.h"

void bench_printf(const char * format, ...) {
    va_list arglist;

    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);


}
