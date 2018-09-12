# Incredibly Simple Benchmark

A very simple (and naive) benchmark aimed at maximum portability across multiple OSes and independence on any system-specific code.

You may ask: **why?**

I was wondering - how fast current computers are? How many 386s would be required to make a job that our Core i7 can do in a second? Properly measuring performance is not a simple task, a lot of things is decides about that. CPU is one, but we also have a compiler that can produce better optimized code.

The idea is to create a very simple benchmark that will be able to run on multiple both modern and retro platforms. It will also allow to compare raw performance of code optimizations performed by various compilers on the same platforms. Also using standard library could influence performance by a big factor.

For this reason it benchmarks only CPU single-threaded integer performance. Floating point tests doesn't make much sense since older CPUs often didn't even had an FPU.

## Approach

Benchmark code are not using any standard library functions, this way it should be easy to port the code to many, even most exotic and old platforms. Some helper utility functions are implemented in "bench/utils.c" file. Currently code is using C89 standard, but many even older C compilers may also be able to compile this program. 

To compare performance in a more sensible way, possibly oldest version of compiler for given platform is preffered to be used for that purpuse. For example: a MS VC++ 2.0 from 1994 can generate code that still runs on modern version of Windows. This way we can compare a broad spectrum of CPUs: from 386 (minimum requirements for early Windows NTs) up to most modern x86 CPUs that are still capable of running 32bit programs. It'll run the same code on all those CPUs. Of course we will loose some degree of optimizations for modern CPUs but at least modern compiler optimizations won't affect the results.

Most sensible results could be get if we use the same binary and OS across multiple CPUs. Comparing accross platforms and compilers could tell us some story, but remember it won't be 100% accurate.

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

**isbench** is just a simple command line program. On systems that supports command line, it can be started as any such program. For simplicity it doesn't supports any arguments and it just starts benchmarking. Each test is performed for 5 seconds (by default) and total number of "operations" per second is presented. This way older devices won't spend entire day trying to calculate some specific results that for modern hardware is a matter of seconds.

For platforms that doesn't have classic command line (like iOS, Android, classic MacOS) - some extremely simple "terminal emulation" is provided.