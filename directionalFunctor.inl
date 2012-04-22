/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
DirectionalFunctor<FP>::DirectionalFunctor(Functor2D<FP> &f2d, FP x0, FP y0, FP dx, FP dy)
                                          : f2d_(f2d), x0_(x0), y0_(y0), dx_(dx) , dy_(dy){}

template <typename FP>
DirectionalFunctor<FP>::~DirectionalFunctor(){}

template <typename FP>
FP DirectionalFunctor<FP>::operator()(FP x){
  return f2d_(x0_ + x*dx_, y0_ + x*dy_);
}

