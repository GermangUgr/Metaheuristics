#include <iostream>
#include "QAP.h"
#include <vector>


using namespace std;

int main (int argc, char **argv){

	if(argc != 3){
	
		cerr << "Uso: <main> <fichero_datos> <semilla>" << endl;
		return -1;

	}


	//INICIALIZACION//

	char *nombre = argv[1];
	int semilla = atoi(argv[2]);
	vector<int> v_solution;
	int weight_solution, dimension;

	QAP qap(nombre, semilla);

	dimension = qap.GetDimension();
	
	qap.GRASP(25, 50000, 0.3);
	// qap.CalculateRandGreedy(0.3);

	v_solution = qap.GetSolPermutation();
	weight_solution = qap.GetSolution();

	cout << "Valor de la solucion GRASP: " << weight_solution << endl;
	cout << "Permutación solucion:" << endl;

	for(int i=0; i<dimension; i++){
		cout << v_solution[i] << " ";
	}
	
	cout << endl;

	return 0;

}