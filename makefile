CC = g++
CFLAGS = -c -Wall -std=c++0x
LDFLAGS =
SOURCES = main.cpp de-solver.cpp maximizer.cpp maximizer2D.cpp sde.cpp tester.cpp test.cpp logger.cpp\
          test-de-solver.cpp test-poly.cpp test-maximizer.cpp stoppingTimes.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = stoppingTimes

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o *~
	
sclean:
	rm *.o *~ tests/*~ stoppingTimes *.out
