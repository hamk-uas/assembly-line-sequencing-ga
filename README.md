# assembly-line-sequencing-ga
Genetic algorithm for assembly line sequencing

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
