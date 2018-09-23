#include <iostream>
#include "QAP.h"
#include <vector>
#include <chrono>
#include <string>
#include <assert.h>
#include <fstream>


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

	//Obtenemos el optipo almacenado en el archivo .sln correspondiente al .dat pasado como argumento
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

	cout << "Greedy -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "Greedy -> Desviacion: " << desv << " & " << d1.count() << endl;

	////////////////////////////////////////////////////////
	///////////////////// LocalSearch1 /////////////////////
	////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.LocalSearch1(50000);
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

	cout << "LocalSearch1 -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "LocalSearch1 -> Desviacion: " << desv << " & " << d1.count() << endl;


	////////////////////////////////////////////////////////
	///////////////////// LocalSearch2 /////////////////////
	////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.LocalSearch2(50000);
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

	cout << "LocalSearch2 -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "LocalSearch2 -> Desviacion: " << desv << " & " << d1.count() << endl;

	//////////////////////////////////////////////////////////////////////////
	///////////////////// GENETICO GENERACIONAL POSICION /////////////////////
	//////////////////////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);
		//cout << "Semilla en qap: " << qap.GetSeed() << endl;

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AGG_Position(0.7, 0.001, 50000, 50);
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

	cout << "AGG_Position -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AGG_Position -> Desviacion: " << desv << " & " << d1.count() << endl;

	////////////////////////////////////////////////////////////////////
	///////////////////// GENETICO GENERACIONAL OX /////////////////////
	////////////////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AGG_OX(0.7, 0.001, 50000, 50);
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

	cout << "AGG_OX -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AGG_OX -> Desviacion: " << desv << " & " << d1.count() << endl;

	//////////////////////////////////////////////////////////////////////////
	///////////////////// GENETICO ESTACIONARIO POSICION /////////////////////
	//////////////////////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AGE_Position(0.7, 0.001, 50000, 50);
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

	cout << "AGE_Position -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AGE_Position -> Desviacion: " << desv << " & " << d1.count() << endl;

	////////////////////////////////////////////////////////////////////
	///////////////////// GENETICO ESTACIONARIO OX /////////////////////
	////////////////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AGE_OX(0.7, 0.001, 50000, 50);
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

	cout << "AGE_OX -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AGE_OX -> Desviacion: " << desv << " & " << d1.count() << endl;

	/////////////////////////////////////////////////////////
	///////////////////// MEMETICO FULL /////////////////////
	/////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AM_Full(0.7, 0.001, 50000, 50);
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

	cout << "AM_Full -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AM_Full -> Desviacion: " << desv << " & " << d1.count() << endl;

	////////////////////////////////////////////////////////
	///////////////////// MEMETICO SUB /////////////////////
	////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AM_Sub(0.7, 0.001, 50000, 50);
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

	cout << "AM_Sub -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AM_Sub -> Desviacion: " << desv << " & " << d1.count() << endl;

	//////////////////////////////////////////////////////////
	///////////////////// MEMETICO ELITE /////////////////////
	//////////////////////////////////////////////////////////

	cout << endl;
	solutions.clear();
	solutions.resize(5);
	desv = 0;

	for(int j=0; j<seeds.size(); j++) {

		qap.SetSeed(seeds[j]);

		t_antes=std::chrono::high_resolution_clock::now();
		qap.AM_Elite(0.7, 0.001, 50000, 50);
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

	cout << "AM_Elite -> Desviacion: " << desv << " Duracion: " << d1.count() << endl;
	// cout << "AM_Elite -> Desviacion: " << desv << " & " << d1.count() << endl;




	cout << endl;
	return 0;

}