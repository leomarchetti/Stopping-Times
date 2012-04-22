/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
Functor1D<FP>::Functor1D(){}

template <typename FP>
Functor1D<FP>::~Functor1D(){}

template <typename FP>
FP Functor1D<FP>::operator()(FP x){
  return 0.0;
}
