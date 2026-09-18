#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include "sprinkle.hpp"
#include "causet.hpp"

using namespace std ;

int main(){

	//seeding the random number engine rd
	random_device rd ;
	uint64_t seed = rd() ;
	cout << "seed = " << seed << endl ;
	mt19937_64 rng(seed) ;
	
	//defining basic parameters
	double V = 1.0 ;//volume of region
	double rho; int itr ;//density of points and no of iterations
	cout << "Enter density of points :" ;
	cin >> rho ;
	cout << "Enter number of iterations :" ;
	cin >> itr ;

	vector<double> ord_fracs(itr) ; //stores order fraction each iteration
	for(int r = 0 ; r < itr ; r++){
		vector<double> u, v ; //coords in null	
		int N = sprinkle(rho, V, rng, u, v) ; //Draw rndm int from poisson dist sprinkle of points

		//establish causal structure
		vector<vector<bool>> causal ; //causality matrix
		int R = build_causet(N, u, v, causal) ;
		
		ord_fracs[r] = ord_frac(N, R) ; //ordering fraction (for checking purposes)	
	}
	//calc mean
	double mean = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0) / itr ;
	
	//calc std dev
	double sq_sum = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0, [mean](double accum, double x) {return accum + (x - mean) * (x - mean) ;}) ;//calc squared sum
	double stdev = sqrt(sq_sum / itr) ;
	
	cout <<"Mean , Standard Deviation of "<< itr << " iterations is :" << mean << ", " << stdev << endl ;
}

