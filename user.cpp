/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/
/* Stopping Times Library Usage Example */

#include<cstdio>
#include"stoppingTimes.h"

double mu(double x){
	return 5.0;
}

double sigma(double x){
	return 3.0;
}

int main(){
	StoppingTimes::StoppingTimes<double> st(mu,sigma, 1.0);
	printf("%.5f\n",st.getBestInferiorLimit());
	return 0;
}
