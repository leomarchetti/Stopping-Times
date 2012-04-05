/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _DE_SOLVER_H_
#define _DE_SOLVER_H_

#include <boost/function.hpp>
#include "de-solver.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template<typename FP>
class DESolver {

  public:
    FP solve(boost::function<FP(FP, FP, FP)> ddf, FP xf, FP f0, FP df0, int n);

  protected:

  private:
    FP RungeKutta(boost::function<FP(FP, FP, FP)> ddf, FP xf, FP f0, FP df0, int n);

};

#include "de-solver.inl"
  
}

#endif // _DE_SOLVER_H_

