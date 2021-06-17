// c_optimize - Genetic algorithm optimizer library for the open loop, fixed starting point traveling salesman problem.
//
// Based on a Python version written in 2020 by Genrikh Ekkerman, Häme University of Applied Sciences.
// Written in 2020 by Olli Niemitalo, Häme University of Applied Sciences.
// 
// This work is licensed under the Creative Commons CC0 1.0 Universal License/Waiver:
// https://creativecommons.org/publicdomain/zero/1.0/
// To the extent possible under law, the authors and Häme University of Applied Sciences have waived all copyright and related or neighboring rights to this work.
// This work is distributed without any warranty.

#pragma once

extern "C" __declspec(dllexport) int run_optimizer(int numGenes, const int *distanceMatrix, int *optimized);
extern "C" __declspec(dllexport) int calc_cost(int numGenes, const int* distanceMatrix, const int* chromosome);
