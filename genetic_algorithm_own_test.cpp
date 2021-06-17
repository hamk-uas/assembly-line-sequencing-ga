// c_optimize - Genetic algorithm optimizer library for the open loop, fixed starting point traveling salesman problem.
//
// Based on a Python version written in 2020 by Genrikh Ekkerman, Häme University of Applied Sciences.
// Written in 2020 by Olli Niemitalo, Häme University of Applied Sciences.
// 
// This work is licensed under the Creative Commons CC0 1.0 Universal License/Waiver:
// https://creativecommons.org/publicdomain/zero/1.0/
// To the extent possible under law, the authors and Häme University of Applied Sciences have waived all copyright and related or neighboring rights to this work.
// This work is distributed without any warranty.

// -*- compile-command: "g++ genetic_algorithm_own_test.cpp -std=c++17 -march=native -I. -O3 -ffast-math -fopenmp -o test" -*-
#include <stdio.h>
#include "genetic_algorithm_own.h"
#include "../data.h" // User data: distance matrixes in flat int array format, length numGenes*numGenes
#include <iostream>
#include <chrono>

// This is a program that will test the optimizer. Select what / how much you want to test:

const int resampleNumGenes = 200; // Number of genes
const int numGenerations = 10000; // Stop after this many generations

const bool runStatistics = false;         // Run statistics? Parameters:
const int numOptimizationSamples = 100;  // Number of optimization runs
const double generationMultiplier = 1.1; // From generation x go to generation generationMultiplier*x rounded up.
const bool trajectory = false;           // Print optimization trajectories?

const bool runSingle = true;           // Run a single optimization? Parameters:
const int numGenerationsPerStep = 100; // Number of generations per step

// Source data
const int numGenes = 211; // Number of genes. Please match with dimensions of distanceMatrix.
const int *distanceMatrix = distanceMatrix211; // Distance matrix to use. If you change this, change also numGenes.
  
// Used for statistics only.
// Randomly sample with replacement from the empirical distribution of N events, creating a list of M events.
// Creates a new M*M distance matrix for the new list of events from the given N*N distance matrix.
void sampleDistanceMatrix(int N, int M, const int *matrixNxN, int *newMatrixMxM, std::mt19937 &randomNumberGenerator) {
  int *shot = new int[M];
  std::uniform_int_distribution<int> uni(0, N - 1);
  for (int i = 0; i < M; i++) {
    shot[i] = uni(randomNumberGenerator);
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      newMatrixMxM[i*M + j] = matrixNxN[shot[i]*N + shot[j]];
    }
  }
  delete[] shot;
}

int main() {
  // Statistics
  if (runStatistics) {
    if (!trajectory) {
      printf("Optimization result when sampling from the empirical distribution of orders:\n");
    }
    auto start = std::chrono::steady_clock::now();
    unsigned seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 samplerRNG(0); // Mersenne Twister random number generator. Seed 0 to always get the same sample.
    const int M = resampleNumGenes;
    int newMatrix[M*M];
    int costSum = 0;
    Optimizer *optimizer = new Optimizer(M, newMatrix); // The optimizer has its own random number generator
    if (trajectory) {
      printf("0,");
      for (int generation = 1; generation < numGenerations;) {
	printf("%d,", generation);
	int nextGeneration = (int)ceil(generation * generationMultiplier);
	if (nextGeneration > numGenerations) {
	  nextGeneration = numGenerations;
	}
	generation = nextGeneration;
      }
      printf("%d\n", numGenerations);
    }
    for (int i = 0; i < numOptimizationSamples; i++) {  
      sampleDistanceMatrix(numGenes, M, distanceMatrix, newMatrix, samplerRNG);
      optimizer->initPopulation();
      if (trajectory) {
	printf("%d,", optimizer->costs[0]); // Random order cost
      }
      for (int generation = 1; generation < numGenerations;) {
	if (trajectory) {
	  printf("%d,", optimizer->bestCost);
	}
	int nextGeneration = (int)ceil(generation * generationMultiplier);
	if (nextGeneration > numGenerations) {
	  nextGeneration = numGenerations;
	}
	optimizer->optimize(nextGeneration - generation);
	generation = nextGeneration;
      }
      printf("%d\n", optimizer->bestCost);
      costSum += optimizer->bestCost;
    }
    auto end = std::chrono::steady_clock::now();
    if (!trajectory) {
      printf("Mean cost = %f\n", costSum/(double)numOptimizationSamples);
      printf("Running time: %f s\n", std::chrono::duration <double> (end - start).count());
    }
    delete optimizer;
  }

  // Single optimization run
  if (runSingle) {
    auto start = std::chrono::steady_clock::now();
    printf("Doing a single optimization run:\n");
    Optimizer *optimizer = new Optimizer(numGenes, distanceMatrix);
    
    printf("Best cost before optimization: %d\n", optimizer->bestCost);
    printf("generation,best_cost\n");
    int generation = 0;
    for (; generation < numGenerations; generation += numGenerationsPerStep) {
      printf("%d,%d\n", generation, optimizer->bestCost);
      optimizer->optimize(numGenerationsPerStep);
    }
    printf("%d,%d\n", generation, optimizer->bestCost);
    
    printf("Best cost after optimization: %d\n", optimizer->bestCost);
    printf("Best chromosome in population:\n");
    int *best = optimizer->best;
    for (int i = 0; i < numGenes; i++) {
      printf("%d,", best[i]);
    }
    printf("\n");
    auto end = std::chrono::steady_clock::now();
    printf("Running time: %f s\n", std::chrono::duration <double> (end - start).count());
    delete optimizer;
  }
}
