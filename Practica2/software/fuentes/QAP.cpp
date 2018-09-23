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

void QAP::RandomSublistMutation(Solution &sol, int sublist_fraction){

	int sublist_size = ceil(dimension/sublist_fraction);
	vector<int> sublist(sublist_size);
	int start = Randint(0, sol.sol_permutation.size()-1);

	for(int i=0; i<sublist_size; i++){

		sublist[i] = sol.sol_permutation[(i+start)%dimension];

	}

	ShuffleVector(sublist);

	for(int i=0; i<sublist_size; i++){

		sol.sol_permutation[(i+start)%dimension] = sublist[i];

	}	

	CalculateNumericSolution(sol);

}

void QAP::CalculateNumericSolution(){

	// cout << "Calculando solucion numerica" << endl;
	
	/*for(int i=0; i<dimension; i++)
		cout << solution.sol_permutation[i] << " ";*/

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

int QAP::CheckAdd(int unit, int loc, vector<int> &assig){

	int improvement = 0;

	for(int i=0; i<assig.size(); i++){

		improvement += flux_matrix[assig[i]][unit] * 
							    distance_matrix[solution.sol_permutation[assig[i]]][loc];

		improvement += flux_matrix[unit][assig[i]] *
								distance_matrix[loc][solution.sol_permutation[assig[i]]];
		
	}

	return improvement;
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

void QAP::ShuffleVector(vector<int> &vec){

	int rand1, aux;

	for(int i=0; i<vec.size(); i++){

		rand1 = Randint(i, vec.size()-1);

		aux = vec[i];
		vec[i] = vec[rand1];
		vec[rand1] = aux;

	}

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

pair<int,int> DiffRands(int l, int h, int Seed){

	pair<int,int> DRand;

	if(h - l > 0){

		DRand.first = Randint(l, h);

		do{

			DRand.second = Randint(l, h);

		} while(DRand.first == DRand.second);

	} else {

		DRand.first = DRand.second = -1;

	}

	return DRand;

}