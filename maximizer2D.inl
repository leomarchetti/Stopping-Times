/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/


template<typename FP>
Maximizer2D<FP>::Maximizer2D(Functor2D<FP> &F, Functor2D<FP> &Fx, Functor2D<FP> &Fy, 
														 Functor2D<FP> &Fxx, Functor2D<FP> &Fxy, Functor2D<FP> &Fyy){
  oriF_ = &F;
  F_ = new OppositeFunction2D<FP>(F);
	Fx_ = new OppositeFunction2D<FP>(Fx);
	Fy_ = new OppositeFunction2D<FP>(Fy);
	Fxx_ = new OppositeFunction2D<FP>(Fxx);
	Fxy_ = new OppositeFunction2D<FP>(Fxy);
	Fyy_ = new OppositeFunction2D<FP>(Fyy);
}

template<typename FP>
Maximizer2D<FP>::~Maximizer2D(){
	delete F_;
	delete Fx_;
	delete Fy_;
	delete Fxx_;
	delete Fxy_;
	delete Fyy_;
}

template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findMaximumNaive(FP xi, FP xf, FP yi, FP yf){
	FP xeps = 0.1*(xf-xi);
	FP yeps = 0.1*(yf-yi);
	std::pair<FP,FP> ret = std::make_pair(xi,yi);
	FP m = (*F_)(xi,yi);
	for(FP x = xi; x <= xf; x += xeps)
		for(FP y = yi; y <= yf; y += yeps){
			FP fxy = (*F_)(x,y);
			//printf("x:%.8f y:%.8f F(x,y):%.8f\n",x,y,(*F_)(x,y));
			if(fxy < m){
				m = fxy;
				ret = std::make_pair(x,y);
			}
		}
	return ret;
}

template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findMaximum(FP xi, FP xf, FP yi, FP yf){
	FP xeps = 0.1*(xf-xi);
	FP yeps = 0.1*(yf-yi);
	FP bx = xi,by = xi;
	FP m = (*F_)(xi,yi);
	for(FP x = xi; x <= xf; x += xeps)
		for(FP y = yi; y <= yf; y += yeps){
			std::pair<FP,FP> local = findNearLocalMaximum(x, y, xi, xf, yi, yf);
			FP fxy = (*F_)(local.first,local.second);
			if(fxy < m){
				m = fxy;
				bx = local.first;
				by = local.second;
			}
		}
	return std::make_pair(bx,by);
}

template<typename FP>
std::pair<FP,FP> Maximizer2D<FP>::findNearLocalMaximum(FP x, FP y, FP xi, FP xf, FP yi, FP yf){
	FP H[2][2], grad[2];
	//printf("Vai começar\n x:%.8f y:%.8f f:%.8f\n",x,y,(*F_)(x,y));
	for(int iter = 1; iter<10;iter++){
		H[0][0] = (*Fxx_)(x,y);
		H[0][1] = H[1][0] = (*Fxy_)(x,y);
		H[1][1] = (*Fyy_)(x,y);
		grad[0] = -(*Fx_)(x,y);
		grad[1] = -(*Fy_)(x,y);
		FP dx, dy;
		//printf("%.8f   %.8f = %.8f\n%.8f   %.8f = %.8f\n",H[0][0],H[0][1],grad[0],H[1][0],H[1][1],grad[1]);
		
		if(!solve2x2b(H,grad,dx,dy)){
			//printf("BUM\n");
			dx = grad[0];
			dy = grad[1];
		}
		else {
			//printf("x:%.8f y:%.8f f:%.8f fx:%.8f fy:%.8f dx:%.8f dy:%.8f\n",x,y,(*F_)(x,y), (*Fx_)(x,y), (*Fy_)(x,y), dx,dy);
		}
		//FP norm = sqrt(dx*dx + dy*dy);
		//x = x + 0.0000001*(dx/norm); 
		//y = y + 0.0000001*(dy/norm);
		//x += dx;
		//y += dy;
		DirectionalFunctor<FP> df(*oriF_,x,y,dx,dy);
		FP l = 0.0, r= (xf-xi)/fabs(dx);           // preguiça pura
		for(int i=0;i<50;i++){
			FP m = 0.5*(l+r);
			if( x+m*dx>=xi && x+m*dx<=xf)
				l=m;
			else r=m;
		}
		FP L = l;
		l = 0.0, r= (yf-yi)/fabs(dy);           // preguiça pura
		for(int i=0;i<50;i++){
			FP m = 0.5*(l+r);
			if( y+m*dy>=yi && y+m*dy<=yf)
				l=m;
			else r=m;
		}
		if(l<L)
			L = l; 
		Maximizer<FP> m(df);
		
		FP d = m.findMaximum(0.0,L, 1e-7,1e-9);
		//printf("x:%.8f y:%.8f f:%.8f fx:%.8f fy:%.8f dx:%.8f dy:%.8f\n",x,y,(*F_)(x,y), (*Fx_)(x,y), (*Fy_)(x,y), dx,dy);
		//printf("L:%.8f d:%.8f\n",L,d);
		x = x + d*dx;
		y = y + d*dy;
		//printf("x:%.8f y:%.8f f:%.8f fx:%.8f fy:%.8f dx:%.8f dy:%.8f\n",x,y,(*F_)(x,y), (*Fx_)(x,y), (*Fy_)(x,y), dx,dy);
	}
	
	return std::make_pair(x,y);
}


template<typename FP>
bool Maximizer2D<FP>::solve2x2a(FP a[2][2], FP b[2], FP &x, FP &y){
  if(a[0][0] == 0.0 && a[1][0] == 0.0)
    return false;
  
  if(fabs(a[1][0]) > fabs(a[0][0])){
    std::swap(a[0][0],a[1][0]);
    std::swap(a[0][1],a[1][1]);
    std::swap(b[0],b[1]);
  }

  FP d = -a[1][0]/a[0][0];
  if(a[1][1] + d*a[0][1] == 0.0)
    return false;
  y = (b[1] + d*b[0])/(a[1][1] + d*a[0][1]);
  x = (b[0] -  a[0][1]*y)/a[0][0];

  return true;
}



template<typename FP>
bool Maximizer2D<FP>::solve2x2b(FP a[2][2], FP b[2], FP &x, FP &y){
  if(a[0][0] <= 0.0 || a[0][0]*a[1][1] - a[0][1]*a[1][0] <= 0.0)
    return false;
  
  bool swapped= false;
  if(fabs(a[1][1]) > fabs(a[0][0])){
    std::swap(a[0][0],a[1][1]);
    swapped = true;
  }

  FP d = -a[1][0]/a[0][0];
  if(a[1][1] + d*a[0][1] == 0.0)
    return false;
  y = (b[1] + d*b[0])/(a[1][1] + d*a[0][1]);
  x = (b[0] -  a[0][1]*y)/a[0][0];
	if(swapped) std::swap(x,y);
  return true;
}

