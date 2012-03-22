/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _TEST_H_
#define _TEST_H_

#include "logger.h"
#include<string>

namespace StoppingTimes{ namespace Testing{

class Test {

  public:
    Test(int id);
    virtual ~Test();
    virtual bool load(const char* path);
    virtual void run(Logger * logger);
    
  protected:
    int id_;
    bool loaded_;
    std::string type_;
    static bool assertEqual(double a, double b, double eps);

  private:
  
};

}}

#endif // _TEST_H_
