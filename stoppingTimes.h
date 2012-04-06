/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _STOPPING_TIMES_H_
#define _STOPPING_TIMES_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <utility>
#include "maximizer.h"
#include "sde.h"
#include "de-solver.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class StoppingTimes
{
  public:
  	 ~StoppingTimes();
    StoppingTimes(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma);
    std::pair<FP,FP> getBestInferiorAndSuperiorLimit(FP rho, int n);
    FP getBestSuperiorLimit(FP rho, int n);
    FP getBestInferiorLimit(FP rho, int n);
  
  protected:

  private:
    FP rho_;
    SDE<FP> *sde_;
    DESolver<FP> solver_;
    Maximizer<FP> maximizer_;
    boost::function<FP(FP)> A_;
    boost::function<FP(FP)> B_;
    FP bestExpectedGainForInferior(FP Linf);
    FP expectedGivenInferior(FP Linf, FP Lsup);
};

#include "stoppingTimes.inl"

}

#endif // _STOPPING_TIMES_H_

