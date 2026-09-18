#pragma once
#include <vector>
using namespace std;

// Build the causal matrix from coordinates, return count of related pairs R.
int build_causet(int N, const vector<double>& u, const vector<double>& v, vector<vector<bool>>& causal);

// Ordering fraction r = 2R / (N(N-1))
double ord_frac(int N, int R);
