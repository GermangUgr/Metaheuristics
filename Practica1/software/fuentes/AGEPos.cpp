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

void QAP::AGE_Position(float P_c, float P_m, int max_eval, int chomosomes){

	int num_cross = 2, num_mut = 2;
	int mut_frec = ceil((1/P_m)/dimension), mut_counter = 0;
	int pairs_index = 0, size;
	int parent1, parent2, candidate1, candidate2;
	vector<Solution> new_solutions;
	vector<pair<int,int>> population_order;
	Solution new_gene, Sol_parent1, Sol_parent2, best_new_solution;
	double eval = 0.0;

	InitializePopulation(chomosomes);

	for(int i=0; i<population.size(); i++){
		population_order.push_back(pair<int,int>(i,population[i].numeric_solution));
	}

	InicializePairsVector(chomosomes);

	size = population.size();

	sort(population_order.begin(), population_order.end(), SolutionComparatorByPointer);

	while(eval < max_eval){

		new_solutions.clear();

		//Generate new members
		for(int i=0; i<num_cross; i++){

			pairs_index = Randint(0, pairs_vector.size()-1);
			candidate1 = pairs_vector[pairs_index].first;
			candidate2 = pairs_vector[pairs_index].second;

			parent1 = candidate1 < candidate2? candidate1:candidate2;

			pairs_index = Randint(0, pairs_vector.size()-1);
			candidate1 = pairs_vector[pairs_index].first;
			candidate2 = pairs_vector[pairs_index].second;

			parent2 = candidate1 < candidate2? candidate1:candidate2;

			Sol_parent1 = population[population_order[parent1].first];
			Sol_parent2 = population[population_order[parent2].first];

			new_gene = PositionCrossingOperator(Sol_parent1, Sol_parent2);

			new_solutions.push_back(new_gene);

		}

		mut_counter += num_cross;

		if(mut_counter >= mut_frec){
			ApplyMutation(new_solutions, num_mut);
			mut_counter = 0;

		}

		eval += num_cross + num_mut/(dimension/4.0);

		new_solutions.push_back(population[population_order[size-1].first]);
		new_solutions.push_back(population[population_order[size-2].first]);

		sort(new_solutions.begin(), new_solutions.end(), SolutionComparator);

		population[population_order[size-2].first] = new_solutions[0];
		population[population_order[size-1].first] = new_solutions[1];	

		population_order.clear();

		for(int i=0; i<population.size(); i++)

			population_order.push_back(pair<int,int>(i,population[i].numeric_solution));


		sort(population_order.begin(), population_order.end(), SolutionComparatorByPointer);

	}

	solution = population[population_order[0].first];
	
}