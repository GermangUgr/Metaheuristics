//#ifndef QAP
//#define QAP

#include <iostream>
#include <vector>

using namespace std;

struct Solution {

	vector<int> sol_permutation; //Indice -> nº unidad Contenido -> localizacion
	int numeric_solution;
	Solution& operator =(const Solution &s);
	bool operator ==(const Solution &s);
	bool operator !=(const Solution &s);

}; 

class QAP {

private:

	int dimension, Seed;
	int **flux_matrix, **distance_matrix;
	vector<pair<int,int>> pairs_vector;
	Solution solution;
	vector<Solution> population;

	void CalculateNumericSolution();
	void CalculateNumericSolution(Solution &sol);
	int CheckMove(int s, int r);
	int CheckMove(int s, int r, Solution &sol);
	void ApplyMove(int s, int r, int improvement);
	void ApplyMove(int s, int r, int improvement, Solution &sol);
	void Reinicialize();
	void InicializePairsVector(int size);
	void ShufflePairsVector();
	void ShuffleVector(vector<int> &vec);
	void InitializePopulation(int total);
	Solution PositionCrossingOperator(Solution &s1, Solution &s2);
	Solution OXCrossingOperator(Solution &s1, Solution &s2);
	void ApplyMutation(vector<Solution> &p, int num_mut);


public:
	
	//Constructor
	QAP(char* filename, int seed);
	~QAP();

	//Resolutores
	void GreedySolver();
	double LocalSearch1(int max_calls);
	double LocalSearch1(int max_calls, Solution &s1);
	double LocalSearch2(int max_calls);
	void AGG_Position(float P_c, float P_m, int max_eval, int chomosomes);
	void AGG_OX(float P_c, float P_m, int max_eval, int chomosomes);
	void AGE_Position(float P_c, float P_m, int max_eval, int chomosomes);
	void AGE_OX(float P_c, float P_m, int max_eval, int chomosomes);
	void AM_Full(float P_c, float P_m, int max_eval, int chomosomes);
	void AM_Sub(float P_c, float P_m, int max_eval, int chomosomes);
	void AM_Elite(float P_c, float P_m, int max_eval, int chomosomes);


	//Getters
	vector<int> GetSolPermutation();
	int GetSolution();
	int GetDimension();
	Solution GetMember(int index);
	int GetSeed();

	//Setters
	void SetSeed(int s);

};

bool SolutionComparator(const Solution &s1, const Solution &s2);
bool SolutionComparatorByPointer(const pair<int,int> &i, const pair<int,int>  &j);
bool OXComparator(const pair<int,int> &i, const pair<int,int>  &j);

//#endif