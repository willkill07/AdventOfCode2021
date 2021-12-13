# AdventOfCode 2021

[![C/C++ CI](https://github.com/willkill07/AdventOfCode2021/actions/workflows/cmake.yml/badge.svg)](https://github.com/willkill07/AdventOfCode2021/actions/workflows/cmake.yml)

## Dependencies

- A C++20 compiler with `std::ranges` support (tested with GCC 11)
- `cmake`
- `git`
- a Unix-like operating system (tested on ArchLinux and macOS)
- `ninja` (optional)

## Downloading

```
git clone --recursive https://github.com/willkill07/AdventOfCode2021.git
```

## Building

If you have `ninja` and want a fast(er) build:

```
cmake -B build -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build --parallel
```

If you don't, just use the Makefile generator:

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

## Running

An `advent` binary lives under the `build` directory.
Invoking it will run all days and report only the answers.

There are some command-line options available:

```
Usage: advent [options] 

Optional arguments:
-h --help       shows help message and exits [default: false]
-v --version    prints version information and exits [default: false]
--mode          execute with mode (one of: run, time, benchmark) [default: "run"]
--day           day to run (0 for all) [default: 0]
--part          part to run (1, 2, or 3 [for all]) [default: 3]
--ntimes        number of times to run (for benchmarking) [default: 10]
```

#### Running a single day

```
./build/advent --day N
```

#### Running a specific part

```
./build/advent --part 1
./build/advent --part 2
```

#### Timing execution

```
./build/advent --mode time
```

#### Benchmarking

```
./build/advent --mode benchmark --ntimes 1000
```

#### Pulling it all together

You can combine various parts together.
For example, if you want to benchmark day 5 part 2 10K times and report the average:
```
./build/advent --mode benchmark --ntimes 10000 --day 5 --part 2
```

## Performance

#### AMD Ryzen 9 5950X

```
$ ./build/advent --mode benchmark --ntimes 10000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |     7.008 us |     0.132 us |     0.132 us |     7.272 us |
|  Day 02   |    15.630 us |     0.834 us |     0.652 us |    17.116 us |
|  Day 03   |    10.925 us |     2.648 us |     5.586 us |    19.160 us |
|  Day 04   |    15.504 us |    17.630 us |    49.872 us |    83.006 us |
|  Day 05   |    11.858 us |   142.120 us |   277.281 us |   431.260 us |
|  Day 06   |     2.771 us |     0.006 us |     0.006 us |     2.782 us |
|  Day 07   |     4.449 us |    35.750 us |   107.971 us |   148.170 us |
|  Day 08   |    48.315 us |     1.904 us |    19.896 us |    70.115 us |
|  Day 09   |     2.768 us |     9.932 us |    59.462 us |    72.162 us |
|  Day 10   |     7.635 us |     8.425 us |     9.088 us |    25.148 us |
|  Day 11   |     2.334 us |    17.260 us |    38.021 us |    57.615 us |
|  Day 12   |     5.427 us |     2.407 us |    19.844 us |    27.678 us |
|  Day 13   |     6.411 us |     8.790 us |     7.998 us |    23.199 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   141.037 us |   247.838 us |   595.807 us |   984.683 us |
+-----------+--------------+--------------+--------------+--------------+
```

#### Apple M1 Pro

```
$ ./build/advent --mode benchmark --ntimes 10000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |    16.674 us |     0.270 us |     0.271 us |    17.215 us |
|  Day 02   |    11.881 us |     2.754 us |     4.515 us |    19.151 us |
|  Day 03   |    17.995 us |     3.515 us |     6.138 us |    27.647 us |
|  Day 04   |    21.842 us |    14.579 us |    45.036 us |    81.457 us |
|  Day 05   |    19.864 us |   120.061 us |   208.601 us |   348.526 us |
|  Day 06   |     8.138 us |     0.002 us |     0.002 us |     8.142 us |
|  Day 07   |    10.287 us |    38.426 us |    81.952 us |   130.665 us |
|  Day 08   |    29.153 us |     0.286 us |     6.408 us |    35.848 us |
|  Day 09   |     7.269 us |    24.329 us |    43.743 us |    75.341 us |
|  Day 10   |    13.193 us |    20.760 us |    10.089 us |    44.042 us |
|  Day 11   |     7.089 us |    12.817 us |    28.485 us |    48.391 us |
|  Day 12   |    10.961 us |     2.599 us |    23.153 us |    36.714 us |
|  Day 13   |    14.235 us |     9.176 us |    18.964 us |    42.375 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   188.583 us |   249.574 us |   477.357 us |   915.514 us |
+-----------+--------------+--------------+--------------+--------------+
```