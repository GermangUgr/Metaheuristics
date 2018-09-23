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

double QAP::LocalSearch(int max_calls, bool reini){

	vector<int> DLB(dimension, 0), exchanger(dimension);
	bool general_improvement = true, improvement_flag = false;
	int numeric_improvement = 0;
	double function_calls = 0.0;
	
	if(reini) Reinicialize();
	exchanger = solution.sol_permutation;

	while(general_improvement && function_calls < max_calls){

		general_improvement = false;
		ShuffleVector(exchanger);

		for(int i=0; i<DLB.size(); i++)
			DLB[i] = 0;

		for(int i=0; i<dimension && !general_improvement; i++){

			if(DLB[exchanger[i]] == 0){

				improvement_flag = false;
				numeric_improvement = 0;

				for(int j=0; j<dimension && !general_improvement; j++){

					numeric_improvement = CheckMove(exchanger[i],exchanger[j]);
					function_calls += 1.0/(dimension/4.0);

					if(numeric_improvement < 0){

						ApplyMove(exchanger[i],exchanger[j], numeric_improvement);
						DLB[exchanger[i]] = 0; DLB[exchanger[j]] = 0;
						improvement_flag = true;
						general_improvement = true;
						function_calls += 1.0/(dimension/4.0);

					}

					if(!improvement_flag) DLB[exchanger[i]] = 1;

				} //end for

			} // end if

		} //end for

	} // end while

	return function_calls;
}