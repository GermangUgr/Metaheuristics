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

void QAP::AM_Sub(float P_c, float P_m, int max_eval, int chomosomes){

	int num_cross = ceil((chomosomes) * P_c);
	int num_mut = ceil(chomosomes * dimension * P_m);
	int pairs_index = 0, random_vector_counter = 0;
	int parent1, parent2, candidate1, candidate2;
	int increase_new_solutions;
	vector<Solution> new_solutions;
	vector<Solution>::iterator best_pos, worst_pos;
	vector<pair<int,int>> population_order;
	vector<int> random_vector(chomosomes);
	Solution new_gene, Sol_parent1, Sol_parent2, best_new_solution;
	int generational_counter = 0, FREC_LS = 10;
	double eval = 0.0, eval_LS;

	InitializePopulation(chomosomes);

	for(int i=0; i<population.size(); i++){
		population_order.push_back(pair<int,int>(i,population[i].numeric_solution));
	}

	for(int i=0; i<chomosomes; i++)
		random_vector[i] = i;

	InicializePairsVector(chomosomes);
	ShuffleVector(random_vector);

	sort(population_order.begin(), population_order.end(), SolutionComparatorByPointer);

	while(eval < max_eval){

		new_solutions.clear();
		eval_LS = 0;
		
		if(generational_counter >= FREC_LS){

			generational_counter = 0;

			for(int i=0; i<ceil(population.size()*0.1); i++){

				eval_LS += LocalSearch1(400, population[random_vector[random_vector_counter]]);

				random_vector_counter++;

				if(random_vector_counter >= random_vector.size() - 1){

					ShuffleVector(random_vector);
					random_vector_counter = 0;

				}
			}
		}

		population_order.clear();

		for(int i=0; i<population.size(); i++)

			population_order.push_back(pair<int,int>(i,population[i].numeric_solution));

		sort(population_order.begin(), population_order.end(), SolutionComparatorByPointer);

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

		eval += (double)(num_cross + num_mut/(dimension/4.0) + eval_LS);

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

		generational_counter++;

	}

	solution = population[population_order[0].first];
	
}