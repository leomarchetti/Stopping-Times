/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template <typename FP>
StoppingTimes<FP>::StoppingTimes(){}

template <typename FP>
StoppingTimes<FP>::~StoppingTimes()
{
	delete sde_;
}

template <typename FP>
StoppingTimes<FP>::StoppingTimes(boost::function<FP(FP)> mu, boost::function<FP(FP)> sigma, FP rho)
	: rho_(rho)
{
	sde_ = new SDE<FP>(mu, sigma, rho);
	solver_ = DESolver<FP>();
	maximizer_ = Maximizer<FP>();
}

template <typename FP>
FP StoppingTimes<FP>::getBestInferiorLimit(){
	boost::function<FP(FP)> expectedGain = boost::bind(&DESolver<FP>::solve, solver_,
																		sde_->getSecondDerivative(), 0.0, _1, 0.0, 1000); 
	maximizer_.setFunction( expectedGain );
	return maximizer_.findMaximum(-1000.0, 0.0, 1e-7,1e-10);
}





