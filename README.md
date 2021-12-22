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
$ cmake -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -G Ninja -DCMAKE_CXX_FLAGS='-march=native'
$ cmake --build build -j
$ OMP_NUM_THREADS=16 KMP_AFFINITY=compact ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |     6.912 us |     0.080 us |     0.079 us |     7.071 us |
|  Day 02   |    15.807 us |     0.689 us |     0.718 us |    17.214 us |
|  Day 03   |    11.127 us |     1.376 us |     3.793 us |    16.296 us |
|  Day 04   |    16.255 us |    18.226 us |    50.746 us |    85.226 us |
|  Day 05   |    12.056 us |   150.973 us |   289.865 us |   452.895 us |
|  Day 06   |     2.891 us |     0.006 us |     0.006 us |     2.902 us |
|  Day 07   |     4.517 us |    10.658 us |    27.098 us |    42.273 us |
|  Day 08   |    51.477 us |     0.234 us |     6.814 us |    58.525 us |
|  Day 09   |     2.845 us |    10.222 us |    60.998 us |    74.065 us |
|  Day 10   |     7.780 us |     8.816 us |     9.251 us |    25.847 us |
|  Day 11   |     2.458 us |    17.571 us |    38.638 us |    58.666 us |
|  Day 12   |     5.736 us |     2.750 us |    34.149 us |    42.635 us |
|  Day 13   |     6.602 us |     8.761 us |    12.331 us |    27.694 us |
|  Day 14   |     2.666 us |     1.190 us |     3.982 us |     7.838 us |
|  Day 15   |     3.084 us |   196.633 us |  6982.930 us |  7182.647 us |
|  Day 16   |    23.263 us |     0.461 us |     0.561 us |    24.284 us |
|  Day 17   |     2.498 us |     0.006 us |   120.323 us |   122.827 us |
|  Day 18   |     7.866 us |   215.467 us |   375.377 us |   598.710 us |
|  Day 19   |    17.129 us | 13452.041 us |    31.670 us | 13500.840 us |
|  Day 20   |    17.100 us |    29.589 us |  1436.640 us |  1483.329 us |
|  Day 21   |     5.515 us |     0.225 us |    82.917 us |    88.657 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   225.583 us | 14125.973 us |  9568.885 us | 23920.441 us |
+-----------+--------------+--------------+--------------+--------------+
```

#### Apple M1 Pro

Note: multi-threaded times appear to be sequential(?!?!)

```
$ cmake -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -G Ninja
$ cmake --build build -j
$ OMP_NUM_THREADS=8 KMP_AFFINITY=compact ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |    23.528 us |     0.359 us |     0.356 us |    24.243 us |
|  Day 02   |    14.933 us |     3.155 us |     5.065 us |    23.153 us |
|  Day 03   |    18.943 us |     3.516 us |     6.262 us |    28.721 us |
|  Day 04   |    22.095 us |    14.626 us |    50.452 us |    87.173 us |
|  Day 05   |    19.745 us |   152.645 us |   241.114 us |   413.504 us |
|  Day 06   |     8.109 us |     0.001 us |     0.002 us |     8.112 us |
|  Day 07   |    10.237 us |    38.642 us |    81.899 us |   130.778 us |
|  Day 08   |    30.247 us |     0.284 us |     6.576 us |    37.107 us |
|  Day 09   |     7.368 us |    25.599 us |    49.881 us |    82.848 us |
|  Day 10   |    12.720 us |    19.853 us |    11.094 us |    43.667 us |
|  Day 11   |     7.148 us |    13.051 us |    28.612 us |    48.811 us |
|  Day 12   |    10.742 us |     3.018 us |    37.243 us |    51.003 us |
|  Day 13   |    14.333 us |    10.048 us |    21.214 us |    45.595 us |
|  Day 14   |     7.488 us |     1.507 us |     4.799 us |    13.794 us |
|  Day 15   |     7.668 us |   148.607 us |  6989.595 us |  7145.870 us |
|  Day 16   |    33.626 us |     0.383 us |     0.460 us |    34.469 us |
|  Day 17   |     7.063 us |     0.001 us |   166.335 us |   173.399 us |
|  Day 18   |    17.501 us |   266.918 us |  1121.863 us |  1406.282 us |
|  Day 19   |    29.818 us | 16437.345 us |   152.863 us | 16620.026 us |
|  Day 20   |    34.107 us |   239.465 us |  7682.529 us |  7956.101 us |
|  Day 21   |     8.285 us |     0.285 us |    87.287 us |    95.857 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   345.704 us | 17379.308 us | 16745.501 us | 34470.513 us |
+-----------+--------------+--------------+--------------+--------------+
```