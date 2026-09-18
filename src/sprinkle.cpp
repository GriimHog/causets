#include "sprinkle.hpp"

int sprinkle(double rho, double V, mt19937_64& rng, vector<double>& u, vector<double>& v) {
	
	//define poisson dist with mean (rho*V)
	poisson_distribution<int> pois(rho * V) ;
	int N = pois(rng);
	
	//define uniform distribution in
	uniform_real_distribution<double>  unidis(0,1) ;
	
	//creating point set
	u.resize(N);
	v.resize(N);
	for (int i = 0; i < N; i++) {
		u[i] = unidis(rng);
		v[i] = unidis(rng);
	}//this part will be be used later on
	
	return N;
}
