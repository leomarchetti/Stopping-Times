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
StoppingTimes<FP>::StoppingTimes(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma){
	sde_ = new SDE<FP>(mu, sigma);
	solver_ = DESolver<FP>();
	maximizer_ = Maximizer<FP>();
}

template <typename FP>
FP StoppingTimes<FP>::getBestInferiorLimit(FP rho, int n){
	return (FP)0.0;
}

template <typename FP>
FP StoppingTimes<FP>::getBestSuperiorLimit(FP rho, int n){
	sde_->setRho(rho);
	A_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 1.0, 0.0, n); 
	B_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 0.0, 1.0, n);
	FP k = B_(15.0)/A_(15.0);
	
	maximizer_.setFunction([=](FP c){return c/(k*A_(c)+B_(c));});

	return maximizer_.findMaximum(0.0, 10.0, 1e-7,1e-10);
}	



template <typename FP>
std::pair<FP,FP> StoppingTimes<FP>::getBestInferiorAndSuperiorLimit(FP rho, int n){
	sde_->setRho(rho);
	A_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 1.0, 0.0, n); 
	B_ = boost::bind(&DESolver<FP>::solve, solver_,
														sde_->getSecondDerivative(), _1, 0.0, 1.0, n);
	boost::function<FP(FP)> expectedGain = boost::bind(&StoppingTimes<FP>::bestExpectedGainForInferior, this, _1);
	Maximizer<FP> m(expectedGain);
	FP Linf = m.findMaximum(-10.0, 0.0, 1e-7,1e-10);
	return std::make_pair(Linf, bestExpectedGainForInferior(Linf));
}

template <typename FP>
FP StoppingTimes<FP>::bestExpectedGainForInferior(FP Linf){
	boost::function<FP(FP)> expGI = boost::bind(&StoppingTimes<FP>::expectedGivenInferior, this,
																		Linf, _1);
	maximizer_.setFunction(expGI);	
	return maximizer_.findMaximum(0.0, 10.0, 1e-7,1e-10);																
}

template <typename FP>
FP StoppingTimes<FP>::expectedGivenInferior(FP Linf, FP Lsup){
	FP Ai = A_(Linf), As = A_(Lsup), Bi = B_(Linf), Bs = B_(Lsup);
	FP beta = (Ai*Lsup - Linf*As)/(Ai*Bs - As*Bi);
	FP alpha = (Linf - beta*Bi)/Ai;
	return alpha*A_(0.0) + beta*B_(0.0);
	// eu sei que A(0) = 1 e B(0) = 0, mas se isso vai ficar mais geral no futuro acho que é melhor assim...
}

