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

Solution& Solution::operator =(const Solution &s){

	sol_permutation.resize(s.sol_permutation.size());

	for(int i=0; i<sol_permutation.size(); i++){

		sol_permutation[i] = s.sol_permutation[i];
	}

	numeric_solution = s.numeric_solution;

}

bool Solution::operator ==(const Solution &s){

	bool equals = true;

	if(sol_permutation.size() != s.sol_permutation.size()){

		equals = false;

	} else {

		for(int i=0; i<sol_permutation.size(); i++)
			if(sol_permutation[i] != s.sol_permutation[i])
				equals = false;

	}

	return equals;

}


bool Solution::operator !=(const Solution &s){

	bool non_equals = false;

	if(sol_permutation.size() != s.sol_permutation.size()){

		non_equals = true;

	} else {

		for(int i=0; i<sol_permutation.size(); i++)
			if(sol_permutation[i] != s.sol_permutation[i])
				non_equals = true;

	}

	return non_equals;

}

QAP::QAP(char* filename, int seed){

	int dim = 0, data = 0;
	ifstream f;
	int aux;
	Seed = seed;

	f.open(filename);

	assert(f.is_open());

	f >> dim;
	dimension = dim;

	flux_matrix = new int*[dimension];
	distance_matrix = new int*[dimension];

	for(int i=0; i<dimension; i++){

		flux_matrix[i] = new int[dimension];
		distance_matrix[i] = new int[dimension];
	}

	f.ignore(1,'\n');

	for(int i=0; i<dimension && !f.eof(); i++){

		for(int j=0; j<dimension; j++){

			f >> data;
			flux_matrix[i][j] = data;
		}
	}

	f.ignore(1,'\n');

	for(int i=0; i<dimension && !f.eof(); i++){

		for(int j=0; j<dimension; j++){

			f >> data;
			distance_matrix[i][j] = data;
		}
	}

	solution.sol_permutation.resize(dimension);
	solution.numeric_solution = 0;

	f.close();

}

QAP::~QAP(){

	for(int i=0; i<dimension; i++){

			delete[] flux_matrix[i];
			delete[] distance_matrix[i];
			
	}

	delete[] flux_matrix;
	delete[] distance_matrix;
}

Solution QAP::PositionCrossingOperator(Solution &s1, Solution &s2){

	Solution new_solution;
	vector<int> non_equals;
	int non_equals_ind = 0;

	new_solution.sol_permutation.resize(dimension);

	for(int i=0; i<dimension; i++){

		if(s1.sol_permutation[i] == s2.sol_permutation[i]){

			new_solution.sol_permutation[i] = s2.sol_permutation[i];

		} else{

			non_equals.push_back(s1.sol_permutation[i]);
			new_solution.sol_permutation[i] = -1;

		}
	}

	ShuffleVector(non_equals);

	for(int i=0; i<new_solution.sol_permutation.size(); i++)

		if(new_solution.sol_permutation[i] == -1){

			new_solution.sol_permutation[i] = non_equals[non_equals_ind];
			non_equals_ind++;

		}


	CalculateNumericSolution(new_solution);

	return new_solution;

}

Solution QAP::OXCrossingOperator(Solution &s1, Solution &s2){

	int segmento = ceil(dimension*0.45);
	vector<pair<int,int>> v;
	int inicio = floor(dimension/2) - floor(segmento/2);
	int fin = inicio + segmento, v_counter = 0;
	Solution hijo;

	//cout << "\nInicio: " << inicio << " Fin: " << fin << endl;

	hijo.sol_permutation.resize(dimension);

	for(int i=0; i<dimension; i++){

		if(i >= inicio && i < fin)
			hijo.sol_permutation[i] = s1.sol_permutation[i];
		else
			v.push_back(pair<int,int>(s1.sol_permutation[i],-1));

	}

	for(int i=0; i<dimension; i++){

		for(int j=0; j<v.size(); j++)

			if(v[j].first == s2.sol_permutation[i])

				v[j].second = i;
	}

	sort(v.begin(), v.end(), OXComparator);

	for(int i=0; i<inicio; i++){

		hijo.sol_permutation[i] = v[v_counter].first;
		v_counter++;

	}

	for(int i=fin; i<dimension; i++){

		hijo.sol_permutation[i] = v[v_counter].first;
		v_counter++;

	}

	CalculateNumericSolution(hijo);

	return hijo;

}

void QAP::ApplyMutation(vector<Solution> &p, int num_mut){

	int member, gene1, gene2, improvement;

	for(int i=0; i<num_mut; i++){

		member = Randint(0,p.size()-1);
		gene1 = Randint(0,dimension-1);

		do{

			gene2 = Randint(0,dimension-1);

		} while (gene2 == gene1);

		improvement = CheckMove(gene1, gene2, p[member]);
		ApplyMove(gene1, gene2, improvement, p[member]);

	}

}

void QAP::CalculateNumericSolution(){

	solution.numeric_solution = 0;

	for(int i=0; i<dimension; i++){

		for(int j=0; j<dimension; j++){

			solution.numeric_solution += flux_matrix[i][j] * 
								    distance_matrix[solution.sol_permutation[i]][solution.sol_permutation[j]];
		}
	}

}


