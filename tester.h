/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _TESTER_H_
#define _TESTER_H_

#include "test.h"
#include <memory>
#include <vector>
#include <utility>
#include <vector>
#include "logger.h"

namespace StoppingTimes{ namespace Testing{

class Tester {

  public:
    void runAll(Logger * logger);
    void loadAll(const char* path);
    void add(Test* t);
    ~Tester();
  
  protected:

  private:
    std::vector< std::unique_ptr<Test> > tests_;
    
};

}}

#endif // _TESTER_H_

