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
							   
void QAP::IterativeLocalSearchSA(int max_iters, int sublist_fraction, 
							     int SA_max_iters, int SA_max_neig, int SA_max_scs, float SA_T_fin, float SA_nu , float SA_phi){

	Solution best;
	
	Reinicialize();
	best = solution;

	for(int i=0; i<max_iters; i++){

		RandomSublistMutation(solution, sublist_fraction);
		SimulatedAnnealing(SA_max_iters, SA_max_neig, SA_max_scs, SA_T_fin, SA_nu, SA_phi, false);
		
		if(solution.numeric_solution < best.numeric_solution)
			best = solution;
		
		solution = best;

	}

}
