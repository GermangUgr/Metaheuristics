#include <iostream>
#include "QAP.h"
#include <vector>
#include <chrono>
#include <string>
#include <assert.h>
#include <fstream>
#include <math.h>


using namespace std;

int main (int argc, char **argv){

	if(argc != 2){
	
		cerr << "Uso: <main> <fichero_datos>" << endl;
		return -1;

	}


	//INICIALIZACION//

	char *nombre = argv[1];
	int dot_position;
	vector<int> v_solution, seeds(5), solutions;
	int weight_solution, dimension, opt;
	double desv;
	string sol_file(nombre), file(nombre);

	//Rellenamos el vector de semillas con 5 números primos
	seeds[0] = 5; seeds[1] = 17; seeds[2] = 281; seeds[3] = 881; seeds[4] = 6673;

	//Declaramos las estructuras necesarias para medir el tiempo de ejecucion
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> d1, d_acumulado;

	//Obtenemos el optimo almacenado en el archivo .sln correspondiente al .dat pasado como argumento
	dot_position = sol_file.find(".");
	sol_file = sol_file.substr(0,dot_position);
	sol_file = sol_file + ".sln";

	ifstream f;
	f.open(sol_file);
	assert(f.is_open());

	f >> opt; f >> opt;

	QAP qap(nombre, 3);

	cout << "NOMBRE DEL ARCHIVO: " << file << " // DIMENSION: " << qap.GetDimension() << " // OPTIMO: " << opt << endl;

	//////////////////////////////////////////////////
	///////////////////// Greedy /////////////////////
	//////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.GreedySolver();
		t_despues=std::chrono::high_resolution_clock::now();

		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "Greedy -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "Greedy -> Desviacion: " << desv << " & " << d1.count() << endl;

	///////////////////////////////////////////////////////
	///////////////////// LocalSearch /////////////////////
	///////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.LocalSearch(50000);
		t_despues=std::chrono::high_resolution_clock::now();

		//cout << "LocalSearch1 Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "LocalSearch -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "LocalSearch -> Desviacion: " << desv << " & " << d1.count() << endl;


	//////////////////////////////////////////////////////////////
	///////////////////// SimulatedAnnealing /////////////////////
	//////////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;
	dimension = qap.GetDimension();

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.SimulatedAnnealing(50000, 10*dimension, ceil(0.1*dimension), 0.001);
		t_despues=std::chrono::high_resolution_clock::now();

		// cout << "LocalSearch1 Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "SA -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "SA -> Desviacion: " << desv << " & " << d1.count() << endl;

	/////////////////////////////////////////////////
	///////////////////// GRASP /////////////////////
	/////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);
		//cout << "Semilla en qap: " << qap.GetSeed() << endl;

		t_antes=std::chrono::high_resolution_clock::now();
		qap.GRASP(25, 50000, 0.3);
		t_despues=std::chrono::high_resolution_clock::now();

		//cout << "AGG_Position Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "GRASP -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "GRASP -> Desviacion: " << desv << " & " << d1.count() << endl;

	//////////////////////////////////////////////////////////////////
	///////////////////// Iterative Local Search /////////////////////
	//////////////////////////////////////////////////////////////////
	
	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.IterativeLocalSearch(25, 50000, 4);
		t_despues=std::chrono::high_resolution_clock::now();

		//cout << "AGG_OX Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "ILS -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "ILS -> Desviacion: " << desv << " & " << d1.count() << endl;
	
	//////////////////////////////////////////////////////////////////
	///////////////////// Basic Multiboot Search /////////////////////
	//////////////////////////////////////////////////////////////////
	
	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.BasicMultibootSearch(25, 50000);
		t_despues=std::chrono::high_resolution_clock::now();

		//cout << "AGE_Position Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "BMS -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "BMS -> Desviacion: " << desv << " & " << d1.count() << endl;


	///////////////////////////////////////////////////////////////////////
	///////////////////// IterativeSimulatedAnnealing /////////////////////
	///////////////////////////////////////////////////////////////////////
	
	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;
	dimension = qap.GetDimension();

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.IterativeLocalSearchSA(25, 4, 50000, 10*dimension, ceil(0.1*dimension), 0.001);
		t_despues=std::chrono::high_resolution_clock::now();

		//cout << "AGE_OX Semilla: " << seeds[j] << " Solucion: " << qap.GetSolution() << endl;
		desv += 100.0*((qap.GetSolution() - (double)opt)/(double)opt);

		if(j==0)
			d_acumulado = std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
		else
			d_acumulado += std::chrono::duration_cast<std::chrono::duration<double>>((t_despues-t_antes));
	}

	d1=d_acumulado/(double)seeds.size();

	desv = desv/(double)solutions.size();

	// cout << "ILSSA -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	cout << "ILSSA -> Desviacion: " << desv << " & " << d1.count() << endl;

	
	// cout << endl;
	return 0;

}