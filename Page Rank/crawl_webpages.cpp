#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "crawl_webpages.h"
#include <fstream>
using namespace std;
//crawl constructor
Crawl_webpages::Crawl_webpages()
{

}
//crawl desctructor
Crawl_webpages::~Crawl_webpages()
{

}
//printing the contents to the file
void Crawl_webpages::print_crawl(ofstream& outfile)
{
	//iterating over the outgoing links and pringing them out
	for(int i = 1; i < int(outgoing_link.size()); i++)
	{
		outfile << outgoing_link[i] << endl;
	}
}
//reading the contents in one webpage
void Crawl_webpages::crawl(string key_word)
{
	//getting the temp webpage by opening it
	ifstream temp_page(key_word.c_str());
	//if we can't open the webpage return
	if(temp_page.fail())
	{
		return;
	}
	//if we already came across the webpage return
	if(outgoing_set.find(key_word) != outgoing_set.end())
	{
		return;
	}
	//push back the keyword we were given into the outgoing link
	outgoing_link.push_back(key_word);
	//insert the keyword into the outgoing set so we can access
	//webpages we already iterated over
	outgoing_set.insert(key_word);
	//while we can open the webpage
	while(!temp_page.fail())
	{
		string temp_line;
		getline(temp_page, temp_line);
		//if when we got the line we didn't fail
		if(!(temp_page.fail()))
		{
			//creating a boolean for if we found the closing square braket
			bool square_brak = false;
			//looking for the front square bracket 
			bool front_square = false;
			//boolean for if we found a (
			bool found_front_brack = false;
			//string for constructing the links
			string link_word;
			//iterating over the word we pulled from the file by each character
			for(int i = 0; i <int(temp_line.length()); i++)
			{
				//getting the temp char that we are going to be looking at
				char temp_char = temp_line[i];
					//if the char is a closing square
				if(temp_char == ']' && front_square)
				{
					//than square brak is true
					square_brak = true;
				}
				//if the char is an opening braket
				else if(temp_char == '[')
				{
					//and we assume it is empty
					front_square = true;
				}
				//if we are at the end of the line and we have a linked word to insert
				if(i+1 == int(temp_line.length()) && link_word.length() > 0)
				{
					//recursviely call on the link that we just found
					crawl(link_word);
					link_word = "";
				}
				//if the char is a parenthise ( and we found a square closing braket
				//right before it, and the ancor is not empty, we know this is valid
				//syntax for a link
				if(temp_char == '(' && square_brak)
				{
					//found a ( that will be the start of a link
					found_front_brack = true;
				}
				//if the char is a ) and there is a corresponding (
				else if(temp_char == ')' && found_front_brack)
				{
					//call crawl on the link word
					crawl(link_word);
					//reset paramaters
					link_word = "";
					found_front_brack = false;
					square_brak = false;
				}
				//if we found a ( and are thus building a linked word
				else if(found_front_brack)
				{
					//add the char to the linked word
					link_word += temp_char;
				}
			}
		}
		//if when we got line it failed
		else
		{
			//break
			break;
		}
	}
	return;
	
}
//read the webpage provided
void Crawl_webpages::read_file(ifstream& input, string file_name)
{
	//if we can not open the webpage
	if(!input.fail())
	{
		//place them into our vector and our set so we know we already came
		//accross this webpage
		outgoing_set.insert(file_name);
		outgoing_link.push_back(file_name);
	}

	//open the input file and make sure that it goesn't fail
	while(!input.fail())
	{
		//create a temp string to retrieve the name of the webpages from 
		//the input
		string temp_string;
		//use getline to get lines in file
		getline(input, temp_string);
		//if getting the line fails, break out of the while loop
		if(input.fail())	
		{
			break;
		}
		//if we can get the line
		else
		{
			//use the function read web to read the contents that exist within 
			//the webpage file itself
			crawl(temp_string);
		}
	}

	return;
}