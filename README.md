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
|  Day 01   |    13.783 us |     0.218 us |     0.220 us |    14.221 us |
|  Day 02   |    16.069 us |     0.867 us |     0.698 us |    17.635 us |
|  Day 03   |    11.108 us |     2.728 us |     4.903 us |    18.739 us |
|  Day 04   |    14.675 us |    18.549 us |    53.599 us |    86.823 us |
|  Day 05   |    12.708 us |   143.091 us |   273.388 us |   429.186 us |
|  Day 06   |     2.717 us |     0.006 us |     0.006 us |     2.728 us |
|  Day 07   |     4.714 us |    36.928 us |   110.910 us |   152.552 us |
|  Day 08   |    51.066 us |     1.971 us |    21.000 us |    74.038 us |
|  Day 09   |     2.833 us |     8.374 us |    64.176 us |    75.383 us |
|  Day 10   |     7.784 us |    10.075 us |    10.158 us |    28.017 us |
|  Day 11   |     2.323 us |    17.607 us |    39.173 us |    59.103 us |
|  Day 12   |     5.686 us |     2.853 us |    34.378 us |    42.917 us |
|  Day 13   |     6.722 us |     9.147 us |     8.289 us |    24.158 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   152.189 us |   252.413 us |   620.899 us |  1025.501 us |
+-----------+--------------+--------------+--------------+--------------+
```

#### Apple M1 Pro

```
$ ./build/advent --mode benchmark --ntimes 10000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |    16.874 us |     0.272 us |     0.271 us |    17.416 us |
|  Day 02   |    12.187 us |     2.756 us |     4.519 us |    19.462 us |
|  Day 03   |    17.009 us |     3.512 us |     6.418 us |    26.939 us |
|  Day 04   |    22.009 us |    14.765 us |    44.744 us |    81.517 us |
|  Day 05   |    20.069 us |   152.281 us |   240.249 us |   412.598 us |
|  Day 06   |     8.221 us |     0.002 us |     0.002 us |     8.224 us |
|  Day 07   |    10.203 us |    39.347 us |    82.093 us |   131.643 us |
|  Day 08   |    29.750 us |     0.286 us |     6.405 us |    36.441 us |
|  Day 09   |     7.263 us |    24.009 us |    43.157 us |    74.430 us |
|  Day 10   |    12.711 us |    19.809 us |    10.076 us |    42.596 us |
|  Day 11   |     7.211 us |    12.793 us |    28.501 us |    48.505 us |
|  Day 12   |    10.877 us |     2.947 us |    37.262 us |    51.086 us |
|  Day 13   |    14.234 us |     9.118 us |    15.637 us |    38.990 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   188.616 us |   281.897 us |   519.333 us |   989.846 us |
+-----------+--------------+--------------+--------------+--------------+
```