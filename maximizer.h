/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _MAXIMIZER_H_
#define _MAXIMIZER_H_

#include<boost/function.hpp>
#include<cmath>

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template<typename FP>
class Maximizer {
  
  public:
    Maximizer();
    Maximizer(boost::function<FP(FP)> minusF);
    FP findMaximum(FP a, FP b, FP rel_tol, FP abs_tol);
    void setFunction(boost::function<FP(FP)> minusF);

  protected:

  private:
    boost::function<FP(FP)> minusF_;
    FP f(FP x);
    FP localMinBrent(FP a, FP b, FP rel_tol, FP abs_tol);
  
};

#include "maximizer.inl"

}

#endif // _MAXIMIZER_H_

