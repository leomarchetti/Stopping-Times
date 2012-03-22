/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _TEST_MAXIMIZER_H_
#define _TEST_MAXIMIZER_H_

#include "maximizer.h"
#include "test.h"
#include "test-poly.h"
#include "logger.h"
#include <boost/function.hpp>

namespace StoppingTimes{ namespace Testing{

class TestMaximizer: public Test {

  public:
    TestMaximizer(int id);
    bool load(const char* path);
    void run(Logger * logger);
    ~TestMaximizer();

  protected:

  private:
    double a_;
    double b_;
    double relTol_;
    double absTol_;
    boost::function<double(double)> f_;
    double expectedResult_;
    TestPoly *fPoly_;
};

}}

#endif // _TEST_DE_MAXIMIZER_H_

