/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include "tester.h"
using namespace std;

namespace StoppingTimes{ namespace Testing{

Tester::~Tester(){
  tests_.clear();
}

void Tester::add(Test *t)
{
  tests_.push_back(unique_ptr<Test>(t));
}

void Tester::loadAll(const char* path)
{
  for(auto it = tests_.cbegin(), end = tests_.cend(); it != end; ++it)
  {
    (*it)->load(path);
  }
}

void Tester::runAll(Logger* logger){
  auto end = tests_.cend();
  for(auto it = tests_.cbegin(); it != end; ++it)
  {
    (*it)->run(logger);
  }
}

}}
