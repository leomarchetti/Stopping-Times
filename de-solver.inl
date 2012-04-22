/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

template<typename FP>
FP DESolver<FP>::solve(boost::function<FP(FP, FP, FP)> ddf, FP xf, FP f0, FP df0, int n){
  return RungeKutta(ddf, xf, f0, df0, n);
}

template<typename FP>
FP DESolver<FP>::RungeKutta(boost::function<FP(FP, FP, FP)> ddf, FP xf, FP f0, FP df0, int n){
  FP h = xf/n, x= (FP)0.0, f=f0, df=df0;
    for (int i = 0; i < n; i++) {
      FP l1 = h * ddf(x, f, df);
      FP k1 = h * (df);
      FP l2 = h * ddf(x + ((FP)0.5)*h, f + ((FP)0.5)*k1, df + ((FP)0.5)*l1);
      FP k2 = h * (df + ((FP)0.5)*l1);
      FP l3 = h * ddf(x + ((FP)0.5)*h, f + ((FP)0.5)*k2, df + ((FP)0.5)*l2);
      FP k3 = h * (df + ((FP)0.5)*l2);
      FP l4 = h * ddf(x + h, f + k3, df + l3);
      FP k4 = h * (df + l3);
      df += (l1 + ((FP)2)*l2 + ((FP)2)*l3 + l4) / ((FP)6);
      f += (k1 + ((FP)2)*k2 + ((FP)2)*k3 + k4) / ((FP)6);
      x += h;
    }
  return f;
}

