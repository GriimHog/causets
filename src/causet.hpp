#pragma once
#include <vector>
#include <cstdint>

using namespace std;

// Build the causal matrix from coordinates, return count of related pairs R.
int build_causet(int N, const vector<double>& u, const vector<double>& v, vector<vector<bool>>& causal);

// Ordering fraction r = 2R / (N(N-1))
double ord_frac(int N, int R);

// count the order interval of different types N_0, N_1, N_2 ...
void ord_intrv(const vector<vector<bool>>& causal, vector<long long>& N_k, int N);

//Build the bitset version of build_causet
int build_bitset_causet(const vector<vector<bool>>& causal, vector<vector<uint64_t>>& ftr, vector<vector<uint64_t>>& pst, int N);

// faster order interval count
void ord_intrv_fast(vector<long long>& N_k, vector<vector<uint64_t>>& ftr, vector<vector<uint64_t>>& pst, int N, int wpr);
