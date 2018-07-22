/*
*  isbench
*  main.c
*
*  Main entry point for moder Unix OS'es
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

#include "platform.h"

int main(int argc, char const *argv[]) {
    return bench_main(argc, argv);
}
