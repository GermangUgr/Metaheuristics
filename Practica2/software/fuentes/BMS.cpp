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

void QAP::BasicMultibootSearch(int max_iters, int LS_max_calls){

	Solution best;

	Reinicialize();
	best = solution;

	for(int i=0; i<max_iters; i++){

		LocalSearch(LS_max_calls);

		if(solution.numeric_solution < best.numeric_solution)
			best = solution;

	}	

	solution = best;

}

