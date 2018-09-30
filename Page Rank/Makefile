CXX = g++
CPPFLAGS = -g -Wall -std=c++11

crawler: crawler.cpp crawl_webpages.o
	$(CXX) $(CPPFLAGS) $^ -o $@
crawl_webpages.o: crawl_webpages.cpp crawl_webpages.h
	$(CXX) $(CPPFLAGS) -c $< -o $@


search: search.cpp webpage.o webstorage.o
	$(CXX) $(CPPFLAGS) $^ -o $@

webpage.o: webpage.cpp webpage.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

webstorage.o: webstorage.cpp webstorage.h qsort.h setutility.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f search webstorage.o webpage.o
	rm -f crawler crawl_webpages.o