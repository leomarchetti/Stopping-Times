/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/
/* Stopping Times Library Usage Example */

#include<cstdio>
#include<cmath>
#include<utility>
#include"stoppingTimes.h"

double mu(double x){
	return -x;
}

double sigma(double x){
	return sqrt(2.0);
}


int main(){
	StoppingTimes::StoppingTimes<double> st(mu,sigma,[](double x){return x;});
	printf("%.5f\n",st.getBestSuperiorLimit(0.0, 0.001,1000));
	std::pair<double, double> BIS = st.getBestInferiorAndSuperiorLimit(0.0, 0.001,1000);
	printf("%.5f %.5f\n",BIS.first, BIS.second);
	return 0;
}
