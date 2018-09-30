#include "webstorage.h"
#include "setutility.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//creating the webstorage constructor
//********* you need to make sureyou are reading everything in correctyly
WebStorage::WebStorage(double steps_, double probab_)
{
	steps = steps_;
	probability = probab_;
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
				if(isalpha(temp_char))
				{
					temp_char = tolower(temp_char);
				}
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
					ifstream link(link_word.c_str());
					if(!link.fail())
					{
						//insert the linked word into the temporary webpage
						temp_web->insert_link(link_word);
						//reset the linked word so it is empty
					}
					//reset the link word so it is empty
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
					ifstream link(link_word.c_str());
					if(!link.fail())
					{
						//insert the linked word into the temporary webpage
						temp_web->insert_link(link_word);
						//reset the linked word so it is empty
					}
					//reset the link word so it is empty
					link_word = "";
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
//looking for words in the map based off of the words that we want to query
set<string> WebStorage::union_string(set<string>& find_words)
{
	//getting an iterator to iterate over all of the words that we are to query
	set<string>::iterator it;
	//getting a set to store the resulitng webpages in that have at least one word
	//that we are searchign for
	set<string> resulting_webpages;
	set<string> corrected_final;
	for(it = find_words.begin(); it != find_words.end(); it++)
	{
		string new_word;
		string curr = *it;
		for(int i = 0; i < int(curr.length()); i++)
		{
			char temp_char = curr[i];
			if(isalpha(temp_char))
			{
				temp_char = tolower(temp_char);
			}
			new_word += temp_char;
		}
		corrected_final.insert(new_word);
	}
	//iterating over all of the words passed in by the set from the query search
	for(it = corrected_final.begin(); it != corrected_final.end(); it++)
	{		//looking to see if the word is in any of the webpages by looking if it is a key in
		//the map
		if(words_to_webpages.find(*it) != words_to_webpages.end())
		{

			//getting the resulting webpage by calling union webpage
			resulting_webpages = union_webpages(words_to_webpages[*it], resulting_webpages);
		}
	}
	//return the resulting webpages
	return resulting_webpages;
}
//function to get webpages that contain the words we are looking for and then call
//intersect webpage to get all of the webpages that contain all of the words that we are looking for
set<string> WebStorage::intersect_string(set<string>& find_words)
{
	//creating an iterator to iterate over all of the words we want to search for
	set<string>::iterator it;
	//creating a resulting webpage set that will contain all of the webpages
	//that have all of the words that we are looking for in them
	set<string> resulting_webpages;
	set<string> corrected_final;
	for(it = find_words.begin(); it != find_words.end(); it++)
	{
		string new_word;
		string curr = *it;
		for(int i = 0; i < int(curr.length()); i++)
		{
			char temp_char = curr[i];
			if(isalpha(temp_char))
			{
				temp_char = tolower(temp_char);
			}
			new_word += temp_char;
		}
		corrected_final.insert(new_word);
	}
	//iterating over all of the words that we are to query
	for(it = corrected_final.begin(); it != corrected_final.end(); it++)
	{
		//looking through the map to check if the 
		if(words_to_webpages.find(*it) != words_to_webpages.end())
		{
			//calling the function intersecting webpages pasing in the set of webpages we found
			//from the key value*it, returning the total intersecting webpages
			resulting_webpages = intersect_webpages(words_to_webpages[*it], resulting_webpages);
		}
	}
	//returning the webpages that have all of the webpages that we are looking for
	return resulting_webpages;
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
			//create a temp word
			string word_find;
			//iterate over the line we just pulled from the file
			bool not_empty = false;
			bool command_found = false;
			string command;
			if(read_line.length() > 1)
			{
				for(int i = 0; i < int(read_line.length()); i++)
				{
					char temp_char = read_line[i];
					//if the character we are on isn't an empty character
					//or if the character isn't the last in the line
					if(read_line[i] != ' ' && i+1 != int(read_line.length()))
					{
						//add it to the word we are constructing
						word_find += read_line[i];
						not_empty = true;
					}
					//if the character is a space
					else if(read_line[i] == ' ' && not_empty)
					{
						//insert the word that we constructed into the find_words set
						//and reset the word_find so it is empty and we aren't
						//building on previous words
						find_words.insert(word_find);
						if(!command_found)
						{
							command = word_find;
							command_found = true;
						}
						word_find = "";
					}
					//if the character is the last item in the line
					else if(i+1 == int(read_line.length()) && not_empty)
					{
						//add the character to the word constructed
						word_find += read_line[i];
						if(!command_found)
						{
							command = word_find;
							command_found = true;
						}
						//add the word to the set
						find_words.insert(word_find);
						//reset the word to empty
						word_find = "";
					}
					else if(i+1 == int(read_line.length()))
					{
						if(isalnum(temp_char))
						{
							//add the character to the word constructed
							word_find += temp_char;
							//add the word to the set
							find_words.insert(word_find);
							if(!command_found)
							{
								command = word_find;
								command_found = true;
							}
							//reset the word to empty
							word_find = "";
							not_empty = true;
						}
					}
				}
			}
			else
			{
				char temp_char = read_line[0];
				if(isalnum(temp_char));
				{
					word_find += temp_char;
					find_words.insert(word_find);
					if(!command_found)
					{
						command = word_find;
						command_found = true;
					}
					not_empty = true;
				}
			}
			//calling execute query on the command we just found if the query isn't empty
			if(not_empty)
			{
				execute_query(find_words, out_file, command);
			}
			else
			{
				out_file << "Invalid query" << endl;
			}
		}

	}
}
//function to get all of the candidate of webpages from a search
//on words based off of the found_webpages
set<string> WebStorage::candidate_pages(set<string>& found_pages)
{
	//getting an iterator to iterate over all of the webpages that contain
	//all words
	set<string> candidates;
	//iterator to got through all of the found webpages from query
	set<string>::iterator it;
	for(it = found_pages.begin(); it != found_pages.end(); it++)
	{
		//get a temp incoming set
		set<string> temp_incoming;
		//get all of the incoming webpages to the webpages that we have in our found pages
		//these will all be our candidates
		temp_incoming = map_search.find(*it)->second->link_to_list();
		//itearator to iterate over the candidate pages
		set<string>::iterator it_incoming;
		for(it_incoming = temp_incoming.begin(); it_incoming != temp_incoming.end(); it_incoming++)
		{
			//insert the current value in the temp incoming into the final candidate set
			candidates.insert(*it_incoming);
		}
		//also do it for the outgoing candidates of the webpages that containded the words
		set<string> temp_outgoing;
		temp_outgoing = map_search.find(*it)->second->link_set_list();
		set<string>::iterator it_out;
		//iteratoe over its temporary outgoing
		for(it_out = temp_outgoing.begin(); it_out != temp_outgoing.end(); it_out++)
		{
			//insert it into the candidate set final
			candidates.insert(*it_out);
		}
	}
	//insert all of the pages that were from the found pages into the candidates
	//since these were the original webpages we were oberving
	for(it = found_pages.begin(); it != found_pages.end(); it++)
	{
		candidates.insert(*it);
	}
	//returning the set we just constructed
	return candidates;
}
//executing all of the commands we found in the query file
void WebStorage::execute_query(set<string>& find_words, ofstream& out_file, string& command)
{
	//getting an iterator
	set<string>::iterator it;
	//setting the iterator to be at the beginning of the set
	it = find_words.find(command);
	//getting an iterator for the map and setting it equal
	//to the start of the map
	map<string, WebPage*>::iterator it2;
	it2 = map_search.begin();
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
			//calling candidate pages on the word_and set to alter the candidates that we
			//are looking at to inclue all of the outoging and incoming links of word_and
			word_and = candidate_pages(word_and);
			//getting the vector to storec the ordering in for page rank
			vector<string> word_and_ordering;
			word_and_ordering = page_rank(word_and);
			//getting the size of how many webpages are in the set 
			web_with_word = word_and_ordering.size();
			//printing out the number of webpages
			out_file << web_with_word << endl;
			//iterator to iterate over the resulting candidate pages
			vector<string>::iterator it_and;
			//iterating over the resulting webpages and printing them out
			for(it_and = word_and_ordering.begin(); it_and != word_and_ordering.end(); it_and++)
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
			//taking the union of all of hte webpages with the desired word
			word_or = union_string(find_words);
			set<string>::iterator it;
 			//getting all of the possible candidates for word_or
			word_or = candidate_pages(word_or);
			//vector to store the results from page rank in
			vector<string> word_or_ordering;
			word_or_ordering = page_rank(word_or);
			//number of words in the union webpage
			web_with_word = word_or_ordering.size();
			//printing out the number of webpages we have from the union
			out_file << web_with_word << endl;
			//gettin an iterator to iterate over all of the webapges we have
			// and then print the webpage out
			vector<string>::iterator it_or;
			for(it_or = word_or_ordering.begin(); it_or != word_or_ordering.end(); it_or++)
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
		for(int i = 0; i < int(command.length()); i++)
		{
			if(isalpha(command[i]))
			{
				command[i] = tolower(command[i]);
			}
		}
		//seeing if the word wearelooking for is in the map
		if(words_to_webpages.find(command) != words_to_webpages.end())
		{
			//getting the webpage with the words from the map
			webpage_with_word = words_to_webpages[command];
			//getting all of the candidates for the webpage
			webpage_with_word = candidate_pages(webpage_with_word);
			//vector to store results from page rank in
			vector<string> webpage_sorted;
			webpage_sorted = page_rank(webpage_with_word);
			//getting an iterator to iterate over the webpages that have the word
			vector<string>::iterator it;
			//getting the number of webpages that contains the word
			int num_webpages = webpage_sorted.size();
			//printing out the number of webpages that contain the word
			out_file << num_webpages << endl;
			//iterating over the set of webpages containg the word and printing them out
			for(it = webpage_sorted.begin(); it != webpage_sorted.end(); it++)
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

//page rank function
vector<string> WebStorage::page_rank(set<string>& candidate_webpages)
{
	//getting an iterator to go over all of the candidates
	set<string>::iterator it;
	//map to store all to store all of the webpage candidates in and their 
	//outgoing webpages
	set<string>::iterator it4;
	for(it4 = candidate_webpages.begin(); it4 != candidate_webpages.end(); it4++)
	{
		//if we don't find the candidate in the map
		if(map_search.find(*it4) == map_search.end())
		{
			//if we can get the input file and we can open it
			ifstream input((*it4).c_str());
			if(!input.fail())
			{
				//call read webpage on the new webpage
				string temp = *it4;
				read_web(input, temp);
			}
			
		}
	}
	//call link to to like all of hte webpages to their corresponing incoming and 
	//outgoing webpages
	link_to();
	//map for the outgoing and ingoing candidates
	map<string, set<string> > candidate_outgoing;
	map<string, set<string> > candidate_incoming;
	//iterating over all of the candidate webpages
	for(it = candidate_webpages.begin(); it != candidate_webpages.end(); it++)
	{
		//get a temp outgoing and temp incoming set
		set<string> temp_outgoing;
		set<string> temp_incoming;
		//search the mapp to find the webpage
		if(map_search.find(*it) != map_search.end())
		{
			//get the temp outgoing webpages for the specific webpages
			temp_outgoing = map_search.find(*it)->second->link_set_list();
			//add a link to the webpage itself
			temp_outgoing.insert(*it);
			set<string>::iterator it55;
			//intersect the webpages to make sure that we only are 
			//using webpages that are in our candidate webpages
			temp_outgoing = intersect_webpages(temp_outgoing, candidate_webpages);
			//candidate at the webpage is equal to the temp outgoing webpages
			//found
			candidate_outgoing[*it] = temp_outgoing;
		}
		//search the map to find the webpage
		if(map_search.find(*it) != map_search.end())
		{
			//get a temp incoming webpage from trying to find it in the map and returning
			//the incoming of that webpage
			temp_incoming = map_search.find(*it)->second->link_to_list();
			//insert a self loop of the webpage
			temp_incoming.insert(*it);
			set<string>::iterator it55;
			//intersect the webpages so that we don't have overlaping webpages that
			//aren't in the dcandidate webpages
			temp_incoming = intersect_webpages(temp_incoming, candidate_webpages);
			//in the incoming map, set the webpage to the temp incoming we found
			candidate_incoming[*it] = temp_incoming;
		}
	}
	//getting the number of verticies that we have in our candidates
	double n = candidate_webpages.size();
	//map to store the ranking list in for all of the webpages at specific
	//iterators
	map<string, vector<double> > ranking_list;
	//get an iterator for the candidate webpages
	set<string>::iterator it5;
	//for all of he candidates in the webpage
	for(it5 = candidate_webpages.begin(); it5 != candidate_webpages.end(); it5++)
	{
		//temp probability is 1/n since this is the begining probability
		double temp_probability = 1/n;
		//get a vector for the temp listing to store all of the 
		//calculated probabilities in
		vector<double> temp_listing;
		//push the calculated temp probability into teh tepm_listtin
		temp_listing.push_back(temp_probability);
		//create the map with the webpage going to its corresponding
		//calculated probabilities
		ranking_list[*it5] = temp_listing;
	}
	//getting a vector to store the resulting rankings in
	vector<double> resulting_ranking;
	//map that will store the calculate probability and will have a corresponding
	//vector that stores all of the webpages with it
	map<double, vector<string> > ranking_pairing;
	//iterating over all of the webpages to calulcate the probability based off of how'
	//many times it stated to calculate steps from the file
	for(int i = 1; i < steps+1; i++)
	{
		//geting an iterator for the map
		map<string, vector<double> >::iterator it6;
		//iterating over the ranking list
		for(it6 = ranking_list.begin(); it6 != ranking_list.end(); it6++)
		{
			//get a set for the incoming pages
			set<string> incoming;
			//get the incoming page for the specific webpage from our map
			incoming = candidate_incoming.find(it6->first)->second;
			set<string>::iterator it;
			//setting the probability to originally be 0
			double sum_incoming_probability = 0.0;
			//geting various iterators
			set<string>::iterator it7;
			map<string, set<string> >::iterator it8;
			map<string, vector<double> >::iterator it9;
			double sum_ = 0.0;
			//iterating over all of the incoming webpages for the current webpage
			//we are calculting the probabilty for
			for(it7 = incoming.begin(); it7 != incoming.end(); it7++)
			{
				//getting the outgoing webpages for the current webpage
				//in the incoming webpage
				set<string> outgoing;
				outgoing = candidate_outgoing.find(*it7)->second;
				//getting the number of webpages in the outgoing degree
				double outgoing_degree = outgoing.size();
				//getting the probability from the map at the webpage we are on
				int index = i-1;
				double prev_probability = ranking_list.find(*it7)->second[index];
				//calculating the prev proability using the algorithm
				sum_ += prev_probability/outgoing_degree;
			} 
			//for all of the sumation of the probaility times it by 1-e and then
			//add 1/n to the value
			sum_incoming_probability = sum_*((1.0-probability)) + (probability*(1.0/n));
			//push back into the vector the 
			it6->second.push_back(sum_incoming_probability);
			//if i is equal to the number of steps
			if(i == (steps))
			{
				//push back the sum probability into the resulting ranking vector
				resulting_ranking.push_back(sum_incoming_probability);
				//create a temp vector
				vector<string> temp;
				//if the sum we calculated is already in the map
				if(ranking_pairing.find(sum_incoming_probability) != ranking_pairing.end())
				{
					//add the webpage of the same sum incoming probabilty to the vector
					//that corresponds to these webpages
					ranking_pairing.find(sum_incoming_probability)->second.push_back(it6->first);
				}
				//otherwise
				else
				{
					//push back the webpage name into themp
					temp.push_back(it6->first);
					//create a new pairing in the map
					ranking_pairing[sum_incoming_probability] = temp;
				}
				
			}
		}
	}
	//call quicksort on our resulting ranking to sort it from greates to least
	QuickSort(resulting_ranking, greater<double>());
	//vector to store the ranked webpages in
	vector<string> ranking_sorted;
	//set to keep trak of the webpages we already added to the final set
	set<string> added_webpages;
	//for all of the webpages
	for(int i = 0; i < n; i++)
	{
		//get the current ranking at the resulting ranking at value i
		double current_ranking_value = resulting_ranking[i];
		//getting the vector of wepages with that current value from the map
		vector<string> webpage_name = ranking_pairing.find(current_ranking_value)->second;
		//iterator to iterate over the webpage we just found
		vector<string>::iterator it2;
		//iterating over all of the webpages from begin to end
		for(it2 = webpage_name.begin(); it2 != webpage_name.end(); it2++)
		{
			//if we havn't added the webpage to the ranking sorted and added webpages
			if(added_webpages.find(*it2) == added_webpages.end())
			{
				//add them to both set and vector
				added_webpages.insert(*it2);
				ranking_sorted.push_back(*it2);
			}
			
		}
	}
	//returng the final ranking sorted
	return ranking_sorted;
}
