# data_generation.py - Python interfacing and statistical tests on assembly line sequencing optimization.
#
# Written in 2021 by Genrikh Ekkerman, Häme University of Applied Sciences.
# 
# This work is licensed under the Creative Commons CC0 1.0 Universal License/Waiver:
# https://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the authors and Häme University of Applied Sciences have waived all copyright and related or neighboring rights to this work.
# This work is distributed without any warranty.

from numpy import random
import numpy as np
from matplotlib import pyplot as plt
from ctypes import *
import csv

function = CDLL(r'c_optimizer_x64.dll') # The traveling salesman optimizer library compiled to a dll

def generate_data(n_boms, n_stations, n_parts, factor):
	BOMs = [0]*n_boms
	for BOM in range(len(BOMs)):
		BOMs[BOM] = [0]*n_stations
		#print(BOMs[BOM])
		#print(type(BOMs[BOM]))
		for part in range(n_stations):
			BOMs[BOM][part] = int(random.zipf(factor, 1))
			while not BOMs[BOM][part] <= n_parts:
				BOMs[BOM][part] = int(random.zipf(factor, 1))
	return BOMs


def create_matrix(BOMs):
	#print(BOMs)
	distance_matrix = []
	distance = 0
	for i in BOMs:
		distance_row = []
		for l in BOMs:
			distance = 0
			for p in range(len(i)):
				if i[p] != l[p]:
					distance += 1
			distance_row.append(distance)
		distance_matrix.append(distance_row)

	return distance_matrix


def test1():
	configs = [[5, 5], [5, 10], [5, 20],
			 [10, 5], [10, 10], [10, 20],
			 [20, 5], [20, 10], [20, 20]]
	for config in configs:
		config_dict = {"Config" : config}
		config_dict
		print("Test for config: ", config)
		average_original = 0
		average_final = 0
		average_improvement = 0
		for i in range(10):
			BOMs = generate_data(100, config[0], config[1], 2)
			config_dict[i] = BOMs
			print("Generated BOMs on run:", i)
			matrix = create_matrix(BOMs)
			print("Created distacne matrix on run:", i)
			flat_matrix = [item for sublist in matrix for item in sublist]
			num_genes = len(matrix)
			input_matrix = (c_int * len(flat_matrix))(*flat_matrix)
			result_list = c_int * num_genes
			input_output = result_list()

			for i in range(num_genes):
				input_output[i] = i;

			original = function.calc_cost(num_genes, input_matrix, input_output)
			print("Initial cost of the boms", original)
			final = function.run_optimizer(num_genes, input_matrix, input_output)
			results = []

			for i in input_output:
				results.append(matrix[i])

			print("Optimized cost of the BOMs", final)
			print("Improvement", 100 - final / original * 100, "%\n")
			average_improvement += 100 - final / original * 100
			average_original += original
			average_final += final
		average_improvement /= 10
		average_original /= 10
		average_final /= 10
		dict_name = str(config)+"test1_"
		print("Test for concluded for config: ", config)
		print("Average original cost: ", average_original)
		print("Average final cost: ", average_final)
		print("Average improvement: ", average_improvement, "%\n")
		config_dict["Average original cost: " + dict_name + str(average_original)] = average_original
		config_dict["Average final cost: " + dict_name + str(average_final)] = average_final
		config_dict["Average improvement: " + dict_name + str(average_improvement)] = average_improvement

		with open('Config' + dict_name+'.csv', 'w') as f:
		    w = csv.DictWriter(f, config_dict.keys())
		    w.writeheader()
		    w.writerow(config_dict)
	return


def test2():
	configs = [20, 50, 100, 200]
	for config in configs:
		config_dict = {"Config" : config}
		config_dict
		print("Test for config: ", config)
		average_original = 0
		average_final = 0
		average_improvement = 0
		for i in range(10):
			BOMs = generate_data(config, 10, 10, 2)
			config_dict[i] = BOMs
			print("Generated BOMs on run:", i)
			matrix = create_matrix(BOMs)
			print("Created distacne matrix on run:", i)
			flat_matrix = [item for sublist in matrix for item in sublist]
			num_genes = len(matrix)
			input_matrix = (c_int * len(flat_matrix))(*flat_matrix)
			result_list = c_int * num_genes
			input_output = result_list()

			for i in range(num_genes):
				input_output[i] = i;

			original = function.calc_cost(num_genes, input_matrix, input_output)
			print("Initial cost of the boms", original)
			final = function.run_optimizer(num_genes, input_matrix, input_output)
			results = []

			for i in input_output:
				results.append(matrix[i])

			print("Optimized cost of the BOMs", final)
			print("Improvement", 100 - final / original * 100, "%\n")
			average_improvement += 100 - final / original * 100
			average_original += original
			average_final += final
		average_improvement /= 10
		average_original /= 10
		average_final /= 10
		dict_name = str(config) + "test2_"
		print("Test for concluded for config: ", config)
		print("Average original cost: ", average_original)
		print("Average final cost: ", average_final)
		print("Average improvement: ", average_improvement, "%\n")
		config_dict["Average original cost: " + dict_name + str(average_original)] = average_original
		config_dict["Average final cost: " + dict_name + str(average_final)] = average_final
		config_dict["Average improvement: " + dict_name + str(average_improvement)] = average_improvement

		with open('Config' + dict_name+'.csv', 'w') as f:
		    w = csv.DictWriter(f, config_dict.keys())
		    w.writeheader()
		    w.writerow(config_dict)
	return

test2()


test1()