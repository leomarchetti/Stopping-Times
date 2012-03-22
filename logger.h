/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include<cstdio>
#include<string>

namespace StoppingTimes{ namespace Testing{

class Logger {

  public:
    Logger();
    Logger(const char * out);
    void notLoaded(int id, std::string & type);
    void failed(int id, std::string & type);
    void failed(int id, std::string & type, double exp, double rec);
    void passed(int id, std::string & type);
    ~Logger();
  
  protected:
  
  private:
    FILE * out_;

};

}}

#endif // _LOGGER_H_

