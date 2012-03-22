/*
 * Stopping Times
 * Copyright (C) Leonardo Marchetti 2011 <leonardomarchetti@gmail.com>
*/

#include "tester.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test-de-solver.h"
#include "test-maximizer.h"
#include "logger.h"

using namespace StoppingTimes;
using namespace StoppingTimes::Testing;

void createTests(Tester *tester);

int main(int argc, char* argv[]){
  if(argc>1){
    Tester *tester = new Tester();
    createTests(tester);
    tester->loadAll(argv[1]);
    
    Logger *logger;
    if(argc>2)
      logger = new Logger(argv[2]);
    else logger = new Logger();
    tester->runAll(logger);
    delete(logger);
    delete(tester);
  }  
  return 0;
}

void createTests(Tester *tester){
  int i=0;
  tester->add(new TestDESolver(++i));
  tester->add(new TestDESolver(++i));
  tester->add(new TestMaximizer(++i));
  tester->add(new TestMaximizer(++i));
  tester->add(new TestMaximizer(++i));
}
