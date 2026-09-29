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

	//seeding the random number engine rd
	random_device rd ;
	uint64_t seed = rd() ;
	cout << "seed = " << seed << endl ;
	mt19937_64 rng(seed) ;
	
	//defining basic parameters
	double V = 1.0 ;//volume of region
	double rho = 1.0 ; int itr ;//density of points and no of iterations
//	cout << "Enter density of points : " ;
//	cin >> rho ;
	cout << "Enter number of iterations : " ;
	cin >> itr ;

	vector<double> ord_fracs(itr) ; //stores order fraction each iteration
	
	for(int p = 0 ; p < 4 ; p++){
		rho = 1000.0 * pow(2.0, p) ;
		for(int r = 0 ; r < itr ; r++){
			vector<double> u, v ; //coords in null	
			int N = sprinkle(rho, V, rng, u, v) ; //Draw rndm int from poisson dist sprinkle of points

			//establish causal structure
			vector<vector<bool>> causal ; //causality matrix
			
			int R = build_causet(N, u, v, causal) ;
			ord_fracs[r] = ord_frac(N, R) ; //ordering fraction (for checking purposes)
			
			auto t1_start = chrono::high_resolution_clock::now();
			// order interval calculation
			vector<long long> N_k_OG, N_k_fst; // allocating N-1 spaces for each interval type maximum possible
			ord_intrv(causal, N_k_OG, N) ; // order interval count of different types
			
			auto t1_end = chrono::high_resolution_clock::now();
			chrono::duration<double> slow_time = t1_end - t1_start; // check runtime of normal order interval counter
			
			long long sum_check = accumulate(N_k_OG.begin(), N_k_OG.end(),0.0) ;
			cout << "OG :"<< endl ;
			cout << "N :" << N << ", R :" << R << ", N_k[0](links) :" << N_k_OG[0] << ", N_k Sum :" << sum_check << endl ;
			cout << "Slow runtime: " << slow_time.count() << " s\n";
			
			auto t2_start = chrono::high_resolution_clock::now();
			
			vector<vector<uint64_t>> ftr, pst; // bitset future and past matrix for efficiency purposes
			int wpr = build_bitset_causet(causal, ftr, pst, N) ;
			ord_intrv_fast(N_k_fst, ftr, pst, N, wpr) ;
			
			auto t2_end = chrono::high_resolution_clock::now();
			chrono::duration<double> fast_time = t2_end - t2_start; // check runtime of bitset order interval counter
			
			sum_check = accumulate(N_k_fst.begin(), N_k_fst.end(),0.0) ;
			cout << "Fast :"<< endl ;
			cout << "N :" << N << ", R :" << R << ", N_k[0](links) :" << N_k_fst[0] << ", N_k Sum :" << sum_check << endl ;
			cout << "Fast runtime (incl. bitset build): " << fast_time.count() << " s\n";
			
			if (N_k_OG == N_k_fst){
	    		cout << "Matching Result : Success" << endl;
			} 
			else{
				cout << "N_k vectors DIFFER." << endl;
				// find and print exactly where
				size_t max_len = max(N_k_OG.size(), N_k_fst.size());
				for (size_t k = 0 ; k < max_len; k++){
					long long a = (k < N_k_OG.size()) ? N_k_OG[k] : -1;
					long long b = (k < N_k_fst.size()) ? N_k_fst[k] : -1;
					if (a != b){
						cout << "  mismatch at k=" << k << ": slow=" << a << " fast=" << b << endl;
					}
				}
			}
		}
	}
	
//	//calc mean
//	double mean = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0) / itr ;
//	
//	//calc std dev
//	double sq_sum = accumulate(ord_fracs.begin(), ord_fracs.end(), 0.0, [mean](double accum, double x) {return accum + (x - mean) * (x - mean) ;}) ;//calc squared sum
//	double stdev = sqrt(sq_sum / itr) ;
//	
//	// dimension estimate under tolerance 1e-6
//	double dmm = est_dim(mean, 0.5, 10, 1e-6) ;
//	double dmin = est_dim(mean - stdev, 0.5, 10, 1e-6) ;
//	double dmax = est_dim(mean + stdev, 0.5, 10, 1e-6) ;
//	double stddmm = abs(dmax - dmin) / 2.0 ;
//	cout <<" the ordering fraction of the ensemble of "<< itr << " iterations is : " << mean << " ± " << stdev << " and the estimate of dimension is : " << dmm << " ± " << stddmm << endl ;
}
