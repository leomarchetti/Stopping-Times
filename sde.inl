/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
SDE<FP>::SDE(){}

template <typename FP>
SDE<FP>::SDE(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma, FP rho)
  : mu_(mu), sigma_(sigma), rho_(rho)
{
  ddf_ = boost::bind(&SDE::secondDerivative, this, _1, _2, _3); 
}

template <typename FP>
SDE<FP>::SDE(const SDE<FP>& source){
  mu_ = source.mu_;
  sigma_ = source.sigma_;
  ddf_ = source.ddf_;
  rho_ = source.rho_;
}

template <typename FP>
FP SDE<FP>::secondDerivative(FP x, FP fx, FP dfx){
  FP s = sigma_(x);
  return 2.0*(rho_*fx - mu_(x)*dfx)/(s*s);
}

template <typename FP>
boost::function<FP(FP, FP, FP)>  SDE<FP>::getSecondDerivative(){
  return ddf_;
}


