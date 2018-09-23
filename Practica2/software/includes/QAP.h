//#ifndef QAP
//#define QAP

#include <iostream>
#include <vector>

using namespace std;

typedef vector<pair<int,int>> PairList;

struct Solution {

	vector<int> sol_permutation; //Indice -> nº unidad, Contenido -> localizacion
	int numeric_solution;
	Solution& operator =(const Solution &s);
	bool operator ==(const Solution &s);
	bool operator !=(const Solution &s);

}; 

class QAP {

private:

	int dimension, Seed;
	int **flux_matrix, **distance_matrix;
	Solution solution;

	void CalculateNumericSolution();
	void CalculateNumericSolution(Solution &sol);
	int CheckMove(int s, int r);
	int CheckMove(int s, int r, Solution &sol);
	int CheckAdd(int unit, int loc, vector<int> &assig);
	void ApplyMove(int s, int r, int improvement);
	void ApplyMove(int s, int r, int improvement, Solution &sol);
	void Reinicialize();
	void ShuffleVector(vector<int> &vec);
	void CalculateRandGreedy(float alpha);
	void CostsLists(vector<int> &Units, vector<int> &Locations, float alpha, PairList &BestUnits, PairList &BestLocations);
	void RandomSublistMutation(Solution &sol, int sublist_fraction);



public:
	
	//Constructor
	QAP(char* filename, int seed);
	~QAP();

	//Resolutores
	void GreedySolver();
	double LocalSearch(int max_calls, bool reini = true);
	void SimulatedAnnealing(int max_iters, int max_neig, int max_scs, float T_fin, float nu = 0.3, float phi = 0.3, bool reini = true);
	void GRASP(int max_iters, int max_iters_ls, float alpha);
	void IterativeLocalSearch(int max_iters, int LS_max_calls, int sublist_fraction);
	void BasicMultibootSearch(int max_iters, int LS_max_calls);
	void IterativeLocalSearchSA(int max_iters, int sublist_fraction,
								int SA_max_iters, int SA_max_neig, int SA_max_scs, float SA_T_fin, float SA_nu = 0.3, float SA_phi = 0.3);



	//Getters
	vector<int> GetSolPermutation();
	int GetSolution();
	int GetDimension();
	int GetSeed();

	//Setters
	void SetSeed(int s);

};

bool SolutionComparator(const Solution &s1, const Solution &s2);
pair<int,int> DiffRands(int l, int h, int Seed);

//#endif