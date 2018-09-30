#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>

//webstorage class, this class will mainly implement all of the executions needed 
//to be done to recieve information from the files, executing the queries, and storing
//a map that has a key of a indivual word and a value of sets of webpages that have the word
//in their webpage
class Crawl_webpages{
public:
	//webstorage constructor and destructor
	Crawl_webpages();
	~Crawl_webpages();
	//function read file, this reads in the input of all the webpages we are to over look
	void crawl(std::string word);
	//function to print out the webpages
	void print_crawl(std::ofstream& outfile);
	//function read webpages reads all of the webpages that we are supposed to read and stores all of the
	//content in the webpage class and in the map
	void read_file(std::ifstream& wfile, std::string file_name);

private:
	//vector to store the correct ordering of the outgoing links
	std::vector<std::string> outgoing_link;
	//set to store the outgoing links we already came accross in
	std::set<std::string> outgoing_set;
};