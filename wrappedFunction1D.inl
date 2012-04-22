/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
inline WrappedFunction1D<FP>::WrappedFunction1D(FP (*fptr)(FP)) : fptr_(fptr){}

template <typename FP>
inline WrappedFunction1D<FP>::~WrappedFunction1D(){}

template <typename FP>
inline FP WrappedFunction1D<FP>::operator()(FP x)
{
  return (*fptr_)(x);
}
