/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _FUNCTOR_1D_H_
#define _FUNCTOR_1D_H_

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class Functor1D 
{
  
  public:
    Functor1D();
    virtual ~Functor1D();
    virtual FP operator()(FP x);
    
  protected:

  private:
        
};

#include "functor1D.inl"

}

#endif // _FUNCTOR_1D_H_

