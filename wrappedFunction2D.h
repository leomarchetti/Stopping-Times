/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _WRAPPED_FUNCTION_2D_H_
#define _WRAPPED_FUNCTION_2D_H_

#include "functor2D.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class WrappedFunction2D : public Functor2D<FP>
{
  
  public:
    WrappedFunction2D(FP (*fptr)(FP, FP));
    ~WrappedFunction2D();
    FP operator()(FP x, FP y);
    
  protected:

  private:
    FP (*fptr_)(FP, FP);
};

#include "wrappedFunction2D.inl"

}

#endif // _WRAPPED_FUNCTION_2D_H_

