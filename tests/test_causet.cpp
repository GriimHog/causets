#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <numeric>
#include <cmath>
#include <chrono>
#include "../src/sprinkle.hpp"
#include "../src/causet.hpp"
#include "../src/dimension.hpp"
#include "../src/action.hpp"

using namespace std;

// simple check helper: prints PASS/FAIL with context
void check(const string& name, long long expected, long long actual) {
    if (expected == actual) {
        cout << "PASS: " << name << endl;
    } else {
        cout << "FAIL: " << name << " -- expected " << expected
             << ", got " << actual << endl;
    }
}

int main() {
	// 4-element diamond: a=0, b=1, c=2, d=3
	// a < b, a < c, a < d, b < d, c < d ; b,c unrelated
	vector<vector<bool>> causal(4, vector<bool>(4, false));
	causal[0][1] = true; // a < b
	causal[0][2] = true; // a < c
	causal[0][3] = true; // a < d
	causal[1][3] = true; // b < d
	causal[2][3] = true; // c < d

	vector<long long> N_k(3,0);
	ord_intrv(causal, N_k, 4);
	
	vector<vector<uint64_t>> ftr ;
	vector<vector<uint64_t>> pst ;
	build_bitset_causet(causal, ftr, pst, 4) ;
	
//	check("N_0 (links)", 4, N_k[0]);
//	check("N_1", 0, N_k[1]);
//	check("N_2", 1, N_k[2]);
	
	check("BDG action S (2d, 4-element diamond)", -6, bdg_action_2d(N_k, 4)) ;
	
//	cout << "future[0]: " << bitset<64>(ftr[0][0]) << endl;
//	cout << "future[1]: " << bitset<64>(ftr[1][0]) << endl;
//	cout << "future[2]: " << bitset<64>(ftr[2][0]) << endl;
//	cout << "future[3]: " << bitset<64>(ftr[3][0]) << endl;
//	cout << "past[0]: " << bitset<64>(pst[0][0]) << endl;
//	cout << "past[1]: " << bitset<64>(pst[1][0]) << endl;
//	cout << "past[2]: " << bitset<64>(pst[2][0]) << endl;
//	cout << "past[3]: " << bitset<64>(pst[3][0]) << endl;
	
	
//	//seeding the random number engine rd
//	random_device rd ;
//	uint64_t seed = rd() ;
//	cout << "seed = " << seed << endl ;
//	mt19937_64 rng(seed) ;
//	
//	//defining basic parameters
//	double V = 1.0 ;//volume of region
//	double rho = 1.0 ; int itr ;//density of points and no of iterations
//	
//	cout << "Enter number of iterations : " ;
//	cin >> itr ;
//	
//	for(int p = 0 ; p < 4 ; p++){
//		rho = 1000.0 * pow(2.0, p) ;
//		for(int r = 0 ; r < itr ; r++){
//			vector<double> u, v ; //coords in null	
//			int N = sprinkle(rho, V, rng, u, v) ; //Draw rndm int from poisson dist sprinkle of points

//			//establish causal structure
//			vector<vector<bool>> causal ; //causality matrix
//			
//			int R = build_causet(N, u, v, causal) ;
//			
//			// order interval calculation
//			
//			auto t1_start = chrono::high_resolution_clock::now();
//			vector<long long> N_k_OG, N_k_fst; // allocating N-1 spaces for each interval type maximum possible
//			ord_intrv(causal, N_k_OG, N) ; // order interval count of different types
//			
//			auto t1_end = chrono::high_resolution_clock::now();
//			chrono::duration<double> slow_time = t1_end - t1_start; // check runtime of normal order interval counter
//			
//			long long sum_check = accumulate(N_k_OG.begin(), N_k_OG.end(),0.0) ;
//			cout << "OG :"<< endl ;
//			cout << "N :" << N << ", R :" << R << ", N_k[0](links) :" << N_k_OG[0] << ", N_k Sum :" << sum_check << endl ;
//			cout << "Slow runtime: " << slow_time.count() << " s\n";
//			
//			auto t2_start = chrono::high_resolution_clock::now();
//			
//			vector<vector<uint64_t>> ftr, pst; // bitset future and past matrix for efficiency purposes
//			int wpr = build_bitset_causet(causal, ftr, pst, N) ;
//			ord_intrv_fast(N_k_fst, ftr, pst, N, wpr) ;
//			
//			auto t2_end = chrono::high_resolution_clock::now();
//			chrono::duration<double> fast_time = t2_end - t2_start; // check runtime of bitset order interval counter
//			
//			sum_check = accumulate(N_k_fst.begin(), N_k_fst.end(),0.0) ;
//			cout << "Fast :"<< endl ;
//			cout << "N :" << N << ", R :" << R << ", N_k[0](links) :" << N_k_fst[0] << ", N_k Sum :" << sum_check << endl ;
//			cout << "Fast runtime (incl. bitset build): " << fast_time.count() << " s\n";
//			
//			if (N_k_OG == N_k_fst)
//	    			cout << "Matching Result : Success" << endl;
//			else{
//				cout << "N_k vectors DIFFER." << endl;
//				// find and print exactly where
//				size_t max_len = max(N_k_OG.size(), N_k_fst.size());
//				for (size_t k = 0 ; k < max_len; k++){
//					long long a = (k < N_k_OG.size()) ? N_k_OG[k] : -1;
//					long long b = (k < N_k_fst.size()) ? N_k_fst[k] : -1;
//					if (a != b){
//						cout << "  mismatch at k=" << k << ": slow=" << a << " fast=" << b << endl;
//					}
//				}
//			}
//		}
//	}
	
	return 0;
}
