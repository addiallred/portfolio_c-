#include <iostream>
#include <vector>

class Crawler_storage()
{
public:
	Crawler_storage();
	~Crawler_storage();
	//inserting links that exist in the webpage into the vector
	void insert_link(const std::string& word);
	//returning the vector for the webpage
	vector<string> 
private:
	std::vector<std::string> links_to;
	
}