/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/


template <typename FP>
StoppingTimes<FP>::~StoppingTimes()
{
	delete sde_;
}

template <typename FP>
StoppingTimes<FP>::StoppingTimes(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma, 
											  boost::function<FP(FP)> g = [](FP x){return x;} ){
	sde_ = new SDE<FP>(mu, sigma);
	solver_ = DESolver<FP>();
	maximizer_ = Maximizer<FP>();
	g_ = g;
}

template <typename FP>
FP StoppingTimes<FP>::getBestInferiorLimit(FP x0, FP rho, int n){
	return (FP)0.0;
}

template <typename FP>
FP StoppingTimes<FP>::getBestSuperiorLimit(FP x0, FP rho, int n){
	sde_->setRho(rho);
	A_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 1.0, 0.0, n); 
	B_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 0.0, 1.0, n);
	FP k = B_(15.0)/A_(15.0);
	maximizer_.setFunction([=](FP c){return c/(k*A_(c)+B_(c));});

	return maximizer_.findMaximum(x0, 10.0*x0+10.0, 1e-7,1e-10);
}	



template <typename FP>
std::pair<FP,FP> StoppingTimes<FP>::getBestInferiorAndSuperiorLimit(FP x0, FP rho, int n){
	sde_->setRho(rho);
	A_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 1.0, 0.0, n); 
	B_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 0.0, 1.0, n);
	boost::function<FP(FP)> expectedGain = boost::bind(&StoppingTimes<FP>::bestExpectedGainForInferior, this, x0, _1);
	Maximizer<FP> m(expectedGain);
	FP Linf = m.findMaximum(-10.0, x0, 1e-7,1e-10);
	return std::make_pair(Linf, bestExpectedGainForInferior(x0,Linf));
}

template <typename FP>
FP StoppingTimes<FP>::bestExpectedGainForInferior(FP x0, FP Linf){
	boost::function<FP(FP)> expGI = boost::bind(&StoppingTimes<FP>::expectedGivenInferior, this,
																		x0, Linf, _1);
	maximizer_.setFunction(expGI);	
	return maximizer_.findMaximum(x0, 10.0*x0+10.0, 1e-7,1e-10);																
}

template <typename FP>
FP StoppingTimes<FP>::expectedGivenInferior(FP x0, FP Linf, FP Lsup){
	FP Ai = A_(Linf), As = A_(Lsup), Bi = B_(Linf), Bs = B_(Lsup), gi = g_(Linf);
	FP beta = (Ai*g_(Lsup) - gi*As)/(Ai*Bs - As*Bi);
	FP alpha = (gi - beta*Bi)/Ai;
	return alpha*A_(x0) + beta*B_(x0);
}

