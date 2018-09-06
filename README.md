# Incredibly Simple Benchmark

A very simple (and naive) benchmark aimed at maximum portability across multiple OSes and independence on any system-specific code.

You may ask: **why?**

I was wondering - how fast current computers are? How many 386s would be required to make a job that our Core i7 can do in a second? Properly measuring performance is not a simple task, a lot of things is decides about that. CPU is one, but we also have a compiler that can produce better optimized code.

The idea is to create a very simple benchmark that will be able to run on multiple both modern and retro platforms.

For this reason it benchmarks only CPU single-threaded integer performance. Floating point tests doesn't make much sense since older CPUs often didn't even had an FPU.

## Approach

All code is not using any standard library functions implicitely, this way it should be easy to port the code to many, even most exotic and old platforms. Currently it's using C89 standard, but many older C compilers may also be able to compile this program. Although it also aim to be readable in 2018 as well, so some very old conventions are not used.

## Benchmarks

Don't expect anything complex, they are mostly here just to make "some" non-trivial work done by the CPU. 

### Random numbers

It's using classic linear-congruential pseudorandom number generator. It's code is also used in some other benchmarks to generate data.

### Word count

Simple algorithm to calculate number of words in a given string.

### CRC32 checksum

Another classic - a 32bit checksum for given data, using this implementation: http://home.thep.lu.se/~bjorn/crc/

### RLE compression algorithm

Very simple, basic compression algorithm

### QuickSort sorting

And yet another immortal classic. Sorting using quick sort algorithm.

## Usage

**isbench** is basically a command line program, on systems that supports command line, it can be started as any such program. For simplicity it doesn't supports any arguments and it just starts benchmarking. Each test is performed for 5 seconds (by default) and total number of "operations" per second is presented. This way older devices won't spend entire day trying to calculate some specific results that for modern hardware is a matter of seconds.

For platforms that doesn't have classic command line (like iOS, Android, classic MacOS) - some extremely simple emulation layer is provided.