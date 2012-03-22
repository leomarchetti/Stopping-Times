/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include "test.h"
#include <cmath>
#include "logger.h"

namespace StoppingTimes{ namespace Testing{

Test::Test(int id){
  id_ = id;
  loaded_ = false;
  type_ = "";
}

Test::~Test(){}

bool Test::load(const char* path){
  return false;
}

void Test::run(Logger *logger){
  ;
}

bool Test::assertEqual(double x, double y, double eps)
{
  return fabs(x-y) < eps;
}

}}
