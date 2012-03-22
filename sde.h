/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _SDE_H_
#define _SDE_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class SDE 
{
  
  public:
    SDE();
    SDE(const SDE& source);
    SDE(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma, FP rho);
    boost::function<FP(FP, FP, FP)> getSecondDerivative();
    
  protected:

  private:
    boost::function<FP(FP)> mu_;
    boost::function<FP(FP)> sigma_;
    FP rho_;
    boost::function<FP(FP, FP, FP)> ddf_;
    FP secondDerivative(FP x, FP fx, FP dfx);

};

#include "sde.inl"

}

#endif // _SDE_H_

