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
$ OMP_NUM_THREADS=16 OMP_PLACES=cores OMP_PROC_BIND=true KMP_AFFINITY=compact ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+                                                                   
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |                                                                   
+-----------+--------------+--------------+--------------+--------------+                                                                   
|  Day 01   |     7.088 us |     0.087 us |     0.086 us |     7.261 us |                                                                   
|  Day 02   |    15.545 us |     0.681 us |     0.687 us |    16.912 us |                                                                   
|  Day 03   |    10.900 us |     1.349 us |     3.776 us |    16.025 us |                                                                   
|  Day 04   |    15.941 us |    17.855 us |    48.923 us |    82.718 us |                                                                   
|  Day 05   |    11.893 us |   146.052 us |   280.331 us |   438.277 us |                                                                   
|  Day 06   |     2.746 us |     0.006 us |     0.006 us |     2.757 us |                                                                   
|  Day 07   |     4.456 us |    10.299 us |    26.293 us |    41.048 us |                                                                   
|  Day 08   |    48.344 us |     0.231 us |     6.578 us |    55.153 us |                                                                   
|  Day 09   |     2.749 us |     9.991 us |    59.558 us |    72.299 us |                                                                   
|  Day 10   |     7.429 us |     8.553 us |     8.987 us |    24.968 us |                                                                   
|  Day 11   |     2.282 us |    17.146 us |    37.591 us |    57.018 us |                                                                   
|  Day 12   |     5.463 us |     2.663 us |    33.153 us |    41.279 us |                                                                   
|  Day 13   |     6.321 us |     8.578 us |    12.133 us |    27.031 us |                                                                   
|  Day 14   |     2.548 us |     1.049 us |     3.970 us |     7.567 us |                                                                   
|  Day 15   |     2.873 us |   193.819 us |  6778.715 us |  6975.408 us |                                                                   
|  Day 16   |    22.241 us |     0.446 us |     0.545 us |    23.232 us |                                                                   
|  Day 17   |     2.272 us |     0.005 us |   117.415 us |   119.693 us |                                                                   
|  Day 18   |     7.438 us |   208.303 us |   404.479 us |   620.220 us |                                                                   
|  Day 19   |    16.504 us | 13272.444 us |    28.233 us | 13317.182 us |                                                                   
|  Day 20   |    16.599 us |    26.968 us |  1343.362 us |  1386.928 us |                                                                   
|  Day 21   |     5.458 us |     0.226 us |    79.750 us |    85.433 us |                                                                   
|  Day 22   |    12.154 us |  1047.457 us |  1051.753 us |  2111.364 us |                                                                   
+-----------+--------------+--------------+--------------+--------------+                                                                   
|  Summary  |   229.244 us | 14974.208 us | 10326.323 us | 25529.774 us |                                                                   
+-----------+--------------+--------------+--------------+--------------+ 
```

#### Apple M1 Pro

Note: multi-threaded times appear to be sequential(?!?!)

```
$ cmake -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -G Ninja
$ cmake --build build -j
$ OMP_NUM_THREADS=8 OMP_PLACES=cores OMP_PROC_BIND=true KMP_AFFINITY=compact ./build/advent --mode benchmark --ntimes 1000
+-----------+--------------+--------------+--------------+--------------+
| AoC++2021 |   Parsing    |    Part 1    |    Part 2    |    Total     |
+-----------+--------------+--------------+--------------+--------------+
|  Day 01   |    28.930 us |     0.500 us |     0.490 us |    29.920 us |
|  Day 02   |    22.470 us |     4.650 us |     8.090 us |    35.210 us |
|  Day 03   |    28.030 us |     5.760 us |    10.980 us |    44.770 us |
|  Day 04   |    33.510 us |    21.610 us |    70.390 us |   125.510 us |
|  Day 05   |    27.000 us |   151.560 us |   223.820 us |   402.380 us |
|  Day 06   |     8.540 us |     0.000 us |     0.010 us |     8.550 us |
|  Day 07   |    10.890 us |    38.750 us |    82.570 us |   132.210 us |
|  Day 08   |    29.380 us |     0.290 us |     7.170 us |    36.840 us |
|  Day 09   |     7.490 us |    24.950 us |    52.350 us |    84.790 us |
|  Day 10   |    13.100 us |    20.100 us |    10.760 us |    43.960 us |
|  Day 11   |     7.240 us |    13.320 us |    29.090 us |    49.650 us |
|  Day 12   |    11.380 us |     3.110 us |    37.400 us |    51.890 us |
|  Day 13   |    14.460 us |    10.060 us |    10.980 us |    35.500 us |
|  Day 14   |     7.810 us |     1.510 us |     4.790 us |    14.110 us |
|  Day 15   |     7.820 us |   145.690 us |  7024.510 us |  7178.020 us |
|  Day 16   |    35.740 us |     0.390 us |     0.480 us |    36.610 us |
|  Day 17   |     7.220 us |     0.000 us |   163.510 us |   170.730 us |
|  Day 18   |    18.380 us |   272.260 us |  1144.050 us |  1434.690 us |
|  Day 19   |    30.330 us | 16263.930 us |   288.640 us | 16582.900 us |
|  Day 20   |    36.030 us |   237.820 us |  7443.720 us |  7717.570 us |
|  Day 21   |    10.150 us |     0.280 us |    88.110 us |    98.540 us |
|  Day 22   |    23.520 us |  1213.460 us |  1217.590 us |  2454.570 us |
+-----------+--------------+--------------+--------------+--------------+
|  Summary  |   419.420 us | 18430.000 us | 17919.500 us | 36768.920 us |
+-----------+--------------+--------------+--------------+--------------+
```
