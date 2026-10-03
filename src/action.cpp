#include "action.hpp"

// compute the BDG action.
long long bdg_action_2d(const vector<long long>& N_k, int N){
	long long S ;
	vector<int> coeff = {-2, 4, -2} ;
	int size = N_k.size() ;
	if(size < 3) // handles tiny causets where N_k has fewer than 3 entries, by letting inner_product naturally pair against however many entries exist
		S = inner_product(N_k.begin(), N_k.end(), coeff.begin(), (long long)N) ;
	else
		S = inner_product(coeff.begin(), coeff.end(), N_k.begin(), (long long)N) ;
	return S ;
}
