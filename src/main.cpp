#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include <chrono>
#include "sprinkle.hpp"
#include "causet.hpp"
#include "dimension.hpp"

using namespace std ;

int main(){
	auto start = chrono::high_resolution_clock::now();
	
	//seeding the random number engine rd
	random_device rd ;
	uint64_t seed = rd() ;
	cout << "seed = " << seed << endl ;
	mt19937_64 rng(seed) ;
	
	//defining basic parameters
	double V = 1.0 ;//volume of region
	double rho = 1.0 ; int itr ;//density of points and no of iterations
	cout << "Enter density of points : " ;
	cin >> rho ;
	cout << "Enter number of iterations : " ;
	cin >> itr ;

	vector<double> ord_fracs(itr) ; //stores order fraction each iteration
	
	for(int r = 0 ; r < itr ; r++){
		vector<double> u, v ; //coords in null	
		int N = sprinkle(rho, V, rng, u, v) ; //Draw rndm int from poisson dist sprinkle of points

		//establish causal structure
		vector<vector<bool>> causal ; //causality matrix

		int R = build_causet(N, u, v, causal) ;
		ord_fracs[r] = ord_frac(N, R) ; //ordering fraction (for checking purposes)

		// order interval calculation
		vector<long long> N_k ; // allocating N-1 spaces for each interval type maximum possible
		vector<vector<uint64_t>> ftr, pst; // bitset future and past matrix for efficiency purposes
		int wpr = build_bitset_causet(causal, ftr, pst, N) ;
		ord_intrv_fast(N_k, ftr, pst, N, wpr) ; // order interval count of different types

		long long sum_check = accumulate(N_k.begin(), N_k.end(),0.0) ;
		cout << "N :" << N << ", R :" << R << ", N_k[0](links) :" << N_k[0] << ", N_k Sum :" << sum_check << endl ;
	}
	
	//calc mean
	double mean = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0) / itr ;
	
	//calc std dev
	double sq_sum = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0, [mean](double accum, double x) {return accum + (x - mean) * (x - mean) ;}) ;//calc squared sum
	double stdev = sqrt(sq_sum / itr) ;
	
	// dimension estimate under tolerance 1e-6
	double dmm = est_dim(mean, 0.5, 10, 1e-6) ;
	double dmin = est_dim(mean - stdev, 0.5, 10, 1e-6) ;
	double dmax = est_dim(mean + stdev, 0.5, 10, 1e-6) ;
	double stddmm = abs(dmax - dmin) / 2.0 ;
	cout <<" the ordering fraction of the ensemble of "<< itr << " iterations is : " << mean << " ± " << stdev << " and the estimate of dimension is : " << dmm << " ± " << stddmm << endl ;

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> runtime = end - start; // check runtime
	cout << "Runtime : " << runtime.count() << " s\n";
}
