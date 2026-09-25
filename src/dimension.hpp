#pragma once
#include <cmath>

// calculate r(d)
double ord_frac_dimd(double d);

// invert r(d) = r_target to return dimension estimate using bisection
double est_dim(double rt, double dl, double dh, double tol);
