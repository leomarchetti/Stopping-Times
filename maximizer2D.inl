/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template<typename FP>
Maximizer2D<FP>::Maximizer2D(boost::function<FP(FP,FP)> F, 
									  boost::function<FP(FP,FP)> Fx = [](FP x, FP y){return 0.0;},
									  boost::function<FP(FP,FP)> Fy = [](FP x, FP y){return 0.0;},
									  boost::function<FP(FP,FP)> Fxx = [](FP x, FP y){return 0.0;},
									  boost::function<FP(FP,FP)> Fxy = [](FP x, FP y){return 0.0;},
									  boost::function<FP(FP,FP)> Fyx = [](FP x, FP y){return 0.0;},
									  boost::function<FP(FP,FP)> Fyy = [](FP x, FP y){return 0.0;}){
  minusF_ = F;
  minusFx_ = Fx;
  minusFy_ = Fy;
  minusFxx_ = Fxx;
  minusFxy_ = Fxy;
  minusFyx_ = Fyx;
  minusFyy_ = Fyy;
}




template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findMaximumNaive(FP xi, FP xs, FP yi, FP ys){
	FP xeps = 0.1*(xs-xi);
	FP yeps = 0.1*(ys-yi);
	std::pair<FP,FP> ret = std::make_pair(xi,yi);
	FP m = F(xi,yi);
	for(FP x = xi; x <= xs; x += xeps)
		for(FP y = yi; y <= ys; y += yeps){
			
			FP fxy = F(x,y);
			
			if(fxy < m){
				m = fxy;
				ret = std::make_pair(x,y);
			}
		}
	return ret;
}

template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findMaximum(FP xi, FP xs, FP yi, FP ys){
	FP xeps = 0.1*(xs-xi);
	FP yeps = 0.1*(ys-yi);
	FP bx = xi,by = xi;
	FP m = F(xi,yi);
	for(FP x = xi; x <= xs; x += xeps)
		for(FP y = yi; y <= ys; y += yeps){
			std::pair<FP,FP> local = findNearLocalMaximum(x,y);
			FP fxy = F(local.first,local.second);
			if(fxy < m){
				m = fxy;
				bx = local.first;
				by = local.second;
			}
		}
	return std::make_pair(bx,by);
}

template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findNearLocalMaximum(FP x, FP y){
	for(int iter = 1; iter<10;iter++){
		FP fx = Fx(x,y), fy = Fy(x,y), fxx = Fxx(x,y), fxy = Fxy(x,y), fyx = Fyx(x,y), fyy = Fyy(x,y);
		FP dx = (y*fxy - fx)/fxx;
		FP dy = (fx*fyx - fy*fxx)/fxx;
		printf("Antes x:%.5f y:%.5f f(x,y):%.5f\n",x,y,F(x,y));
		FP norm = sqrt(dx*dx + dy*dy);
		x = x + 0.001*(dx/norm); 
		y = y + 0.001*(dy/norm);
		printf("Depois x:%.5f y:%.5f f(x,y):%.5f\n",x,y,F(x,y));
	}
	return std::make_pair(x,y);
}



template<typename FP>
FP Maximizer2D<FP>::F(FP x, FP y){
  return -minusF_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fx(FP x, FP y){
  return -minusFx_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fy(FP x, FP y){
  return -minusFy_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fxx(FP x, FP y){
  return -minusFxx_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fxy(FP x, FP y){
  return -minusFxy_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fyx(FP x, FP y){
  return -minusFyx_(x,y);
}

template<typename FP>
FP Maximizer2D<FP>::Fyy(FP x, FP y){
  return -minusFyy_(x,y);
}
