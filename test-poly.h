/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _TEST_POLY_
#define _TEST_POLY_

#include <vector>

namespace StoppingTimes{ namespace Testing{

class TestPoly {
  // coef_[0]*x^0 + coef_[1]*x^1 + ... + coef_[n]*x^n
  
  public:
    TestPoly();
    TestPoly(const std::vector<double> &coef);
    TestPoly(const TestPoly& source);
    double evaluate(double x);
    
  protected:

  private:
    std::vector<double> coef_;
    
};

}}

#endif // _TEST_POLY_

