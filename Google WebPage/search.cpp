#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "webstorage.h"
#include <set>
using namespace std;

map<string, string> config(ifstream &config)
{
	map<string, string> my_map;
	while(!config.fail())
	{
		string temp_string;
		getline(config, temp_string);
		if(config.fail())
		{
			break;
		}
		else
		{
			bool found_equal = false;
			string key = "";
			string value;
			bool need_add = false;
			for(int i = 0; i < int(temp_string.length()); i++)
			{
				if(temp_string[i] == '#')
				{
					if(found_equal)
					{
						my_map[key] = value;
					}
					break;
				}
				else if(temp_string[i] == '=')
				{
					found_equal = true;
					need_add = true;
				}
				else if(temp_string[i] != ' ')
				{
					if(!found_equal)
					{
						key += temp_string[i];
					}
					else
					{
						value += temp_string[i];
					}
				}
			}
			if(need_add)
			{
				my_map[key] = value;
			}
		}
	}
	return my_map;
}

int main(int argc, char* argv[])
{
	//making sure we have enough input
	if(argc < 4)
	{
		cout << "Not enough input provided " << endl;
	}
	//creating a map with the key being a single string word, and the value
	//being a set of webpages names that corespond to the word
	WebStorage my_storage;
	//getting the file that stores the information about the webpages provided
	ifstream input_file(argv[1]);
	//reading in the file to store the infomration in the map
	my_storage.read_file(input_file);
	my_storage.link_to();
	//closing the file
	input_file.close();
	//getting the file we will draw the query information from
	ifstream query_file(argv[2]);
	//getting the file we will pring out to
	ofstream out_file(argv[3]);
	//calling query to execute the compands provided by the query file on the map of the webpage
	my_storage.query(query_file, out_file);
	//closing the query file and the outfile
	query_file.close();
	out_file.close();
}