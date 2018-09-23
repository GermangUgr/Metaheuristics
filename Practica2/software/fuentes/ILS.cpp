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

void QAP::IterativeLocalSearch(int max_iters, int LS_max_calls, int sublist_fraction){

	Solution best;
	
	Reinicialize();
	best = solution;

	for(int i=0; i<max_iters; i++){

		RandomSublistMutation(solution, sublist_fraction);
		LocalSearch(LS_max_calls, false);

		if(solution.numeric_solution < best.numeric_solution)
			best = solution;
		

		solution = best;

	}

}
