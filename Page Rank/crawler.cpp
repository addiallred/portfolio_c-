#include <iostream>
#include <string>
#include "crawl_webpages.h"
#include <map>
#include <fstream>
using namespace std;
//creating the config function, this will take in one config file and will
//parse the contents of it
map<string, string> config(ifstream &config)
{
	//getting a map that will store the contents of the file
	map<string, string> my_map;
	while(!config.fail())
	{
		//get a line from the config file
		string temp_string;
		getline(config, temp_string);
		//if we failed when getting the line break
		if(config.fail())
		{
			break;
		}
		//other wise
		else
		{
			//boolean so we know when we found the inequality 
			bool found_equal = false;
			//key and value strings that we will use and construct
			//be placed into the map
			string key = "";
			string value = "";
			//need added, is false if we found an equal sign and we need 
			//to start building the value
			bool need_add = false;
			//iterate over the string
			for(int i = 0; i < int(temp_string.length()); i++)
			{
				//if the char is the poind sign
				if(temp_string[i] == '#')
				{
					//if we have constructed key and values
					//place them into the map
					if(found_equal)
					{
						my_map[key] = value;
					}
					//stop reading because everything else on the line is just 
					//comments that don't need to be read
					break;
				}
				//if temp string is the equal sign
				else if(temp_string[i] == '=')
				{
					//we found the equal sign and we need to start building the value
					found_equal = true;
					need_add = true;
				}
				//if the tempstring isn't a space
				else if(temp_string[i] != ' ')
				{
					//if we haven't found the equal sign
					if(!found_equal)
					{
						//build the key
						key += temp_string[i];
					}
					//if we found the equal sign
					else
					{
						//build the value
						value += temp_string[i];
					}
				}
			}
			//if the words we constructed need to be addedto the map
			if(need_add)
			{
				//add the value and key pairing
				my_map[key] = value;
			}
		}
	}
	//return the map we just constructed
	return my_map;
}
int main(int argc, char* argv[])
{
	//getting the ifstream
	ifstream input;
	//if there are less than 2 arguments
	if(argc < 2)
	{
		//out input file is a default config.txt
		input.open("config.txt");
	}
	else
	{
		//open the provided config file
		input.open(argv[1]);
	}
	//get the map from calling the configurartion function
	map<string, string> final;
	final = config(input);
	//getting an iterator to the map
	map<string, string>::iterator it;
	//looking for the index file which will provided the file name
	it = final.find("INDEX_FILE");
	string file_index = it->second;
	//placing the index file value into an ifstream so we can open the file
	ifstream input_file(it->second.c_str());
	//looking for the index file while will provide the output file name
	it = final.find("OUTPUT_FILE");
	//place the file name in the outfile ofstrem
	ofstream out_file(it->second.c_str());
	//create a webpage class to crawl on
	Crawl_webpages my_crawl;
	//call the crawl funtions to read from the files and print to them
	my_crawl.read_file(input_file, file_index);
	my_crawl.print_crawl(out_file);
	//close the files we opened
	input_file.close();
	out_file.close();
	return 0;
}