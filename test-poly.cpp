/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include "test-poly.h"
#include <vector>
using namespace std;

namespace StoppingTimes{ namespace Testing{

TestPoly::TestPoly(){}

TestPoly::TestPoly(const vector<double> &coef) : coef_(coef){}

TestPoly::TestPoly(const TestPoly& source){
  coef_ = source.coef_;
}

/* Evaluate the polynomial using Horner Scheme */
double TestPoly::evaluate(double x){
  double res = 0.0;
  for(int i = (int)coef_.size() - 1; i>=0; i--)
    res = res*x + coef_[i];
  return res;
}

}}

