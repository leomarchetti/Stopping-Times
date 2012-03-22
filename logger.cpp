/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include "logger.h"
#include <cstdio>
#include <cstring>
using namespace std;

namespace StoppingTimes{ namespace Testing{

Logger::Logger(){
  out_ = stdout;
}

Logger::Logger(const char * outPath){
    out_ = fopen(outPath,"w");
    if(out_ == NULL)
      out_ = stdout;
}

Logger::~Logger(){
  if(out_ != stdout)
    fclose(out_);
}

void Logger::notLoaded(int id, string &type){
  fprintf(out_, "Test %d (%s) = NOT LOADED\n", id, type.c_str());
}

void Logger::failed(int id, string &type){
  fprintf(out_, "Test %d (%s) = FAILED!\n", id, type.c_str());
}

void Logger::failed(int id, string &type, double exp, double rec){
  fprintf(out_, "Test %d (%s) = FAILED! [ expected = %.10f , received = %.10f ]\n", id,type.c_str(), exp, rec);
}

void Logger::passed(int id, string &type){
  fprintf(out_, "Test %d (%s) = PASSED\n", id,type.c_str());
}

}}
