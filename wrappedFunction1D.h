/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _WRAPPED_FUNCTION_1D_H_
#define _WRAPPED_FUNCTION_1D_H_

#include "functor1D.h"

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class WrappedFunction1D : public Functor1D<FP>
{
  
  public:
    WrappedFunction1D(FP (*fptr)(FP));
    ~WrappedFunction1D();
    FP operator()(FP x);
    
  protected:

  private:
    FP (*fptr_)(FP);
};

#include "wrappedFunction1D.inl"

}

#endif // _WRAPPED_FUNCTION_1D_H_

