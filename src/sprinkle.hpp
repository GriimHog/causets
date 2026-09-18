#pragma once
#include <vector>
#include <random>
using namespace std;

// Sprinkle N points (N drawn from Poisson(rho*V)) into the unit square
// in light-cone coordinates u,v. Returns N by writing into u and v.
int sprinkle(double rho, double V, mt19937_64& rng, vector<double>& u, vector<double>& v);
