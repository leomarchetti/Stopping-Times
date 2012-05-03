/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _MAXIMIZER2D_H_
#define _MAXIMIZER2D_H_

#include "functor2D.h"
#include "oppositeFunction2D.h"
#include "directionalFunctor.h"
#include "maximizer.h"
#include <utility>

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template<typename FP>
class Maximizer2D {
  
  public:
    Maximizer2D(Functor2D<FP> &F, Functor2D<FP> &Fx, Functor2D<FP> &Fy, Functor2D<FP> &Fxx, Functor2D<FP> &Fxy, Functor2D<FP> &Fyy);
    ~Maximizer2D();
    std::pair<FP,FP> findMaximum(FP xi, FP xf, FP yi, FP yf);
	  std::pair<FP,FP> findMaximumNaive(FP xi, FP xf, FP yi, FP yf);
  protected:

  private:
  	Functor2D<FP> *oriF_;
  	Functor2D<FP> *F_;
  	Functor2D<FP> *Fx_;
  	Functor2D<FP> *Fy_;
  	Functor2D<FP> *Fxx_;
  	Functor2D<FP> *Fxy_;
  	Functor2D<FP> *Fyy_;
    std::pair<FP,FP> findNearLocalMaximum(FP x, FP y,FP xi, FP xf, FP yi, FP yf);
    bool solve2x2a(FP a[2][2], FP b[2], FP &x, FP &y);
    bool solve2x2b(FP a[2][2], FP b[2], FP &x, FP &y);
};
	
#include "maximizer2D.inl"
}

#endif // _MAXIMIZER2D_H_

