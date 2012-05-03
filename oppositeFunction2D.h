/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _OPPOSITE_FUNCTION_2D_H_
#define _OPPOSITE_FUNCTION_2D_H_

#include "functor2D.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class OppositeFunction2D : public Functor2D<FP>
{
  
  public:
    OppositeFunction2D(Functor2D<FP> & f);
    ~OppositeFunction2D();
    FP operator()(FP x, FP y);
    
  protected:

  private:
    Functor2D<FP> & f_;
};

#include "oppositeFunction2D.inl"

}

#endif // _OPPOSITE_FUNCTION_2D_H_

