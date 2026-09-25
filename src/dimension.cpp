#include "dimension.hpp"

// calculate r(d)
double ord_frac_dimd(double d){
	double r = (tgamma(d+1) * tgamma(d / 2)) / (2 * tgamma(3 * d / 2)); // r(d)
	return r ;
}

// invert r(d) = r_target to return dimension estimate using bisection
double est_dim(double rt, double dl, double dh, double tol){
	double dm = (dl + dh) / 2, rd = 0.0 ; // d_mid, r(d)
	
	while(dh - dl > tol){
		dm = (dl + dh) / 2 ;
		rd = ord_frac_dimd(dm) ;
		if(rd > rt)
			dl = dm ;
		else if(rd < rt)
			dh = dm ;
		else
			break;
	}
	
	return dm ;
}
