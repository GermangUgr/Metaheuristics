#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

using namespace std;

void Format(char* filename){

	int dim = 0, data = 0;
	ifstream f;
	int aux;

	f.open(filename);

	assert(f.is_open());

	//Read instance dimension

	//f.ignore(1,' ');

	f >> dim;

	int **m1 = new int*[dim];
	int **m2 = new int*[dim];

	for(int i=0; i<dim; i++){

		m1[i] = new int[dim];
		m2[i] = new int[dim];
	}

	f.ignore(1,'\n');

	//Read firsts dim*dim integers (first matrix)

	for(int i=0; i<dim && !f.eof(); i++){

		for(int j=0; j<dim; j++){

			f >> data;
			m1[i][j] = data;
		}
	}

	f.ignore(1,'\n');

	//Read seconds dim*dim integers (second matrix)

	for(int i=0; i<dim && !f.eof(); i++){

		for(int j=0; j<dim; j++){

			f >> data;
			m2[i][j] = data;
		}
	}

	//Print instance dimension

	cout << dim << endl;

	cout << endl;

	//Print first matrix

	for(int i=0; i<dim; i++){

		for(int j=0; j<dim; j++)
			cout << m1[i][j] << " ";

		cout << endl;
	}

	//Print second matrix

	cout << endl;

	for(int i=0; i<dim; i++){

		for(int j=0; j<dim; j++)
			cout << m2[i][j] << " ";

		cout << endl;
	}


	f.close();

}

//Compilar con: g++ -o ExeCorrector corrector.cpp

int main (int argc, char **argv){

	if(argc != 2){
	
		cerr << "Especifique el nombre del fichero de datos" << endl;
		return -1;

	}

	char *nombre = argv[1];

	Format(nombre);

	return 0;

}