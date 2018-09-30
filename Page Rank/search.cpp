#include <iostream>
#include <map>
#include <string>
#include <sstream>
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
	//filename that will allow us to acess config
	ifstream input;
	//if the number of argumnents are only 1
	if(argc < 2)
	{
		//by default, open the config.txt file
		input.open("config.txt");
	}
	//if the number of arguments are 2,thanthe config file was provided
	else if(argc == 2)
	{
		//open the file provided
		input.open(argv[1]);
		//if when trying to open the file we fail
		if(input.fail())
		{
			//return 
			return 0;
		}
	}
	//if the numberof arguments are greater than 2,we know
	//this is an invalid input since we should ony be provided 
	//one input file
	else
	{
		cout << "Invalid amount of paramaters" << endl;
		return 0;
	}
	//this is the map that will store the results from config
	map<string,string> final;
	//getting the map that will store the results from config
	//by calling it
	final = config(input);
	//getting an iterator to search through the map we just created from
	//config'
	map<string,string>::iterator it;
	//checking that we have the input file provided
	it = final.find("RESTART_PROBABILITY");
	//getting the probability fron the map
	double prob =  atof(it->second.c_str());
	//geting the number of steps that we will have from the map
	it = final.find("STEP_NUMBER");
	double steps = atof(it->second.c_str());
	//creating the webstorage to run the program on
	WebStorage my_storage(steps, prob);
	it = final.find("INDEX_FILE");
	if(it != final.end())
	{
		//getting the file that stores the information about the webpages provided
		ifstream input_file(it->second.c_str());
		map<string,string>::iterator it1;
		map<string,string>::iterator it2;
		//reading in the file to store the infomration in the map
		my_storage.read_file(input_file);
		my_storage.link_to();
		//closing the file
		input_file.close();
		//getting the file we will draw the query information from
		it = final.find("QUERY_FILE");
		if(it != final.end())
		{
			ifstream query_file(it->second.c_str());
			//getting the file we will pring out to
			it = final.find("OUTPUT_FILE");
			if(it != final.end())
			{
				ofstream out_file(it->second.c_str());
				//calling query to execute the compands provided by the query file on the map of the webpage
				my_storage.query(query_file, out_file);
				//closing the query file and the outfile
				out_file.close();
			}
			query_file.close();
		}
	}
	return 0;
}