/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
Functor2D<FP>::Functor2D(){}

template <typename FP>
Functor2D<FP>::~Functor2D(){}

template <typename FP>
FP Functor2D<FP>::operator()(FP x, FP y){
  return 0.0;
}
