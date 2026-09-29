#include <iostream>
#include <vector>
#include "../src/causet.hpp"
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

    check("N_0 (links)", 4, N_k[0]);
    check("N_1", 0, N_k[1]);
    check("N_2", 1, N_k[2]);

    return 0;
}
