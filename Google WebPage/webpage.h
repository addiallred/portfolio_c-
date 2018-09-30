#include <iostream>
#include <string>
#include <set>
#include <vector>
//creating a class called webpage which will store the contents
//of an entire webpage
class WebPage{
public:
	//constructor
	WebPage();
	//desctructor
	~WebPage();
	//takes in a word, this will insert a word into the compile string
	//to create the entire contents of the webpage excluding the links
	void set_word(const std::string& word);
	//returing the string of all unparsed words in the webpage stored in
	//compile string
	std::string get_word() const;
	//inserting into the webpage the words that are parsed
	void insert_web(const std::string& word);
	//inserting links that exist in the webpage into the set
	void insert_link(const std::string& word);
	//returning the set of link_set, which has all of the links
	//in the webpage
	std::set<std::string> link_set_list();
	//returning the set of links_to, which contains all of the
	//webpages that has a link to this webpage
	std::set<std::string> link_to_list();
	//taking in a webpage name that the current webpage exist as a 
	//link it and inserting it into the links_to set
	void set_links_to(const std::string& word);

private:
	//set for all of the parsed words in the webpage
	std::set<std::string> web_set;
	//set for all of the unparsed words in webpage
	std::string compile_string;
	//set for all of the links that the webpage contains
	std::vector<std::string> link_set;
	//set for all of the links that go to the webpage from another
	//webpage
	std::vector<std::string> links_to;
};