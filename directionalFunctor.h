/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _DIRECTIONAL_FUNCTOR_H_
#define _DIRECTIONAL_FUNCTOR_H_

#include "functor1D.h"
#include "functor2D.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class DirectionalFunctor : public Functor1D<FP>
{
 
  public:
    DirectionalFunctor(Functor2D<FP> &f2d, FP x0, FP y0, FP dx, FP dy);
    ~DirectionalFunctor();
    FP operator()(FP x);
    
  protected:

  private:
    Functor2D<FP> &f2d_;
    FP x0_;
    FP y0_;
    FP dx_;
    FP dy_;
};

#include "directionalFunctor.inl"

}

#endif // _DIRECTIONAL_FUNCTOR_H_

