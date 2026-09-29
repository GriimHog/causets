#include "causet.hpp"

//building the causal matrix ; Returns the number of causal pairs
int build_causet(int N, const vector<double>& u, const vector<double>& v, vector<vector<bool>>& causal){

	causal.assign(N, vector<bool>(N, false));   // allocate N x N, default false
	
	int R = 0 ;
	for(int i = 0 ; i <= N-1 ; i++){
		for(int j = 0 ; j <= N-1 ; j++){
			if(i != j and u[i] < u[j] and v[i] < v[j]){
				causal[i][j] = true ;
				R = R + 1 ;
			}
		}
	}
	
	return R ;
}

//ordering fraction r
double ord_frac(int N, int R){
	double r = (2.0 * R) / (N * (N-1)) ;
	return r ;
}

// count the order interval of different types N_0, N_1, N_2 ...
void ord_intrv(const vector<vector<bool>>& causal, vector<long long>& N_k, int N){
	N_k.assign(N-1, 0) ;
	for(int i = 0 ; i < N ; i++){
		for(int j = 0 ; j < N ; j++){
			long long cnt = 0 ;
			if(causal[i][j]){
				for(int k = 0 ; k < N ; k++){
				if(causal[i][k] && causal[k][j])
					cnt++ ;
				}
				N_k[cnt]++;
			}
		}
	}
}

//Build the bitset version of build_causet
int build_bitset_causet(const vector<vector<bool>>& causal, vector<vector<uint64_t>>& ftr, vector<vector<uint64_t>>& pst, int N){
	int wpr = (N + 63) / 64 ; // word per row
	
	ftr.assign(N, vector<uint64_t>(wpr, 0)) ;
	pst.assign(N, vector<uint64_t>(wpr, 0)) ;
	
	for(int i = 0 ; i < N ; i++ ){
		for(int j = 0 ; j < N ; j++ ){
			if(causal[i][j] == true){
				ftr[i][j / 64] |= (1ULL << (j % 64)) ;
				pst[j][i / 64] |= (1ULL << (i % 64)) ;
			}
		}
	}
	return wpr ;
}

// faster order interval count
void ord_intrv_fast(vector<long long>& N_k, vector<vector<uint64_t>>& ftr, vector<vector<uint64_t>>& pst, int N, int wpr){
	N_k.assign(N-1, 0) ;
	
	for(int i = 0 ; i < N ; i++){
		for(int j = 0 ; j < N ; j++){
			long long cnt = 0 ;
			if((ftr[i][j / 64] & (1ULL << (j % 64))) != 0){
				for(int w = 0 ; w < wpr ; w++){
					uint64_t overlap = ftr[i][w] & pst[j][w] ;
						cnt += __builtin_popcountll(overlap) ;
				}
				N_k[cnt]++;
			}
		}
	}
}
