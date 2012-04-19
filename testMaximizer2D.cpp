/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/
/* Stopping Times Library Usage Example */

#include<cstdio>
#include<cmath>
#include<utility>
#include"maximizer2D.h"


double f(double x, double y){
	return 3.0*x*x*x + 2.0*x*y*y + y*y;
}

int main(){
	StoppingTimes::Maximizer2D<double> m(  f,
													 	[](double x,double y){return 9.0*x*x + 2.0*y*y;},
													 	[](double x,double y){return 4.0*x*y + 2.0*y;},
													 	[](double x,double y){return 18.0*x;},
													 	[](double x,double y){return 4.0*y;},
													 	[](double x,double y){return 4.0*y;},
													 	[](double x,double y){return 4.0*x + 2.0;});
	std::pair<double, double> B = m.findMaximumNaive(0.5, 3.3, 1.2, 9.0);
	printf("%.8f %.8f -> %.8f\n",B.first,B.second, f(B.first,B.second));
	B = m.findMaximum(0.5, 3.3, 1.2, 9.0);
	printf("%.8f %.8f -> %.8f\n",B.first,B.second, f(B.first,B.second));
	return 0;
}
