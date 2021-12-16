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
$ ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |     7.554 us |     0.146 us |     0.146 us |     7.846 us |
|  Day 02   |    17.141 us |     0.778 us |     0.934 us |    18.852 us |
|  Day 03   |    12.458 us |     2.963 us |     5.582 us |    21.003 us |
|  Day 04   |    17.665 us |    17.745 us |    59.788 us |    95.198 us |
|  Day 05   |    13.495 us |   155.273 us |   302.618 us |   471.385 us |
|  Day 06   |     3.869 us |     0.006 us |     0.006 us |     3.882 us |
|  Day 07   |     4.705 us |    40.150 us |   119.131 us |   163.986 us |
|  Day 08   |    53.670 us |     2.185 us |    22.938 us |    78.793 us |
|  Day 09   |     3.180 us |    11.129 us |    69.965 us |    84.273 us |
|  Day 10   |     8.457 us |    10.899 us |    10.955 us |    30.311 us |
|  Day 11   |     2.523 us |    19.412 us |    42.974 us |    64.909 us |
|  Day 12   |     6.213 us |     3.110 us |    39.491 us |    48.814 us |
|  Day 13   |     6.829 us |    10.458 us |     9.192 us |    26.479 us |
|  Day 14   |     2.865 us |     1.232 us |     4.368 us |     8.465 us |
|  Day 15   |     3.486 us |   205.434 us |  7480.331 us |  7689.250 us |
|  Day 16   |    26.039 us |     0.526 us |     0.619 us |    27.183 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   190.148 us |   481.445 us |  8169.038 us |  8840.631 us |
+-----------+--------------+--------------+--------------+--------------+
```

#### Apple M1 Pro

```
$ ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |    22.224 us |     0.328 us |     0.328 us |    22.880 us |
|  Day 02   |    14.890 us |     3.133 us |     4.856 us |    22.879 us |
|  Day 03   |    18.211 us |     3.585 us |     6.138 us |    27.934 us |
|  Day 04   |    22.830 us |    14.725 us |    45.579 us |    83.134 us |
|  Day 05   |    20.224 us |   122.277 us |   209.700 us |   352.201 us |
|  Day 06   |     8.723 us |     0.002 us |     0.002 us |     8.727 us |
|  Day 07   |    11.214 us |    38.834 us |    82.676 us |   132.724 us |
|  Day 08   |    29.804 us |     0.285 us |     7.106 us |    37.195 us |
|  Day 09   |     7.972 us |    23.599 us |    42.704 us |    74.275 us |
|  Day 10   |    13.960 us |    20.311 us |     9.718 us |    43.989 us |
|  Day 11   |     7.557 us |    13.069 us |    29.148 us |    49.774 us |
|  Day 12   |    11.606 us |     2.935 us |    37.978 us |    52.519 us |
|  Day 13   |    14.562 us |    13.579 us |    14.878 us |    43.019 us |
|  Day 14   |     8.137 us |     1.523 us |     4.856 us |    14.516 us |
|  Day 15   |     8.328 us |   156.804 us |  7013.975 us |  7179.107 us |
|  Day 16   |    34.181 us |     0.384 us |     0.461 us |    35.026 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   254.423 us |   415.373 us |  7510.103 us |  8179.899 us |
+-----------+--------------+--------------+--------------+--------------+
```