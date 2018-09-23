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

//Precond.: max_iters != 0 && max_neig != 0 $$ T_fin != 0 $$ nu != 0
void QAP::SimulatedAnnealing(int max_iters, int max_neig, int max_scs, float T_fin, float nu , float phi, bool reini){

	vector<int> exchanger(dimension);
	int n_improvement = 0, K = 1, successes = 1, generated = 0;
	int M = ceil(max_iters/max_neig);
	double function_calls = 0.0;
	float T, beta;
	Solution best;
	
	if(reini) Reinicialize();

	exchanger = solution.sol_permutation;
	best.numeric_solution = INFINITE;

	T = (nu * solution.numeric_solution)/(-log(phi));
	beta = (T - T_fin)/(M * T * T_fin);

	while(T > T_fin && successes > 0 && K <= M){

		ShuffleVector(exchanger);
		successes = 0;
		generated = 0;

		for(int i=0; i<dimension && generated < max_neig && successes < max_scs; i++){

			for(int j=i+1; j<dimension && generated < max_neig && successes < max_scs; j++){

				n_improvement = CheckMove(exchanger[i],exchanger[j]);
				function_calls += 1.0/(dimension/4.0);
				generated++;

				if(n_improvement < 0 || (Rand() <= exp(-n_improvement/(T)))){

					ApplyMove(exchanger[i],exchanger[j], n_improvement);
					successes++;

					if(solution.numeric_solution < best.numeric_solution){
						best = solution;
					}

				}

			} //end for

		} //end for

		T = T / (1 + beta*T);
		K++;

	} // end while

	solution = best;
}
