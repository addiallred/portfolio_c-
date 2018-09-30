CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: search

search: search.cpp webpage.o webstorage.o
	$(CXX) $(CPPFLAGS) $^ -o $@
	
webpage.o: webpage.cpp webpage.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

webstorage.o: webstorage.cpp webstorage.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f search webstorage.o webpage.o