/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
OppositeFunction2D<FP>::OppositeFunction2D(Functor2D<FP> & f) : f_(f) {}

template <typename FP>
OppositeFunction2D<FP>::~OppositeFunction2D(){}

template <typename FP>
FP OppositeFunction2D<FP>::operator()(FP x, FP y)
{
  return -(f_)(x, y);
}
