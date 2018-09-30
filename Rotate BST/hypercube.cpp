#include <iostream>
#include "hypercube_data.cpp"
#include <fstream>
#include <set>
using namespace std;
//function to read in the file
set<string> readFile(ifstream& infile)
{
	//getting a blank string to get line from, we know that the first value will just be
	string blank;
	getline(infile, blank);
	//getting a set of strings that will store the content of the file
	set<string> file_read;
	//while we can read into the file without failing
	while(!infile.fail())
	{
		//string temp that will be used in getline to get the line in the file
		string temp;
		getline(infile, temp);
		//if we try to open the file and we fail return
		if(infile.fail())
		{
			return file_read;
		}
		//other wise
		else
		{
			//insert the string we just got intothe vector
			file_read.insert(temp);
		}
	}
	//return the vector we just created from reading the file
	return file_read;
}

//main function
int main(int argc, char* argv[])
{
	//getting the file that we will use to open
	ifstream input(argv[2]);
	//if we can open the file return
	if(input.fail())
	{
		return 0;
	}
	//if the number of contents thatwe have is less than 2 retur
	if(argc < 2) 
	{
		return 0;
	}
	//getting a set to store the valid nodes in
	set<string> valid_nodes;
	//valid nodes get it from reading the file wiht the correct ifstream
	valid_nodes = readFile(input);
	//getting an iterator to make sure the bools are the same size as the
	//one provided
	set<string>::iterator it;
	it = valid_nodes.begin();
	//temp binary string
	string temp = *it;
	//the start string is the first input
	string start = argv[1];
	//if length are diffenet return
	if(temp.length() != start.length())
	{
		return 0;
	}
	//construct a hypercube given the information from the command line
	HyperCube user_hyperCube(start, valid_nodes);
	//calling the search function for astar
	user_hyperCube.a_star();
	//get the results from calling found path
	bool results = user_hyperCube.found_path();
	//if we found a path
	if(results)
	{
		//get the vector from calling return path this gives the final paths
		vector<string> final_path = user_hyperCube.return_path();
		//iterate over the vector and iterate through it backwards since it is placed
		//into the vector from end to begining
		for(int i =int(final_path.size()) -1; i >= 0; i--)
		{
			cout << final_path[i] << endl;
		}
	}
	//if we didn't find a path
	else
	{
		//print that we didn't find a transformation
		cout << "No transformation" << endl;
	}
	//get the expansion value from calling return expand
	int expansions = user_hyperCube.return_expand();
	//print out the number of expansions that we have
	cout << "expansions = " << expansions << endl;

	return 0;
}