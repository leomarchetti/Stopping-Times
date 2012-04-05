/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template<typename FP>
Maximizer<FP>::Maximizer() : minusF_(NULL){}

template<typename FP>
Maximizer<FP>::Maximizer(boost::function<FP(FP)> minusF){
  minusF_ = minusF;
}

template<typename FP>
FP Maximizer<FP>::f(FP x){
  return -minusF_(x);
}

template<typename FP>
void Maximizer<FP>::setFunction(boost::function<FP(FP)> minusF){
  minusF_ = minusF;
}

template<typename FP>
FP Maximizer<FP>::findMaximum(FP a, FP b, FP rel_tol, FP abs_tol){
  if(minusF_!=NULL)
    return localMinBrent(a, b, rel_tol, abs_tol);
  return 0.0;
}

template<typename FP>
FP Maximizer<FP>::localMinBrent(FP a, FP b, FP rel_tol, FP abs_tol){
  const FP two_minus_gratio = 0.3819660112501; /* two_minus_gratio = (3-sqrt(5))/2 = 2 - phi */
  FP x, v, w;
  FP fx, fv, fw;
  FP e=0;
  
  v = w = x = a + two_minus_gratio*(b-a);
  fv = fw = fx = f(x);
  while(1){
    FP m = 0.5*(a+b);
    FP tol = rel_tol*fabs(x) + abs_tol;
    FP tol2 = tol + tol;
    FP d = 0;
    FP r = 0, p = 0, q = 0, u = 0;
    if(fabs(x-m) <= tol2 - 0.5*(b-a))
      break;
    if(fabs(e) > tol){
      /* descobre a parabola */
      r = (x-w)*(fx-fv);
      q = (x-v)*(fx-fw);
      p = (x-v)*q - (x-w)*r;
      q = 2*(q-r);
      if(q>0.0) p = -p;
      else q = -q;
      r = e;
      e = d;
    }
    if(fabs(p) < fabs(0.5*q*r) && p < q*(a-x) && p < q*(b-x)){
      /* parabola serviu e sera usada nessa iteracao ("parabolic interpolation") */
      d = p/q;
      u = x+d;
      if( u-a < tol2 || b-u < tol2){ /* nao devemos calcular a funcao em uma abscissa muito proxima de a ou b */
        if(x < m) d = tol;
        else d = -tol;
      }
    }
    else{
      /* parabola nao serviu, entao "golden section" sera usada nessa iteracao */
      if(x < m)
        e = b-x;
      else e = a-x;
      d = two_minus_gratio*e; 
    }
    
    if( fabs(d)<tol){ /* nao devemos calcular a funcao em uma abscissa muito proxima de x*/
      if(d > 0) d = tol;
      else d = -tol;
    }
    u = x + d;
    FP fu = f(u);
    if(fu <= fx){
      if(u<x) 
        b = x;
      else a = x;
      v = w;
      fv = fw;
      w = x;
      fw = fx;
      x = u;
      fx = fu;
    }
    else{
      if(u < x)
        a=u;
      else b = u;
      if(fu <= fw || w == x){
        v = w;  
        fv = fw;
        w = u;
        fw = fu;
      }
      else if( fu <= fv || v==x || v==w){
        v = u;
        fv = fu;
      }
    }  
  }
  return x;
}
