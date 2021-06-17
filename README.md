# assembly-line-sequencing-ga
Genetic algorithm optimizer library for the open loop, fixed starting point traveling salesman problem.

# Authors
Based on a Python version written in 2020 by Genrikh Ekkerman, Häme University of Applied Sciences.
C++ version written in 2020 by Olli Niemitalo, Häme University of Applied Sciences.
 
# License
This work is licensed under the Creative Commons CC0 1.0 Universal License/Waiver: https://creativecommons.org/publicdomain/zero/1.0/
To the extent possible under law, the authors and Häme University of Applied Sciences have waived all copyright and related or neighboring rights to this work.
This work is distributed without any warranty.

# Compilation
## Visual Studio
To compile for use in Python, create a DLL project in Visual Studio and add existing items:

* optimize.cpp
* optimize.h
* genetic_algorithm_own.h

Build... Configuration manager... choose the appropriate configuration for your computer:

* Active solution platform: x64
* Compile for release.
* Use C/C++ options: `/openmp /fp:except- /Qpar /Ob2`
* Use C++ Language Standard option `Default` or at least: `/std:c++17`
* Preferably use an appropriate Enable Enhanced Instruction Set option for your computer: `/arch:SSE2`

## G++
To compile for testing:

`g++ genetic_algorithm_own_test.cpp -std=c++17 -march=native -I. -O3 -ffast-math -fopenmp -o test`
