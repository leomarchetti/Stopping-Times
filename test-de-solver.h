/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _TEST_DE_SOLVER_H_
#define _TEST_DE_SOLVER_H_

#include "sde.h"
#include "test.h"
#include "test-poly.h"
#include "logger.h"
#include <boost/function.hpp>

namespace StoppingTimes{ namespace Testing{

class TestDESolver: public Test {

  public:
    TestDESolver(int id);
    bool load(const char* path);
    void run(Logger * logger);
    ~TestDESolver();
    
  protected:

  private:
    double xf_;
    double f0_;
    double df0_;
    int numberOfSteps_;
    boost::function<double(double, double, double)> ddf_;
    double expectedResult_;
    TestPoly muPoly_;
    TestPoly sigmaPoly_;
    SDE<double> *eq_;
};

}}

#endif // _TEST_DE_SOLVER_H_

