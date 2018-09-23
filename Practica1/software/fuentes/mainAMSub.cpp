#include <iostream>
#include "QAP.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <assert.h>
#include <fstream>


using namespace std;

int main (int argc, char **argv){

	if(argc != 7){
	
		cerr << "Uso: <main> <fichero_datos> <semilla> <P_c> <P_m> <Max_eval> <Tam_poblacion>" << endl;
		return -1;

	}


	//INICIALIZACION//

	char *nombre = argv[1];
	int semilla = atoi(argv[2]), Max_eval = atoi(argv[5]), Tam_poblacion = atoi(argv[6]);
	double P_c = atof(argv[3]), P_m = atof(argv[4]);
	vector<int> v_solution;
	int weight_solution, dot_position, opt;
	string sol_file(nombre), file(nombre);
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> d1;

	dot_position = sol_file.find(".");
	sol_file = sol_file.substr(0,dot_position);
	sol_file = sol_file + ".sln";

	ifstream f;
	f.open(sol_file);
	assert(f.is_open());

	f >> opt; f >> opt;

	QAP qap(nombre, semilla);

	//cout << "\nNOMBRE DEL ARCHIVO: " << file << " // DIMENSION: " << qap.GetDimension() << " // OPTIMO: " << opt << endl;

	t_antes=std::chrono::high_resolution_clock::now();

	qap.AM_Sub(P_c, P_m, Max_eval, Tam_poblacion);

	t_despues=std::chrono::high_resolution_clock::now();

	d1 = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));

	v_solution = qap.GetSolPermutation();
	weight_solution = qap.GetSolution();

	/*cout << "\nValor para la solucion AGE_Position: " << weight_solution << " Tiempo empleado: " << d1.count() << endl;
	cout << "\nPermutación solucion:" << endl;

	for(int i=0; i<v_solution.size(); i++){
		cout << v_solution[i] << " ";
	}

	cout << endl << endl;
	cout << "Fin de ejecucion" << endl;
	cout << endl;*/

	return 0;

}