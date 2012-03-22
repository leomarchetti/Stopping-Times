/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/


#include <sstream>
#include <cstdio>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "test-de-solver.h"
#include "de-solver.h"
#include "logger.h"
#include "test-poly.h"
using namespace std;

namespace StoppingTimes{ namespace Testing{

TestDESolver::TestDESolver(int id) : Test(id)
{
  type_ = "DE-Solver";
}

TestDESolver::~TestDESolver() {
  delete(eq_);
}

bool TestDESolver::load(const char* path){
  stringstream ss;
  string id;
  ss << id_;
  ss >> id;
  FILE * testIn = fopen( ((string)path +id+ ".tst").c_str(),"r");
  if(testIn == false) return false;
  double rho;
  
  vector<double> coef;
  int n;
  if(fscanf(testIn, " mu = %d", &n)!=1) return false;
  for(int i=0;i<n;i++){
    double c;
    if(fscanf(testIn, " %lf", &c)!=1) return false;
    coef.push_back(c);
  }
  muPoly_ = TestPoly(coef);
  
  coef.clear();
  if(fscanf(testIn, " sigma = %d", &n)!=1) return false;
  for(int i=0;i<n;i++){
    double c;
    if(fscanf(testIn, " %lf", &c)!=1) return false;
    coef.push_back(c);
  }
  sigmaPoly_ = TestPoly(coef);
  
  if(fscanf(testIn, " rho = %lf", &rho)!=1) return false;
  if(fscanf(testIn, " x = %lf", &xf_)!=1) return false;
  if(fscanf(testIn, " f0 = %lf", &f0_)!=1) return false;
  if(fscanf(testIn, " df0 = %lf", &df0_)!=1) return false;
  if(fscanf(testIn, " numberOfSteps = %d", &numberOfSteps_)!=1) return false;
  if(fscanf(testIn, " expectedResult = %lf", &expectedResult_)!=1) return false;
  
  eq_ = new SDE<double>( boost::bind(&TestPoly::evaluate, &muPoly_, _1) ,
                         boost::bind(&TestPoly::evaluate, &sigmaPoly_, _1), rho);
                         
  ddf_ = eq_->getSecondDerivative();
  return loaded_ = true;
}

void TestDESolver::run(Logger *logger){
  if(loaded_ == false)
    logger->notLoaded(id_, type_);
  else{
    DESolver<double> s;
    double r = s.solve(ddf_, xf_,f0_,df0_,numberOfSteps_);
    if(assertEqual(r,expectedResult_, 1e-8))
      logger->passed(id_, type_);
    else logger->failed(id_, type_, expectedResult_, r);
  }
}

}}
