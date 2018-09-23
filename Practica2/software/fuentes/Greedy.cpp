#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <math.h>
#include "QAP.h"

using namespace std;

const int INFINITE = numeric_limits<int>::max();

void QAP::GreedySolver(){

	vector<int> flux_sum;
	vector<int> distance_sum;
	int f_sum, d_sum, max_f_index, min_d_index, max_f_value, min_d_value;

	Reinicialize();

	//Calcular la suma de distancias y flujos para cada modulo (fila)
	for(int i=0; i<dimension; i++){

		f_sum = 0; d_sum = 0;

		for(int j=0; j<dimension; j++){

			f_sum += flux_matrix[i][j];
			d_sum += distance_matrix[i][j];

		}

		flux_sum.push_back(f_sum);
		distance_sum.push_back(d_sum);
	}

	/*
	1º-Buscar el módulo que maximice el flujo
	2º-Buscar el area que mas centrica (que minice la distancia)
	3º-Asignar el módulo al área
	4º-Marcar módulo y área como procesados.
	*/

	for(int s=0; s<dimension; s++){

		min_d_index = 0; max_f_index = 0;
		max_f_value = -1; min_d_value = INFINITE;

		for(int i=0; i<dimension; i++){

			if(flux_sum[i] > max_f_value){

				max_f_index = i;
				max_f_value = flux_sum[i];
			}

			if(distance_sum[i] < min_d_value){

				min_d_index = i;
				min_d_value = distance_sum[i];
			}
		}

		solution.sol_permutation[max_f_index] =  min_d_index;

		distance_sum[min_d_index] = INFINITE;
		flux_sum[max_f_index] = -1;
	}

	CalculateNumericSolution();

}