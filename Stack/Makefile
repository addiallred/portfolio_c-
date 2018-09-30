CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: stringparser

stringparser: stringparser.cpp lliststr.o stackstr.o
	$(CXX) $(CPPFLAGS) $^  -o $@

lliststr.o: lliststr.cpp lliststr.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

stackstr.o: stackstr.cpp stackstr.h
	$(CXX) $(CPPFLAGS) -c $< -o $@