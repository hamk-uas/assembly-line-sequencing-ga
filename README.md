# assembly-line-sequencing-ga
Genetic algorithm optimizer library for the open loop, fixed starting point traveling salesman problem. Written in C++ and can be compiled to a DLL to be used in Python.

# Authors
Based on a Python version written in 2020 by Genrikh Ekkerman, Häme University of Applied Sciences.
C++ version written in 2020 by Olli Niemitalo, Häme University of Applied Sciences.
 
# License
This work is licensed under the Creative Commons CC0 1.0 Universal License/Waiver: https://creativecommons.org/publicdomain/zero/1.0/
To the extent possible under law, the authors and Häme University of Applied Sciences have waived all copyright and related or neighboring rights to this work.
This work is distributed without any warranty.

# Files

* `genetic_algorithm_own.h` – C++ header-only optimizer library, contains the genetic algorithm implementation
* `genetic_algorithm_own_test.cpp` – A C++ program for testing the optimizer
* `optimizer.cpp` – C++ source code for the C calling convention DLL wrapper for the optimizer
* `optimizer.h` – C header file for the DLL wrapper
* `data_generation.py` – Python interfacing example with assembly line sequencing test runs

# Compilation

The DLL can be compiled using Visual Studio. Tests can be compiled using GNU C++ compiler (g++).

## Visual Studio
To compile for use in Python, create a DLL project in Visual Studio and add existing items:

* optimize.cpp
* optimize.h
* genetic_algorithm_own.h

Build... Configuration manager... choose the appropriate configuration for your computer:

* Active solution platform: `x64`
* Compile for release. Use C/C++ options: `/openmp /fp:except- /Qpar /Ob2`
* Use C++ Language Standard option `Default` or at least: `/std:c++17`
* Preferably use an appropriate Enable Enhanced Instruction Set option for your computer: `/arch:SSE2`

## g++
To compile for testing:

`g++ genetic_algorithm_own_test.cpp -std=c++17 -march=native -I. -O3 -ffast-math -fopenmp -o test`

Note that you need to provide your own distance matrix data file.

To compile and build as DLL:

```
g++ -c optimize.cpp -std=c++17 -march=native -I. -O3 -ffast-math -fopenmp -o optimize.o
g++ -shared -o c_optimizer_x64.dll -static-libstdc++ -fopenmp optimize.o
```

 If this does not work, try Visual Studio.

## Python

Once you have a 64-bit DLL built as `c_optimizer_x64.dll`, you can run a test suite of assembly line sequencing optimization runs:

`python data_generation.py`
