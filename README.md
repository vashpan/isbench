# Incredibly Simple Benchmark

A very simple (and naive) integer benchmark aimed at maximum portability across multiple OSes and independence on any system-specific code.

You may ask: **why?**

I was wondering - how fast current computers are? How many 386s would be required to make a job that our Core i7 can do in a second? Properly measuring performance is not a simple task, a lot of things decides about that. CPU is one, but we also have a compiler that can produce better optimized code.

The idea is to create a very simple benchmark that will be able to run on multiple, both modern and retro platforms. It would also allow to compare raw performance of code optimizations performed by various compilers on the same platforms. 

It benchmarks only CPU single-threaded integer performance. Floating point tests doesn't make much sense since older CPUs often didn't even had an FPU, or it was very slow compared to integer unit. 

## Approach

Benchmark code is not using any standard library functions. It's more fair this way, as standard library implementations or optimizations vary from platform to platform. It would also allow to port the code for even most barebone platforms, like microcontrollers. 

Currently code is using C89 standard, but many even older C compilers may also be able to compile this program. 

To compare performance in a more sensible way, possibly oldest version of compiler for given platform is preffered to be used for that purpuse. For example: a MS VC++ 2.0 from 1994 can generate code that still runs on modern version of Windows. This way we can compare a broad spectrum of CPUs: from 386 (minimum requirements for early Windows NTs) up to most modern x86 CPUs that are still capable of running 32bit programs. It'll run the same code on all those CPUs. Of course we will loose some degree of optimizations for modern CPUs but at least modern compiler optimizations won't affect the results.

Most sensible results could be get if we use the same binary and OS across multiple CPUs. Comparing accross platforms and compilers could tell us some story, but remember it won't be 100% accurate.

## Usage

**isbench** is a simple command line program. On systems that supports command line, it can be started as any such program. For simplicity it doesn't supports any arguments and it just starts benchmarking. Each test is performed for 5 seconds (by default) and total number of "operations" per second is presented. This way older devices won't spend entire day trying to calculate some specific results that for modern hardware is a matter of seconds.

For platforms that doesn't have classic command line (like iOS, Android, classic MacOS) - some extremely simple "terminal emulation" is provided.

## Porting

Code is structured as simple as possible, to allow easy porting to other platforms.

In order to support a new platform, you must implement functions that are declared in `src/platform.h` file. Do do that, create a new folder in `src/platform` folder with necessary files required to run on a given platform.

A `main` function must be provided as well, as an entry point for the application.

If you're using some IDE or build system, you also need to place your IDE-specific files within a folder inside `build` folder. There could be many IDEs/compilers for a given platform.

Check for existing implementation for examples.

## Results

I plan to create a dedicated repository/website that will host results. For now you can submit me your results via [Twitter](https://twitter.com/vashpan).

Submit following informations: 

CPU type
L1, L2, L3 cache (if possible)
Machine type (PC, Microcontroller, SBC...)
Operating system (with version)
Compiler (with version)
Results (all benchmarks + total score)

## Benchmarks

Don't expect anything complex, they are mostly here just to make "some" non-trivial work done by the CPU. Score is calculated against i486DX4 CPU running on Windows NT 3.5.

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
