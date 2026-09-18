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
