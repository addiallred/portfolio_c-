#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
//change all of these to templates
template <class T>
//unioning together all of the webpages that have at least one word in
// common with the words
std::set<T> union_webpages(std::set<T> partial_webpages, std::set<T>
 resulting_webpages)
{
	//getting an iterator to point at the begining of the 
	typename std::set<T>::iterator it;
	it = partial_webpages.begin();
	//iterating over all of the new webpages we got from searching for
	// a word in the map
	//and returning a set
	for(it = partial_webpages.begin(); it != partial_webpages.end(); it++)
	{
		//inserting the name of the webpage into the results
		resulting_webpages.insert(*it);
	}
	//returning the results
	return resulting_webpages;
};
//intersect webpages which will only allow for our returning webpage
// to contain all of the webpages that
//contains all of the words that we want to see in the webpage
template <class T>
std::set<T> intersect_webpages(std::set<T> partial_webpages, std::set<T>
 resulting_webpages)
{
	//getting an iterator to iterate over all of the webpages that we retrieved
	//from a single word call
	typename std::set<T>::iterator it;
	it = partial_webpages.begin();
	//creating the temp webpages which will return the resulting webpages with
	//all words desired in the webpage
	std::set<T> temp_webpage_set;
	//if we haven't inserted anything into the resulting webpage set yet
	// have it be equal
	//to the partial webpage we passed in
	if(resulting_webpages.size() == 0)
	{
		temp_webpage_set = partial_webpages;
	}
	//if it isn't empty
	else
	{
		//create an iterator to iterate over the current resulting webpages
		typename std::set<T>::iterator it2;
		it2 = resulting_webpages.begin();
		//while we are not at the end of either of the sets
		while(it != partial_webpages.end() && it2 != resulting_webpages.end())
		{
			//if the word in partial webpages we are on is the same as the
			// word we are on for 
			//resulting webpages
			if(*it == *it2)
			{
				
				//insert the webpage into the temp webpage that has the new
				// intersection
				temp_webpage_set.insert(*it);  
				//increase the iterators so we are looking at the next item in the set
				it++;
				it2++;
			}
			//if the first webpage is less than that of the second webpage name
			else if(*it < *it2)
			{
				//if the first iteratoris not at the end of the set
				if(it != partial_webpages.end())
				{
					//increase the iterator
					it++;
				}
			}
			//if the first webpage is greater than that of the first webpage name
			else if(*it > *it2 && it2 != resulting_webpages.end())
			{
				//increases it iterator
				it2++;
			}
		}
	}
	//return the new intersected webpage
	return temp_webpage_set;
};
