/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _MAXIMIZER2D_H_
#define _MAXIMIZER2D_H_

#include<boost/function.hpp>
#include<cmath>
#include <algorithm>

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template<typename FP>
class Maximizer2D {
  
  public:
    Maximizer2D(boost::function<FP(FP,FP)> F, 
					 boost::function<FP(FP,FP)> Fx,
					 boost::function<FP(FP,FP)> Fy,
					 boost::function<FP(FP,FP)> Fxx,
					 boost::function<FP(FP,FP)> Fxy,
					 boost::function<FP(FP,FP)> Fyx,
					 boost::function<FP(FP,FP)> Fyy );
    std::pair<FP,FP> findMaximum(FP xi, FP xs, FP yi, FP ys);
	 std::pair<FP,FP> findMaximumNaive(FP xi, FP xs, FP yi, FP ys);
  protected:

  private:
    boost::function<FP(FP,FP)> minusF_;
    boost::function<FP(FP,FP)> minusFx_;
    boost::function<FP(FP,FP)> minusFy_;
    boost::function<FP(FP,FP)> minusFxx_;
    boost::function<FP(FP,FP)> minusFxy_;
    boost::function<FP(FP,FP)> minusFyx_;
    boost::function<FP(FP,FP)> minusFyy_;
    
    FP F(FP x, FP y);
    FP Fx(FP x, FP y);
    FP Fy(FP x, FP y);
    FP Fxx(FP x, FP y);
    FP Fxy(FP x, FP y);
    FP Fyx(FP x, FP y);
    FP Fyy(FP x, FP y);
    std::pair<FP,FP> findNearLocalMaximum(FP x, FP y);
};

#include "maximizer2D.inl"

}

#endif // _MAXIMIZER2D_H_

