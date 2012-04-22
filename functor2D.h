/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _FUNCTOR_2D_H_
#define _FUNCTOR_2D_H_

namespace StoppingTimes{

/* FP is a template for Floating Point types. */
template <typename FP>
class Functor2D 
{
  
  public:
    Functor2D();
    virtual ~Functor2D();
    virtual FP operator()(FP x, FP y);
    
  protected:

  private:
        
};

#include "functor2D.inl"

}

#endif // _FUNCTOR_2D_H_

