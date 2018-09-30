#include "webpage.h"
#include <iostream>
#include <set>
using namespace std;
//defining the constructor
WebPage::WebPage()
{
	
}
//defining the destructor
WebPage::~WebPage()
{

}
//deffining set word
void WebPage::set_word(const string& new_word)
{
	//inserting the word passed in to the string of the whole webpage
	//file unparsed
	compile_string = compile_string + new_word;
}

//defining get word
string WebPage::get_word() const
{
	//this will return the string compile string which is the whole webpage unparsed
	return compile_string;
}

//defining insert_web
void WebPage::insert_web(const string& new_word)
{
	//takes the new word and inserts it into the web set which consist of
	//all parsed words
	web_set.insert(new_word);
}
//defining insert_link
void WebPage::insert_link(const string& new_word)
{
	//takes the new word and inserts it into the link set which consist 
	//of all the links within a webpage
	link_set.insert(new_word);
}
//defining link_set_list
set<string> WebPage::link_set_list()
{
	//returns the set of links that exist within the webpage
	return link_set;
}
//deffining set_links_to
void WebPage::set_links_to(const string& word)
{
	//insert the word passed in to the set of links to which other webpages
	//have to the current webpage
	links_to.insert(word);
}
//defining link_to_list
set<string> WebPage::link_to_list()
{
	//returning the set of links which has a list of other webpages to which
	//the current webpage has a link in
	return links_to;
}