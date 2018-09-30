#include <iostream>
#include <map>
#include <set>
#include <string>
#include "qsort.h"
#include <vector>
#include <fstream>
#include "webpage.h"

//webstorage class, this class will mainly implement all of the executions needed 
//to be done to recieve information from the files, executing the queries, and storing
//a map that has a key of a indivual word and a value of sets of webpages that have the word
//in their webpage
class WebStorage{
public:
	//webstorage constructor and destructor
	WebStorage(double steps_, double probab_);
	~WebStorage();
	//function read file, this reads in the input of all the webpages we are to over look
	void read_file(std::ifstream& infile);
	//function construct map, this constructs the map that has a key of a indivual word and a 
	//value of sets of webpages that have the word in their webpage
	void construct_map(const std::string word, std::string webpages);
	//function read webpages reads all of the webpages that we are supposed to read and stores all of the
	//content in the webpage class and in the map
	void read_web(std::ifstream& wfile, std::string key_word);
	//function links to over looks all of the webpages outgoing webpages from a specific webpage and
	//sets that webpage to be an incoming webpage for the outgoing webpage link it stores
	void link_to();
	//function for getting all of the webpages that store all words that we are trying to query
	std::set<std::string> intersect_string(std::set<std::string>& find_words);
	//looking at the webpages that stores a word and making sure that it stores all of the other words
	//that we want to also have in the webpage
	//std::set<std::string> intersect_webpages(std::set<std::string>& partial_webpages, std::set<std::string>& resulting_webpages);
	//function for getting all of the webpages that stores at least one of the words we are quering
	std::set<std::string> union_string(std::set<std::string>& find_words);
	//combining together all of the webpages that store atleast one of the words that we are quering
	//void union_webpages(std::set<std::string>& partial_webpages,std::set<std::string>& resulting_webpages);
	//reads in all of the information from query file and calls the execute query function
	void query(std::ifstream& query_file, std::ofstream& out_file);
	//executing all of the queries that need to be done based off of the commands passed in 
	//by query and printing them out
	void execute_query(std::set<std::string> &find_words, std::ofstream& out_file, std::string& command);
	//function to compute page_rank
	std::vector<std::string> page_rank(std::set<std::string>& candidate_webpages);
	//function to get all of the candidates of the pages that we found
	std::set<std::string> candidate_pages(std::set<std::string>& found_pages);

private:
	//a map that has a key of a indivual word and a value of sets of webpages that have the word
	//in their webpage, isspecific to webstorage class
	std::map<std::string, std::set<std::string> > words_to_webpages;
	//creating a map with the string being the webpage name as the key, and the 
	//value being a webpage class that corellates to the 
	std::map<std::string,WebPage*> map_search;
	//number of steps for page rank
	double steps;
	//the probability for page rank
	double probability;
};