#include "lliststr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


int main(int argc, char* argv[])
{
	//creating a new object of the list to
	//use throughout the function
	LListStr* list = new LListStr();
	
	//make sure that a file was provided to read from
	if(argc < 2)
	{
		cout << "Please provide an input file" << endl;
		return -1;
	}

	//opening the file to read from it
	ifstream input;
	input.open(argv[1]);

	//if opening the file failed output the correct results
	if(input.fail())
	{
		cout << "Failed reading this file" << endl;
	}

	//while we can still read from the file and read in
	//continue to execute instructions below
	while(!(input.fail()))
	{
		//reading in the action that we are 
		//trying to execute from the function
		string action;
		input >> action;
		//if the function is equal to add
		if(action == "ADD")
		{
			//read in the position that we are 
			//trying to create
			int position;
			input >> position;
			//read in the name for the positio
			string name;
			input >> name;
			//placing the values read in into the insert function
			list->insert(position, name);
		}

		//if the action read in is replace
		else if(action == "REPLACE")
		{
			//read in the position value from the file
			int position;
			input >> position;
			//read in  the name from the file
			string name;
			input >> name;
			//use the name and position to reset the name at given location
			list->set(position, name);
			
		}

		//if the action read in is act
		else if(action == "ACT")
		{
			//making sure that the list size is larger than one
			//so that if there is only one person left we dont let them
			//try to kill themself
			if(list->size() > 1)
			{
				//read in the position of the individual who will
				//assassin someone
				int position;
				input >> position;
				//get the size of the list and then subtract it
				//by one to get the max index value
				int max_size = list->size();
				max_size--;

				//if the position is within valid bounds
				if(position <= max_size)
				{
					//create a string to read in the killed name into
					string killed;
					//initialize the remove position
					int remove_pos = 0;
					//if the position of the assassinator is the max index
					if(position == max_size)
					{
						//the individual that we will remove is at index 0
						//and we can get their name by the get funciton
						killed = list->get(remove_pos);
						list->remove(remove_pos);
					}
					else
					{
						//other wise increase the remove position by one so we 
						//kill the individual next to the assassinator
						//we can also get their name value by get function
						remove_pos = position + 1;
						killed = list->get(remove_pos);
						
						list->remove(remove_pos);
					}

					//print out whoever was killd
					cout << "Assassinated: " << killed << endl;
				}

			}

			//if the list has size one
			
		}
	}

	//if the list is not empty and the size of the list is larger than one
	if(list->size() == 1)
	{
		//the last user, at index 0, is the winner
		string winner;
		winner = list->get(0);
		cout << "Winner: " << winner << endl;
	}
	else if(!(list->empty()) && list->size() > 1)
	{
		//get the size of the list
		int player = list->size();
		cout << "Remaining Players: " << player << endl;
		//iterate through the list to get all of the players names
		//using the get function and then printing them out
		for(int i = 0; i < player; i++)
		{
			string player_name = list->get(i);
			cout << player_name << endl;
		}
			
	}

	//at the end delete the list
	delete list;

}