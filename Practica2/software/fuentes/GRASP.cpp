#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <math.h>
#include "QAP.h"
#include "GeneradorNumerosPseudoaleatorios.h"

using namespace std;

const int INFINITE = numeric_limits<int>::max();
const int MINFINITE = numeric_limits<int>::min();

					 //Parámetros de entrada                                  //Parámetros de salida
void QAP::CostsLists(vector<int> &Units, vector<int> &Locations, float alpha, PairList &BestUnits, PairList &BestLocations){


	int unit_max = MINFINITE, unit_min = INFINITE;
	int loc_max = MINFINITE, loc_min = INFINITE;
	double mu_units, mu_locs;

	for(int i=0; i<dimension; i++){

		if(Units[i] > unit_max && Units[i] != INFINITE) unit_max = Units[i];
		if(Units[i] < unit_min && Units[i] != MINFINITE) unit_min = Units[i];

		if(Locations[i] > loc_max && Locations[i] != INFINITE) loc_max = Locations[i];
		if(Locations[i] < loc_min && Locations[i] != MINFINITE) loc_min = Locations[i];

	}

	mu_units = unit_max - alpha * (unit_max - unit_min);
	mu_locs = loc_min + alpha * (loc_max - loc_min);

	BestUnits.clear(); BestLocations.clear();

	for(int i=0; i<dimension; i++){


		if(Units[i] >= mu_units && Units[i] != MINFINITE)
			BestUnits.push_back(pair<int,int>(i, Units[i]));

		if(Locations[i] <= mu_locs && Locations[i] != INFINITE)
			BestLocations.push_back(pair<int,int>(i, Locations[i]));


	}

}

void QAP::CalculateRandGreedy(float alpha){

	vector<int> Units_sum, Locs_sum, assignements, assig_values, candidates;
	PairList BestLocs, BestUnits, feasible_assig(0);
	pair<int,int> rand_pair1, rand_pair2;
	int rand1, rand2, f_sum, d_sum, unit, location, max, min;
	double mu;


	//Calcular la suma de distancias y flujos para cada modulo (fila)
	for(int i=0; i<dimension; i++){

		f_sum = 0; d_sum = 0;

		for(int j=0; j<dimension; j++){

			f_sum += flux_matrix[i][j];
			d_sum += distance_matrix[i][j];

		}

		Units_sum.push_back(f_sum);
		Locs_sum.push_back(d_sum);
	}

	//Build feassible assignement vector
	for(int i=0; i<dimension; i++)
		for(int j=0; j<dimension; j++)
			feasible_assig.push_back(pair<int,int>(i,j)); //first = unidades, second = localizaciones 

	for(int i=0; i<dimension; i++)
			solution.sol_permutation[i] = 0;


	assig_values.resize(feasible_assig.size());

	/////////////////////// Paso 1 ///////////////////////

	CostsLists(Units_sum, Locs_sum, alpha, BestUnits, BestLocs);

	rand_pair1 = DiffRands(0, BestUnits.size()-1, Seed);
	rand_pair2 = DiffRands(0, BestLocs.size()-1, Seed);

	solution.sol_permutation[BestUnits[rand_pair1.first].first] = BestLocs[rand_pair2.first].first;
	solution.sol_permutation[BestUnits[rand_pair1.second].first] = BestLocs[rand_pair2.second].first;

	for(int i=0; i<feasible_assig.size(); i++){

		if(feasible_assig[i].first == BestUnits[rand_pair1.first].first || 
		   feasible_assig[i].second == BestLocs[rand_pair2.first].first ||
		   feasible_assig[i].first == BestUnits[rand_pair1.second].first || 
		   feasible_assig[i].second == BestLocs[rand_pair2.second].first){

			feasible_assig[i].first = -1;
			feasible_assig[i].second = -1;

		}

		assig_values[i] = INFINITE;

	}

	assignements.push_back(BestUnits[rand_pair1.first].first);
	assignements.push_back(BestUnits[rand_pair1.second].first);

	/////////////////////// Paso 2 ///////////////////////

	for(int k=0; k<dimension-2; k++){

		max = MINFINITE;
		min = INFINITE;
		candidates.clear();

		for(int j=0; j<feasible_assig.size(); j++){

			if(feasible_assig[j].first != -1 && feasible_assig[j].second != -1){

				assig_values[j] = CheckAdd(feasible_assig[j].first, feasible_assig[j].second, assignements);

				if(assig_values[j] < min)
					min = assig_values[j];

				if(assig_values[j] > max)
					max = assig_values[j];

			}

		}

		mu = (double) min + alpha * ((double) max - (double) min);

		for(int j=0; j<assig_values.size(); j++){

			if((double) assig_values[j] <= mu)
				candidates.push_back(j);

		}

		rand1 = Randint(0, candidates.size()-1);

		unit = feasible_assig[candidates[rand1]].first;
		location = feasible_assig[candidates[rand1]].second;

		solution.sol_permutation[unit] = location;

		assignements.push_back(unit);

		for(int j=0; j<feasible_assig.size(); j++){

			if(feasible_assig[j].first == unit || feasible_assig[j].second == location){

				feasible_assig[j].first = -1;
				feasible_assig[j].second = -1;

			}

			assig_values[j] = INFINITE;

		}
		
	}

	CalculateNumericSolution();

}

void QAP::GRASP(int max_iters, int max_iters_ls, float alpha){

	Solution best_solution;

	best_solution.numeric_solution = INFINITE;

	for(int i=0; i<max_iters; i++){

		CalculateRandGreedy(alpha);
		LocalSearch(max_iters_ls, false);

		if(solution.numeric_solution < best_solution.numeric_solution)
			best_solution = solution;

	}

	solution = best_solution;

}