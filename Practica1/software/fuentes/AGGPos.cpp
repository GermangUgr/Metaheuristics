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

void QAP::AGG_Position(float P_c, float P_m, int max_eval, int chomosomes){

	int num_cross = ceil((chomosomes) * P_c);
	int num_mut = ceil(chomosomes * dimension * P_m);
	int pairs_index = 0;
	int parent1, parent2, candidate1, candidate2;
	int increase_new_solutions;
	vector<Solution> new_solutions;
	vector<Solution>::iterator best_pos, worst_pos;
	vector<pair<int,int>> population_order;
	Solution new_gene, Sol_parent1, Sol_parent2, best_new_solution;
	double eval = 0.0;

	InitializePopulation(chomosomes);

	for(int i=0; i<population.size(); i++){
		population_order.push_back(pair<int,int>(i,population[i].numeric_solution));
	}

	InicializePairsVector(chomosomes);

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

		//Apply mutation operator
		ApplyMutation(new_solutions, num_mut);

		eval += num_cross + num_mut/(dimension/4.0);

		best_pos = min_element(new_solutions.begin(), new_solutions.end(), SolutionComparator);
		worst_pos = max_element(new_solutions.begin(), new_solutions.end(), SolutionComparator);

		if(*best_pos != population[population_order[0].first]){
			new_solutions.erase(worst_pos);
			new_solutions.push_back((population[population_order[0].first]));
		}

		increase_new_solutions = chomosomes - new_solutions.size();
		for(int i=1; i<increase_new_solutions+1; i++)

			new_solutions.push_back(population[population_order[i].first]);

		

		population_order.clear();

		for(int i=0; i<new_solutions.size(); i++)

			population_order.push_back(pair<int,int>(i,new_solutions[i].numeric_solution));


		sort(population_order.begin(), population_order.end(), SolutionComparatorByPointer);

		population = new_solutions;

	}

	solution = population[population_order[0].first];
	
}