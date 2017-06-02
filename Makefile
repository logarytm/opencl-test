CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++14 -g
LIBS := $(shell pkg-config OpenCL --libs)

main: main.cc pch.hh.gch
	$(CXX) $(CXXFLAGS) main.cc -o $@ $(LIBS)

pch.hh.gch: pch.hh
	$(CXX) -x c++-header -o $@ -c main.cc
