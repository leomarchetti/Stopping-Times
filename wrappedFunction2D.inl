/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
WrappedFunction2D<FP>::WrappedFunction2D(FP (*fptr)(FP, FP)) : fptr_(fptr){}

template <typename FP>
WrappedFunction2D<FP>::~WrappedFunction2D(){}

template <typename FP>
FP WrappedFunction2D<FP>::operator()(FP x, FP y)
{
  return (*fptr_)(x, y);
}
