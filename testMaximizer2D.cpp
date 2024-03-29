/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include<cstdio>
#include<cmath>
#include<algorithm>
#include<utility>
#include "maximizer2D.h"
#include "wrappedFunction1D.h"
#include "wrappedFunction2D.h"
#include "directionalFunctor.h"


double f(double x){
  return x/3;
}




double g(double x, double y){
	return sin(x*y);
}


double gx(double x, double y){
	return y*cos(x*y);
}

double gy(double x, double y){
	return x*cos(x*y);
}

double gxx(double x, double y){
	return -y*y*sin(x*y);
}


double gxy(double x, double y){
	return cos(x*y) - x*y*sin(x*y);
}


double gyy(double x, double y){
	return -x*x*sin(x*y);
}






bool solve2x2(double a[2][2], double b[2], double &x, double &y){
  if(a[0][0] == 0.0 && a[1][0] == 0.0)
    return false;
  
  if(fabs(a[1][0]) > fabs(a[0][0])){
    std::swap(a[0][0],a[1][0]);
    std::swap(a[0][1],a[1][1]);
    std::swap(b[0],b[1]);
  }

  double d = -a[1][0]/a[0][0];
  if(a[1][1] + d*a[0][1] == 0.0)
    return false;
  y = (b[1] + d*b[0])/(a[1][1] + d*a[0][1]);
  x = (b[0] -  a[0][1]*y)/a[0][0];

  return true;
}

int main(){
  StoppingTimes::WrappedFunction1D<double> F(&f);
  printf("F(9.8) = %.5f\n",F(9.8));
  StoppingTimes::WrappedFunction2D<double> G(&g);
  printf("G(1.0,2.0) = %.5f\n",G(1.0,2.0));
  StoppingTimes::DirectionalFunctor<double> D(G, 0.0,1.0, 1.0, 1.0);
  printf("D(0.0) = %.5f\n",D(0.0));
  printf("D(1.0) = %.5f\n",D(1.0));
  printf("D(-1.0) = %.5f\n",D(-1.0));
  
  double M[2][2] = { {1,2},{3,4}};
  double b[2] = {2,3};
  double x,y;
  solve2x2(M,b,x,y);
  printf("x:%.5f y:%.5f\n",x,y);
  
  double M2[2][2] = { {3,4},{1,2}};
  double b2[2] = {3,2};
  solve2x2(M2,b2,x,y);
  printf("x:%.5f y:%.5f\n",x,y);
  
  StoppingTimes::WrappedFunction2D<double> wg (g);
  StoppingTimes::WrappedFunction2D<double> wgx (gx);
  StoppingTimes::WrappedFunction2D<double> wgy (gy);
  StoppingTimes::WrappedFunction2D<double> wgxx (gxx);
  StoppingTimes::WrappedFunction2D<double> wgxy (gxy);
  StoppingTimes::WrappedFunction2D<double> wgyy (gyy);
  
	StoppingTimes::Maximizer2D<double> m(wg,wgx,wgy,wgxx,wgxy,wgyy);
	std::pair<double,double> B = m.findMaximumNaive(0.5, 3.3, 1.2, 9.0);
	printf("%.8f %.8f -> %.8f\n",B.first,B.second, g(B.first,B.second));
	B = m.findMaximum(0.5, 3.3, 1.2, 9.0);
	printf("%.8f %.8f -> %.8f\n",B.first,B.second, g(B.first,B.second));
	
	return 0;
}