void QAP::CalculateNumericSolution(Solution &sol){

	sol.numeric_solution = 0;

	for(int i=0; i<dimension; i++){

		for(int j=0; j<dimension; j++){

			sol.numeric_solution += flux_matrix[i][j] * 
								    distance_matrix[sol.sol_permutation[i]][sol.sol_permutation[j]];
		}
	}
}

int QAP::CheckMove(int s, int r){

	int improvement = 0, ir, ik, is;

	for(int k=0; k<dimension; k++){

		if(k != s && k != r){

			ir = solution.sol_permutation[r];
			ik = solution.sol_permutation[k];
			is = solution.sol_permutation[s];

			improvement += flux_matrix[r][k] * (distance_matrix[is][ik] - distance_matrix[ir][ik])+
						   flux_matrix[s][k] * (distance_matrix[ir][ik] - distance_matrix[is][ik])+
						   flux_matrix[k][r] * (distance_matrix[ik][is] - distance_matrix[ik][ir])+
						   flux_matrix[k][s] * (distance_matrix[ik][ir] - distance_matrix[ik][is]);
		}
	}

	return improvement;

}

int QAP::CheckMove(int s, int r, Solution &sol){

	int improvement = 0, ir, ik, is;

	for(int k=0; k<dimension; k++){

		if(k != s && k != r){

			ir = sol.sol_permutation[r];
			ik = sol.sol_permutation[k];
			is = sol.sol_permutation[s];

			improvement += flux_matrix[r][k] * (distance_matrix[is][ik] - distance_matrix[ir][ik])+
						   flux_matrix[s][k] * (distance_matrix[ir][ik] - distance_matrix[is][ik])+
						   flux_matrix[k][r] * (distance_matrix[ik][is] - distance_matrix[ik][ir])+
						   flux_matrix[k][s] * (distance_matrix[ik][ir] - distance_matrix[ik][is]);
		}
	}

	return improvement;

}

void QAP::ApplyMove(int s, int r, int improvement){

	int aux = solution.sol_permutation[s];

	solution.sol_permutation[s] = solution.sol_permutation[r];
	solution.sol_permutation[r] = aux;

	solution.numeric_solution += improvement;
}

void QAP::ApplyMove(int s, int r, int improvement, Solution &sol){

	int aux = sol.sol_permutation[s];

	sol.sol_permutation[s] = sol.sol_permutation[r];
	sol.sol_permutation[r] = aux;

	sol.numeric_solution += improvement;
}

void QAP::Reinicialize(){

	int rand1, aux;

	for(int i=0; i<dimension; i++)
		solution.sol_permutation[i] = i;

	for(int i=0; i<dimension; i++){

		rand1 = Randint(i,dimension-1);

		aux = solution.sol_permutation[i];
		solution.sol_permutation[i] = solution.sol_permutation[rand1];
		solution.sol_permutation[rand1] = aux;

	}

	CalculateNumericSolution();

}

void QAP::InicializePairsVector(int size){

	pairs_vector.clear();
	pairs_vector.resize((size*(size-1))/2);

	for(int i=0; i<size; i++)

		for(int j=i; j<size; j++)

			pairs_vector[i] = pair<int,int>(i,j);

}

void QAP::ShufflePairsVector(){

	int rand1;
	pair<int,int> aux;

	for(int i=0; i<pairs_vector.size(); i++){

		rand1 = Randint(i, pairs_vector.size()-1);

		aux = pairs_vector[i];
		pairs_vector[i] = pairs_vector[rand1];
		pairs_vector[rand1] = aux;
	}
}

void QAP::ShuffleVector(vector<int> &vec){

	int rand1, aux;

	for(int i=0; i<vec.size(); i++){

		rand1 = Randint(i, vec.size()-1);

		aux = vec[i];
		vec[i] = vec[rand1];
		vec[rand1] = aux;

	}

}

void QAP::InitializePopulation(int total){

	Solution random_solution;
	vector<int> random_sol_permutation(dimension);
	population.clear();

	for(int i=0; i<total; i++){

		for(int j=0; j<dimension; j++)
			random_sol_permutation[j] = j;

		ShuffleVector(random_sol_permutation);
		random_solution.sol_permutation = random_sol_permutation;
		CalculateNumericSolution(random_solution);

		population.push_back(random_solution);

	}

	//sort(population.begin(), population.end(), SolutionComparator);

}

//Getters

vector<int> QAP::GetSolPermutation(){

	return solution.sol_permutation;
}

int QAP::GetSolution(){

	return solution.numeric_solution;
}

int QAP::GetDimension(){

	return dimension;
}

Solution QAP::GetMember(int index){

	return population[index];
}

int QAP::GetSeed(){

	return Seed;
}

//Setters

void QAP::SetSeed(int s){

	Seed = s;
}

//Functors

bool SolutionComparator(const Solution &s1, const Solution &s2){

	return (s1.numeric_solution < s2.numeric_solution); //Ordena de menor a mayor
}

bool SolutionComparatorByPointer(const pair<int,int> &i, const pair<int,int>  &j){

	return (i.second < j.second);

}

bool OXComparator(const pair<int,int> &i, const pair<int,int>  &j){

	return (i.second < j.second);
}