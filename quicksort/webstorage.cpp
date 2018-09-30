#include "setutility.h"
#include "webstorage.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
//creating the webstorage constructor
WebStorage::WebStorage()
{

}
//creating the webstorage destructor
WebStorage::~WebStorage()
{
	//getting an iterator to delete the dynampically allocated webpages
	map<string, WebPage*>::iterator it;
	//delete all of the webpage class that was dynamically allocated
	for(it = map_search.begin(); it != map_search.end(); it++)
	{
		delete it->second;
	}
}
//defining the construct map, which constructs a map with keys being words in
//the webpages and the value being a set of all the webpages that contain the 
//word
void WebStorage::construct_map(const string word, string webpages)
{
	//checking if the word isn't already in the map
	if(words_to_webpages.find(word) == words_to_webpages.end())
	{
		//creating a temporary set that we will push the name of the webpage into
		set<string> temp_set;
		temp_set.insert(webpages);
		//creating a new pair in a map with the key being the word, and the value 
		//being the set of webpages that contain the word
		words_to_webpages[word] = temp_set;
	}
	//if the word is already in the map
	else if(words_to_webpages.find(word) != words_to_webpages.end())
	{
		//if we search through the word set of wepages and don't find the current 
		//webpage we are looking to insert 
		if(words_to_webpages[word].find(webpages) == words_to_webpages[word].end())
		{
			words_to_webpages[word].insert(webpages);
		}
	}
	return;
}
//reading the contents in one webpage
void WebStorage::read_web(ifstream& wfile, string key_word)
{
	//dynamically allocate a webpage class
	WebPage* temp_web = new WebPage();
	//create a set to store the whole unedited webpage in
	set<string> whole_text_temp;
	//create a string to store the whole unedited webpage in
	string final_print;
	//creating a boolean for if we find (
	bool closing_brack = false;
	while(!wfile.fail())
	{
		string temp_line;
		getline(wfile, temp_line);
		//if when we got the line we didn't fail
		if(!(wfile.fail()))
		{
			//insert the templine into the whole text set
			whole_text_temp.insert(temp_line);
			for(int i = 0; i < int(temp_line.length()); i++)
			{
			//if the char we are on is not a opening bracket, or we have not came
			//across an opening bracket 
				if(temp_line[i] != '(' && !closing_brack)
				{
					//add the char to the word we are building
					final_print = final_print + temp_line[i];
				}
				//if we find the closing bracket
				else if(temp_line[i] == ')')
				{
					//we no longer need to search for a closing bracket
					//set it equal to false
					closing_brack = false;
					if(temp_line[i + 1] != ' ')
					{
						final_print += " ";
					}
				}
				//if we find an opening bracket
				else if(temp_line[i]== '(')
				{
					//we need to find the closing bracket so we aren't
					//adding words that are a link to the final word
					closing_brack = true;
				}
			}
			//add an endline to the string so prints out properly
			final_print = final_print + '\n';
			//creating a boolean for if we found the closing square braket
			bool square_brak = false;
			//looking for the front square bracket 
			bool front_square = false;
			//string that we will construct words with
			string build_word;
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
					//insert the linked word into the temporary webpage
					temp_web->insert_link(link_word);
					//reset the linked word so it is empty
					link_word = "";
				}
				//if the char isn't a letter or a number and the build word is greater than 0
				//meaining that we have built the word
				if((!isalnum(temp_char) && build_word.length() > 0) || i+1 == int(temp_line.length()))
				{
					
					if(isalnum(temp_char))
					{
						build_word += temp_char;
					}
					//insert the built word into the web set storing all of the parsed
					//words in the webpage
					temp_web->insert_web(build_word);
					//passing in the word we just build and the webpage we are on
					//to create the key to webpage map
					construct_map(build_word, key_word);
					//reset build word
					build_word = "";
				}
				//if the char is and empty string and if we have not encoundered a patehthise ( or
				//the index is the size of the word, meaining it is the last char in the word
				else if((temp_char == ' ' && !found_front_brack) || (i == int(temp_line.length())))
				{
					//insert the built word into the set
					temp_web->insert_web(build_word);
					//passing in the word we just build and the webpage we are on
					//to create the key to webpage map
					construct_map(build_word, key_word);
					//reset build word
					build_word = "";
				}
				//if the char is a parenthise ( and we found a square closing braket
				//right before it, and the ancor is not empty, we know this is valid
				//syntax for a link
				else if(temp_char == '(' && square_brak)
				{
					//found a ( that will be the start of a link
					found_front_brack = true;
				}
				//if the char is a ) and there is a corresponding (
				else if(temp_char == ')' && found_front_brack)
				{
					//insert the word we constructed into the linked words 
					//since this word is a link
					temp_web->insert_link(link_word);
					//reset values
					link_word= "";
					found_front_brack = false;
					square_brak = false;
				}
				//if we have not found a front braket for a link
				else if(!found_front_brack)
				{
					//get an int to get if the char is a number
					int value_char = int(temp_char);
					if(isalnum(value_char))
					{
						//add the char to the word we are building
						build_word += temp_char;
					}
					//if it isn't a letter or number
					else if(build_word.size() != 0 && temp_char != '[')
					{
						//insert it into the web set of all parsedwords
						temp_web->insert_web(build_word);
						//passing in the word we just build and the webpage we are on
						//to create the key to webpage map
						construct_map(build_word, key_word);
						//reset the build word
						build_word = "";
					}
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
	//inserting the string created that contains all unparsed words
	temp_web->set_word(final_print);
	//creating the map of a string by the webpage name and the value a webpage class
	//that contains the information with in the webpage
	map_search[key_word] = temp_web;
	return;
}
//creataing the function to read the contents that exist within the webpage
void WebStorage::read_file(ifstream& infile)
{
	//open the input file and make sure that it goesn't fail
	while(!infile.fail())
	{
		//create a temp string to retrieve the name of the webpages from 
		//the input
		string temp_string;
		//use getline to get lines in file
		getline(infile, temp_string);
		//if getting the line fails, break out of the while loop
		if(infile.fail())	
		{
			break;
		}
		//if we can get the line
		else
		{
			//open the webpage we just pulled from file
			ifstream input(temp_string.c_str());
			//use the function read web to read the contents that exist within 
			//the webpage file itself
			read_web(input, temp_string);
		}
	}
	return;
}
//making all of the incoming connections based off of outgoing links
void WebStorage::link_to()
{
	//get an iterator for the webpage
	map<string, WebPage*>::iterator it;
	//iterate over the map to access every webpage in the map
	for(it = map_search.begin(); it != map_search.end(); it++)
	{
		//get a string of the maps name 
		string map_name = it->first;
		//create a temporary set to store all of the outgoing
		//links in
		set<string> temp_links;
		//get the outgoing links from the current webpage we are on
		temp_links = it->second->link_set_list();
		//create an iterator
		set<string>::iterator it2;
		//iterate over all of the values in the outgoing links
		for(it2 = temp_links.begin(); it2 != temp_links.end(); it2++)
		{
			//if the outgoing link is in the map
			if(map_search.find(*it2) != map_search.end())
			{
				//for that outgoing link name, for its incoming link
				//insert into it set the name of the map that 
				//contains the link to the webpage
				map_search[*it2]->set_links_to(map_name);
			}
		}
	}
	return;
}
//reading in the contents from the query file
void WebStorage::query(ifstream& query_file, ofstream& out_file)
{
	//reading the query file
	while(!query_file.fail())
	{
		//getting a set to put the words in from the file
		set<string> find_words;
		//getting a single line of the file
		string read_line;
		getline(query_file, read_line);
		//making sure that when we got the line that we didn't fail
		if(!query_file.fail())
		{
			string new_word;
			//create a temp word
			stringstream ss(read_line);
			bool not_empty;
			while(ss >> new_word)
			{
				find_words.insert(new_word);
				not_empty = true;
			}
			
			//calling execute query on the command we just found if the query isn't empty
			if(not_empty)
			{
				execute_query(find_words, out_file);
			}
			else
			{
				out_file << "Invalid query" << endl;
			}
		}

	}
}
//executing all of the commands we found in the query file
void WebStorage::execute_query(set<string>& find_words, ofstream& out_file)
{
	//getting an iterator
	set<string>::iterator it;
	//setting the iterator to be at the beginning of the set
	it = find_words.begin();
	//getting an iterator for the map and setting it equal
	//to the start of the map
	map<string, WebPage*>::iterator it2;
	it2 = map_search.begin();
	//getting the comman action from the words from find_words
	//and then removing it from the set since it is not a word
	//we should search for if the size of findwords is greater than
	//2
	string command = *it;
	//setting it to the begining again since we erased what it was originally pointing to
	find_words.erase(it);
	//if the size is gretter than 1
	if(find_words.size() >= 1)
	{	
		//redefine the iterator since we removed the beginning 
		it = find_words.begin();
		//command is and
		if(command == "AND")
		{
			//creating a set to store all of the webpages in 
			set<string> word_and;
			//function for the number of webpages there are					
			int web_with_word = 0;
			//getting the intersecting words by calling the function and passing in
			//all of the words that we want to find
			word_and = intersect_string(find_words);
			//getting the size of how many webpages are in the set
			web_with_word = word_and.size();
			//getting an iterator to iterate over all of the webpages that contain
			//all words
			set<string>::iterator it_and;
			//printing out the number of webpages
			out_file << web_with_word << endl;
			//iterating over the resulting webpages and printing them out
			for(it_and = word_and.begin(); it_and != word_and.end(); it_and++)
			{
				out_file << *it_and << endl;
			}
		}

		//if the command is or
		else if(command == "OR")
		{
			//creating a set for all of the webpages that have at least one word
			set<string> word_or;
			int web_with_word = 0;
			word_or = union_string(find_words);
			//number of words in the union webpage
			web_with_word = word_or.size();
			//printing out the number of webpages we have from the union
			out_file << web_with_word << endl;
			//gettin an iterator to iterate over all of the webapges we have
			// and then print the webpage out
			set<string>::iterator it_or;
			for(it_or = word_or.begin(); it_or != word_or.end(); it_or++)
			{
				out_file << *it_or << endl;
			}		
		}
		//if the command is print
		else if(command == "PRINT")
		{
			//check that the website name provided is in the map
			if(map_search.find(*it) != map_search.end())
			{
			//create a temp print string
				string temp_print; 
				//get the string to print from the webclass function of the 
				//webpage weare on
				temp_print = map_search.find(*it)->second->get_word();
				//print out the webpage name
				out_file << *it << endl;
				//print out the string
				out_file << temp_print;
			}
			//if the webpage isn't in the map based off of the keys
			else
			{
				out_file << "Invalid query" << endl;
			}
		}
		//if the command is incoming
		else if(command == "INCOMING")
		{
			//go through the map and check that the webpage is in the map
			if(map_search.find(*it) != map_search.end())
			{
				//create a set to store the incoming webpages in
				set<string> temp_incoming;
				//get the incoming webpages using the inputed webpage
				temp_incoming = map_search.find(*it)->second->link_to_list();
				//creating an iterator
				set<string>::iterator it;
				//getting the number of incoming webpages for one webpage and
				//printing it out
				int size = temp_incoming.size();
				out_file << size << endl;
				//iterating through the incoming webpages and printing them out
				for(it = temp_incoming.begin(); it != temp_incoming.end(); it++)
				{
					out_file << *it << endl;
				}				
			}
			//if there are no incoming webpages to another webpage
			else
			{
				out_file << "Invalid query" << endl;
			}
		}
		//if the command is outgoing
		else if(command == "OUTGOING")
		{					
			//check that the webpage we are looking for is in the map
			if(map_search.find(*it) != map_search.end())
			{
				//createa set to store the outgoing webpages of the webpage we are
				//in
				set<string> temp_outgoing;
				//get the set of the outgoing webpages from the webpage function
				//that returns the outgoing webpages of a specific webpage
				temp_outgoing = map_search.find(*it)->second->link_set_list();
				//create an iterator
				set<string>::iterator it3;
				//geting the number of outgoing files from a webpage and printing it out
				int size = temp_outgoing.size();
				out_file << size << endl;
				//iterate over the retrieved outgoing webpages and print them
				for(it3 = temp_outgoing.begin(); it3 != temp_outgoing.end(); it3++)
				{
					out_file << *it3 << endl;
				}
			}
			//if the webpage we are trying to look up is not in the webpage map
			else
			{
				out_file << "Invalid query" << endl;
			}
		}
		//if it is none of these commands and there is more than two words
		//in the origiinal line it is invalid
		else 
		{
			out_file << "Invalid query" << endl;
		}
	}
	//if there is only one word in the line we got from the file
	//because when we removed the first it the size of the set is now 0
	else if(find_words.size() == 0)
	{
		//creating a set for the webpages that contain the single word we are looking for
		set<string> webpage_with_word;
		//seeing if the word wearelooking for is in the map
		if(words_to_webpages.find(command) != words_to_webpages.end())
		{
			//getting the webpage with the words from the map
			webpage_with_word = words_to_webpages[command];
			//getting an iterator to iterate over the webpages that have the word
			set<string>::iterator it;
			//getting the number of webpages that contains the word
			int num_webpages = webpage_with_word.size();
			//printing out the number of webpages that contain the word
			out_file << num_webpages << endl;
			//iterating over the set of webpages containg the word and printing them out
			for(it = webpage_with_word.begin(); it != webpage_with_word.end(); it++)
			{
				out_file << *it << endl;
			}
		}
		//if the word is not in the file, print out 0
		else
		{
			out_file << 0 << endl;
		}
	}
}