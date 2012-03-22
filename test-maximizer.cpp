/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include <sstream>
#include <cstdio>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "test-maximizer.h"
#include "maximizer.h"
#include "logger.h"
#include "test-poly.h"
using namespace std;

namespace StoppingTimes{ namespace Testing{

TestMaximizer::TestMaximizer(int id) : Test(id)
{
  type_ = "Maximizer";
}

TestMaximizer::~TestMaximizer() {
  delete(fPoly_);
}

bool TestMaximizer::load(const char* path){

  stringstream ss;
  string id;
  ss << id_;
  ss >> id;
  FILE * testIn = fopen( ((string)path +id+ ".tst").c_str(),"r");
  if(testIn == false) return false;
  
  vector<double> coef;
  int n;
  if(fscanf(testIn, " f = %d", &n)!=1) return false;
  for(int i=0;i<n;i++){
    double c;
    if(fscanf(testIn, " %lf", &c)!=1) return false;
    coef.push_back(c);
  }
  fPoly_ = new TestPoly(coef);
  f_ = boost::bind(&TestPoly::evaluate, fPoly_, _1);
  
  if(fscanf(testIn, " a = %lf", &a_)!=1) return false;
  if(fscanf(testIn, " b = %lf", &b_)!=1) return false;
  if(fscanf(testIn, " relTol = %lf", &relTol_)!=1) return false;
  if(fscanf(testIn, " absTol = %lf", &absTol_)!=1) return false;
  if(fscanf(testIn, " expectedResult = %lf", &expectedResult_)!=1) return false;
  
  return loaded_ = true;
}

void TestMaximizer::run(Logger *logger){
  if(loaded_ == false)
    logger->notLoaded(id_, type_);
  else{
    Maximizer<double> m(f_);
    double r = m.findMaximum(a_, b_, relTol_, absTol_);
    if(assertEqual(r,expectedResult_, 1e-8))
      logger->passed(id_, type_);
    else logger->failed(id_,  type_, expectedResult_, r);
  }
}

}}
