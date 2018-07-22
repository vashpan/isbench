/*
*  platform.h
*  isbench
*
*  Platform dependend interface, should be implemented  
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

/* should be defined in platform "main" function and called just after environment setup */
int bench_main(int argc, char const *argv[]);

/* printing functions */
void bench_printf(const char * format, ...);



