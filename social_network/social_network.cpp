#include "network.h"
#include "user.h"
#include <iostream>
#include <string>
#include <iomanip>
//addison allred
using namespace std;
//defining a function to print out the menu of the
//various selections that a user could make
void print_menu()
{
	cout << "Please enter your selection: " << endl;
	cout << "(Enter any number not within the range of(1-6) to exit)" << endl;
	cout << "\t" << "1. Add a user(Enter Full Name DOB and Zip" << endl;
	cout << "\t"  << "2. Add friend connection(Enter two names)" << endl;
	cout << "\t" << "3. Remove friend connection(Enter two names)" << endl;
	cout << "\t" << "4. Display all users" << endl;
	cout << "\t" << "5. Display all friends of a user(Enter users name)" << endl;
	cout << "\t" << "6. Write user information to a data file(Provide desired";
	cout << " file name)" << endl;
	cout << "\t" << "7. Shortest path between two users." << endl;
	cout << "\t" << "8. Disjoint sets" << endl;
	cout << "\t" << "9. Friends Suggestion." << endl;
	cout << ">";
}


int main(int argc, char *argv[])
{
	//creating the network object
	Network myNetwork;
	//getting the provided file from argv and using it
	//for reading in the information into the network
	myNetwork.read_friends(argv[1]);
	//if not enough commands are given to the input
	if(argc < 2)
	{
		return -1;
	}

	//printing out the menu to the user
	print_menu();
	//reading in the users choice provided from cin
	int user_choice;
	cin >> user_choice;
	//executing functions while the input is valid input
	while(user_choice < 10 && user_choice > 0)
	{
		//if the user chooses one enter this function
		if(user_choice == 1)
		{
			//getting the id of the new user
			//that we are trying to create
			//we get this by getting the number
			//of users in the network and this will
			//be the new id of the created user
			int id = myNetwork.get_numusers();
			//reading in the first and last name
			//of the provided user and creating the 
			//full name in a string by adding them together
			string first;
			cin >> first;
			string last;
			cin >> last;
			string full = first + " " + last;
			//reding in the year
			int year;
			cin >> year;
			//reading in the zip code
			int zip;
			cin >> zip;
			//greating a user by the given information
			User user1(id, year, full, zip);
			//adding the created user into the network
			myNetwork.add_user(user1);
		}

		//if choice 2 is chosen
		else if(user_choice == 2)
		{
			//reading in the two names provided 
			//in first and last name and then 
			//adding it into a full name string
			string first;
			cin >> first;
			string last;
			cin >> last;
			string full1 = first + " " + last;
			string first2;
			cin >> first2;
			string last2;
			cin >> last2;
			string full2 = first2 + " " + last2;
			//placing the two given names into the 
			//add connection function for network
			//between the two names provided
			myNetwork.add_connection(full1, full2);
		}

		//if the user chooses option 3
		else if(user_choice == 3)
		{
			//reading in both the first and last
			//name of provided by the user
			//and adding it together so the
			//name is in one string
			string first1;
			cin >> first1;
			string last1;
			cin >> last1;
			string full1 = first1 + " " + last1;
			string first2;
			cin >> first2;
			string last2;
			cin >> last2;
			string full2 = first2 + " " + last2;
			//taking the inputed names from the user
			//and placing them in the remove connection
			//function for the network to remove the connection
			//between the two people
			myNetwork.remove_connection(full1, full2);
		}

		//if the users choice is four
		else if(user_choice == 4)
		{
			//print out the network of users using
			//the print function
			myNetwork.print_everything();
		}

		//if the users choice is 5
		else if(user_choice == 5)
		{
			//reading in the name provided
			string first1;
			cin >> first1;
			string last1;
			cin >> last1;
			//adding the first and last name togeth
			//so the name is in one string
			string full1 = first1 + " " + last1;
			//putting the provided name into the print
			//friend function to print all friends out 
			//of the provided user
			myNetwork.print_friends(full1);
		}

		//if the user choice is 6
		else if(user_choice == 6)
		{
			//reading in the file name in from the user
			string file_name;
			cin >> file_name;
			//using the file name provided to write out
			//the data informationto the data file provided

			myNetwork.write_friends(file_name.c_str());
		}
		//if the users choice is 7
			else if(user_choice == 7)
		{
			//reading in the string of the user inputed
			//and then adding it to the same string
			string first1;
			cin >> first1;
			string last1;
			cin >> last1;
			string full1 = first1 + " " + last1;
			string first2;
			cin >> first2;
			string last2;
			cin >> last2;
			string full2 = first2 + " " + last2;
			//creating ids so that we get the ids
			//of the users whos names were inputed
			int id1;
			int id2;
			id1 = myNetwork.get_id(full1);
			id2 = myNetwork.get_id(full2);

			//creating a results vector to store the results
			//from the shortest path in
			vector<int> results;
			//making sure that both id1 and id2 are valid
			//id's, the user exists, so we don't try to run
			//the shortest path function
			if(id1 != -1 && id2 != -1)
			{
				//running the shortest path funciton with the 
				//ids of the input users and storing it in the vector
				results = myNetwork.shortest_path(id1, id2);
				//only run if results size is bigger than 0 so that 
				//it isn't empty and that we actually have a path
				if(results.size() > 0)
				{
					for(int i = 0; i < results.size(); i++)
					{
						//printing it out in the correct format,
						//if last value in the vector don't pring an arrow 
						//after
						if(i == results.size()-1)
						{
							string name = myNetwork.get_usname(results[i]);
							cout << name << endl;

						}
						else
						{
							string name = myNetwork.get_usname(results[i]);
							cout << name << "->";
						}
				
					}
				}

				//if the vector is empty print out that it is empty
				else
				{
					cout << "No friend connection between the two users." << endl;
				}
				
			}
		
		}

		//if the users choice is 8
		else if(user_choice == 8)
		{
			//creating a vector to store the results in
			vector<vector<int> > results;
			//getting the vector of vectors by calling groups function
			results = myNetwork.groups();

			//initializing the click to print out
			int cur_click = 1;

			//making sure that the vector isn't empty
			if(results.size() != 0)
			{
				//going through the various vectors
				for(int i = 0; i < results.size(); i++)
				{
					

					cout << "Set " << cur_click << " => ";
					//pringint out the individual names in each vector
					//based on the location in the vetor vector
					for(int j = 0; j < results[i].size(); j++)
					{
						//printing it out in the correct order so that the last name
						//doesn't have a comma after it
						if( j == results[i].size()-1)
						{
							string name = myNetwork.get_usname(results[i][j]);
							cout << name;
						}
						else
						{
							string name = myNetwork.get_usname(results[i][j]);
							cout << name << ", ";
						}
					
					}
					//increasing the click we are on
					cur_click++;
					cout << endl;
					
				}
				cout << endl;
			}

			//printing outif the vector is empty meaning there are no clicks
			else
			{
				cout << "There are no sets." << endl;
			}
		}

		//if the user chooses 9
		else if(user_choice == 9)
		{
			//reading in the inputed names in to a full name
			string first1;
			cin >> first1;
			string last1;
			cin >> last1;
			string full1 = first1 + " " + last1;

			//gettting the id of the user put in
			int id = -1;
			id = myNetwork.get_id(full1);
			//creating a vector to put the results in
			vector<int> results;
			int score = 0;
			//if the id isn't -1 run friends, if it is -1
			//than the user inputeded does not exist
			if(id != -1)
			{
				//running suggest friends with the users id and
				//a score value that is a reference so we can access it outside
				//of the function
				results = myNetwork.suggest_friends(id, score);
				//printing out all the users in results and the correlatting
				//score
				cout << "The suggested friend(s) is/are: " << endl;
				if(results.size() != 0)
				{
					for(int i = 0; i < results.size(); i++)
					{
						cout << left <<  setw(30);
						cout << myNetwork.get_usname(results[i]) << " ";
						cout << setw(10) <<" Score:" << score;
						cout << endl;
					}
				}
				//if the resul size is 0, there is not suggestion
				else
				{
					cout << "There are no friends suggestions." << endl;
				}				}	
			}
			// if the user isn't in the network display it
			else
			{ 
				cout << "User does not exist." << endl;
			}
		//printint out th emenur to the user after we execute
		//the users input
		print_menu();
		//reading in the users input
		cin >> user_choice;
	}
	

  return 0;
}