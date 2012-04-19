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
	return 6.0-x;
}

double sigma(double x){
	return sqrt(2.0);
}


int main(){
	StoppingTimes::StoppingTimes<double> st(mu,sigma,[](double x){return x;});
	
	
	printf("%.5f\n",st.getBestSuperiorLimit(5.0, 0.001,1000));
	
	//std::pair<double, double> BIS = st.getBestInferiorAndSuperiorLimitOld(5.0, 0.001,1000);
	//printf("%.5f %.5f -> %.5f\n",BIS.first, BIS.second,  st.expectedGivenInferiorAndSuperior(5.0, BIS.first, BIS.second));
	std::pair<double, double> BIS = st.getBestInferiorAndSuperiorLimitNewNaive(5.0, 0.001,1000);
	printf("%.5f %.5f -> %.5f\n",BIS.first, BIS.second, st.expectedGivenInferiorAndSuperior(5.0, BIS.first, BIS.second));
	return 0;
}
