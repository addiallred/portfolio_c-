#include <iostream>
#include "network.h"
#include <string>
#include <fstream>
#include <vector>
#include "user.h"
#include <sstream>
#include <iomanip>
#include <deque>
#include <algorithm>
//addison allred
using namespace std;

//creating the constructor
Network::Network()
{

}

//making the destructor
Network::~Network()
{

}

//creating the network read friends function
int Network::read_friends(const char* filename)
{
	//opening the filename that was provided
	ifstream read_file;
	read_file.open(filename);
	//if the file fails to open, printing out the correct
	//results that it failed
	if(read_file.fail())
	{
		cout << "Failed reading the file" << endl;
		return -1;
	}

	//initializing the number of people in the file
	int num_friends = 0;
	//reading in the number of people provided in the file
	read_file >> num_friends;
	//creating a string dummy, this string dummy will read
	//in the remaining white space in the file so that
	//it will continue to read in the file content correct
	string dummy;
	getline(read_file, dummy);
	//defining the zip year id name and the friends vector
	//so that we can read it in from the user
	int zip;
	int year;
	int id;
	string name;
	vector<int> friends;
	//continuing to read in all the information
	//until the number of users that is provided
	//by the file is added in
	for(int i = 0; i < num_friends; i++)
	{
		//reading in the id from the file
		read_file >> id;

		//reading in the white space before the first name
		getline(read_file, dummy);
		//reading in the first name
		string first;
		read_file >> first;
		//reading in the last name
		string last;
		read_file >> last;
		//adding the first and last name togther so that we have the
		//full name in one string
		string full = first + " " + last;
		//reading in the white space before the year
		getline(read_file, dummy);
		//reading in the year
		read_file >> year;
		//reading in the white space beore the zip
		getline(read_file, dummy);
		//reading in the zip
		read_file >> zip;
		//creating the user object
		User temp(id, year, full, zip);
		//reading in the white space beore the number of friends
		getline(read_file, dummy);
		//reading in the number of friends the user has
		string values;
		getline(read_file, values);
		//creating a string stream and reading in the values
		//of friends into the ss. 
		stringstream ss;
		ss << values;
		//initializing the id of the friends value
		int friend_id;
		//looping through while we can still read in 
		//information from the ss
		while(ss >> friend_id)
		{
			//adding the friend id to the users
			//friends vector
			temp.add_friend(friend_id);
		}
		//adding the user we read in to the network file
		add_user(temp);
	}
	//closing the file
	read_file.close();
	return 0;
}

//creating the function to write the network of users 
//out to a file
int Network::write_friends(const char* filename)
{
	//opening the file to write the information out to
	ofstream outfile;
	outfile.open(filename);
	//if fail to open the file, than exit trying to write to 
	//the file
	if(outfile.fail())
	{
		cout << "Failed to open the file to write to." << endl;
		return -1;
	}
	//writing the header to the file
	outfile << user_vector.size() << endl;

	//writing out the user information using get functions
	for(int i = 0; i < user_vector.size(); i++)
	{
		outfile << user_vector[i].get_id() << endl;
		outfile << "\t" << user_vector[i].get_name() << endl;
		outfile << "\t" << user_vector[i].get_year() << endl;
		outfile << "\t" << user_vector[i].get_zip() << endl;
		//creating a friends vector for the current user we are on
		vector <int> friends_us;

		friends_us = *user_vector[i].get_friends();
		outfile << "\t";
		//going through the frineds vector and printing out the id of
		//every friend
		for(int j = 0; j < friends_us.size(); j++)
		{
			outfile << friends_us[j] << " ";
		}
		outfile << endl;
	}
	//closing the files you write too
	outfile.close();
	return 0;
}

//creating the function to print out all the information of hte 
//users in the network
void Network::print_everything()
{
	//printing outt eh title header
	cout << left << setw(5) << "ID"<< left << setw(25) << "Name" << left;
	cout << setw(8) << "Year";
	cout << left << setw(5) << "Zip" << endl;
	for(int i = 0; i < 60; i++)
	{
		cout << "=";
	}
	cout << endl;
	//looping through all the users in the network
	//and printing out the users information based
	//on the get function
	for(int i = 0; i < user_vector.size(); i++)
	{
		cout << left << setw(5) << user_vector[i].get_id() << left << setw(25);
		cout << user_vector[i].get_name();
		cout << left << setw(8) << user_vector[i].get_year() << left << setw(5);
		cout << user_vector[i].get_zip() << endl;
	}

}

//creating the function to print out all the friends of
//the user given 
void Network::print_friends(string name1)
{
	//creating a vector for the list of friends
	vector <int> list_friends;
	//getting the id of the name provided
	int id_name;
	id_name = get_id(name1);
	//making sure that the id returned is a valid id number
	//so that we only print out individuals who are in our
	//network
	if(id_name != -1)
	{
		//putting the list of friends from the specific user
		//getting the users id and placing it in the created vector
		list_friends = *user_vector[id_name].get_friends();
		//printing out the header 
		cout << left << setw(5) << "ID"<< left << setw(25) << "Name" << left;
		cout << setw(8) << "Year";
		cout << left << setw(5) << "Zip" << endl;
		for(int i = 0; i < 60; i++)
		{
			cout << "=";
		}
		cout << endl;
		//printing out the friend information of the user based
		//on the users in the list that we got returned by 
		//the user funtion of get friends and then
		//taking the size of the vector to know how many times to loop through it
		for(int i = 0; i < list_friends.size(); i++)
		{
			//getting the id of the friend in the friend list
			//so that we can print out the proper information
			//for that user
			int current_id;
			current_id = list_friends[i];
			//printing out the friends information based on the functions
			//of get with the current index
			cout << left << setw(5) << user_vector[current_id].get_id();
			cout << left << setw(25);
			cout << user_vector[current_id].get_name();
			cout << left << setw(8) << user_vector[current_id].get_year();
			cout << left << setw(5);
			cout << user_vector[current_id].get_zip() << endl;
		}
	}
	//if we try to print out a list of a users friends
	//who the user doesn't exist, print out that we can't
	//print it out
	else
	{
		cout << "User does not exist." << endl;
	}

		
}

//getting the number of users in the network
int Network::get_numusers()
{
	return user_vector.size();
}

//adding the user to the end of the network
void Network::add_user(User temp)
{
	user_vector.push_back(temp);
}

//adding a connection between two users based upon the
//two names given
int Network::add_connection(string name1, string name2)
{
	//setting the original ids to -1 in case the name
	//of the user provided does not exist so we dont attempt
	//to add a connection between two users who dont'
	//exist
	int id1 = -1;
	int id2 = -1;
	//getting the ids of the users based on their names
	//provided
	id1 = get_id(name1);
	id2 = get_id(name2);
	//only entering the statement if the ids are correct
	//and valid
	if(id1 != -1 && id2 != -1)
	{
		//using the add friend function from the user
		//class and adding the connection for each
		//of the users based upon the ids
		//adding both connection for both users
		user_vector[id1].add_friend(id2);
		user_vector[id2].add_friend(id1);
		return 0;
	}
	//returning -1 if the connection doesn't exist
	cout << "User/s doesn't exist, connection not made." << endl;
	return -1;
}


int Network::remove_connection(string name1, string name2)
{
	//setting the original ids to -1 so if we don't find the 
	//user in the network than we wont try to remove the connection
	int id1 = -1;
	int id2 = -1;
	//getting the id of the users names provided
	id1 = get_id(name1);
	id2 = get_id(name2);
	//if the users exit in the network than we can delete the connection
	if(id1 != -1 && id2 != -1)
	{
		//removing the connection between the two 
		//users provided using the function used in the 
		//user class with the delete function
		user_vector[id1].delete_friend(id2);
		user_vector[id2].delete_friend(id1);
		return 0;
	}
	//printing out unsuccesful if the user provided does not exist
	cout << "Removal not successful, user/s does not exist." << endl; 
	return -1;

}

//getting the id of the user in the network
int Network::get_id(string username)
{
	//going through the users vector network
	for(int i = 0; i < user_vector.size() ;i++)
	{
		//if the currect user we are on in the vector
		//is equal to the name inputed
		if(user_vector[i].get_name() == username)
		{
			//return the user id of the username
			//that is the same as the user put in
			return user_vector[i].get_id();
		}

	}
	//printing out if the user put in is not in the network
	cout << "User is not in network" << endl;
	return -1;
}

//creating a bfs function to be used for the network
void Network::bfs(int start, int end)
{
	//going through the user vector and initializing all
	//values of the user vector to -1
	for(int i = 0; i < user_vector.size(); i++)
	{
		user_vector[i].set_pred(-1);
		user_vector[i].set_depth(-1);
	}

	//creating a deque to walk through the bfs in
	deque<User> current_net;
	//setting the users depth that we start with 0
	user_vector[start].set_depth(0); 
	//pushing back a user object into the deque
	current_net.push_back(user_vector[start]);
	
	//continuing to go through the network until the deque
	//is empty
	while(!(current_net.empty()))
	{
		//creating an user object of the current user that we are on
		User current_user = current_net.front();
		//setting the current depth of the users friends, 
		//it will be plus one of the current users depth since
		//they are after the current user in the graph
		int cur_depth = current_user.get_depth() + 1;

		//getting the current id to be used for the predicessor
		//of the users friends
		int cur_id = current_user.get_id();

		//if the curent id we are on is the end id
		//don't continue the search and break out of the bfs search
		if(cur_id == end)
		{
			break;
		}

		//popping out the first user in the deque
		current_net.pop_front();
		//getting the vector of the first user
		vector<int> friends_user;
		friends_user = *user_vector[cur_id].get_friends();

		//going through the current users friends list
		for(int i = 0; i < user_vector[cur_id].get_numfriends(); i++)
		{
			//if a user in the friend list has a depth of -1, 
			//this means that they have not been visited yet 
			//and we can add them into the deque with out adding
			// a user twice
			if(user_vector[friends_user[i]].get_depth() == -1)
			{
				//setting the depth and the pred of the user
				//in the friend vector we are currently on to be
				//the user we popped id, and their depth + 1
				user_vector[friends_user[i]].set_depth(cur_depth);
				user_vector[friends_user[i]].set_pred(cur_id);
				//adding the friends into the deque
				current_net.push_back(user_vector[friends_user[i]]);


			}
			
		}
	}

}

//creating the shortest path function to take
//in two inputs and find the shortest path between two users
vector<int> Network::shortest_path(int from, int to)
{
	//creating a vector to store the found path from the friends
	vector<int> path_found;
	//implement the bfs to set all the needed values, such as
	//predecessor
	bfs(from, to);

	//if no path was found, meaning the users 
	//depth who we wanted to end with is still -1, retuwn
	//as there is not path between the two users
	if(user_vector[to].get_depth() == -1)
	{

		return path_found;
	}	

	//setting the current depth and id equal to the
	//values of the to user passed in
	int cur_depth = user_vector[to].get_depth();

	int cur_id = user_vector[to].get_id();
	
	//working from the to user and working backwards to get to the
	//from user, so when we get to the from user, who's depth
	//will be 0, we stop pushing in user ids
	while(cur_depth != 0)
	{
		//pushing back the current user into the vector
		path_found.push_back(user_vector[cur_id].get_id());
		//setting the current id to the predecessor of the current
		//user that we are on, this will work its way
		// backwards in the 
		//shortest way possible
		cur_id = user_vector[cur_id].get_pred();
		//setting current depth to the current depth of the 
		//user id we are on
		cur_depth = user_vector[cur_id].get_depth();
	}

	//once we exit the while loop, we push back the last user
	//into the vector
	path_found.push_back(user_vector[cur_id].get_id());

	//reversing the vector because we are pushing it in to->from
	//where we want it to be from->to
	reverse(path_found.begin(), path_found.end());
	return path_found;
}

//creating the get username, taking in the user id
//and returning the users name based on their id
string Network::get_usname(int id)
{
	string name = user_vector[id].get_name();
	return name;
}

//creating suggested friends funtion taking in the user and
//an int reference so that we can update the score out of the 
//function
vector<int> Network::suggest_friends(int who, int& score)
{
	//creating a vector for the suggested friends
	vector<int> sug_friends;
	//doing a bfs starting with who and then going to -1
	//allowing for bfs to naturally end and go through all
	//users
	bfs(who, -1);
	//creating a current friends list of the user
	//who we are running suggest friends for
	vector<int> cur_friends;
	//getting the users frieneds vector
	cur_friends = *user_vector[who].get_friends();
	//setting the score to -1 because we know it can't be
	//-1
	score = -1;
	//setting all users score to 0 so that the scores are not
	// carrying over from previously running it

	for(int i = 0; i < user_vector.size(); i++)
	{

		user_vector[i].set_score(0);
	}
	
	//looping through all the users in the network
	for(int i = 0; i < user_vector.size(); i++)
	{

		//if the users depth is 2, we want to see the score
		//to the current user we are on
		if(user_vector[i].get_depth() == 2)
		{
			//creaing a tempscore to add points when
			//the user has a common friend with the
			//individual we are looping through in the vector
			int tempscore = 0; 
			//getting the friends vector of the user
			//we are looping through whose depth is 2
			vector<int> two_friends;
			two_friends = *user_vector[i].get_friends();
			
			//looping through the who's friends vector 
			//and the current user we are on by the foor
			//loop and comparing if they have any friends in
			//common, 
			for(int k = 0; k < cur_friends.size(); k++)
			{
				for(int j = 0; j < two_friends.size(); j++)
				{
					//if they have riends in common increase the
					//tempscore
					if(cur_friends[k] == two_friends[j])
					{
						tempscore++;
					}
				}
				//after seeing how any friends they have in cmmon
				//setting the users score
				user_vector[i].set_score(tempscore);
			}
			//if the temporary score of the user is larger
			//than the current score, set the score equal
			//to the tempscore
			if(tempscore > score)
			{
				score = tempscore;
			}
		}

	}

	//looping through the user vector and seeing if
	//the users score is similar to the final max score
	//that we found
	for(int i = 0; i < user_vector.size(); i++)
	{
		//if the users score is the same as the max score
		//than add it to the suggest friends vector
		if(user_vector[i].get_score() == score)
		{
			sug_friends.push_back(user_vector[i].get_id());
		}
	}

	//returning the suggest friends vector
	return sug_friends;
}

//creating the groups function
vector<vector<int> > Network::groups()
{
	//creating a vector of vector for the clicks
	vector<vector<int> > clicks;
	
	//the current click is 0
	int cur_click = 0;
	//setting all users in the vector click to -1
	//because that is not a possible click value
	for(int i = 0; i < user_vector.size(); i++)
	{
		user_vector[i].set_click(-1);
	}
	//going through the user vector
	for(int i = 0; i < user_vector.size(); i++)
	{
		//if the current user we one click value is -1, 
		//meaning that they don't belong to any clicks
		//that have been searched, than run bfs
		//with them being the starting point and go
		//to the very end of the graph to cover all
		//individuals in the click and increase num of click
		if(user_vector[i].get_click() == -1)
		{
			bfs(i, -1);
			cur_click++;
			
		}

		//going through the user vector 
		for(int k = 0; k < user_vector.size(); k++)
		{
			//if the current user we are on does not have a 
			//depth of -1, meaning they were just recently updated
			//by bfs, set their click to the current click that
			//we are on
			if(user_vector[k].get_depth() != -1)
			{
				user_vector[k].set_click(cur_click);
			}
		}
		

	}
	
	//going through the different groups of click
	for(int j = 1; j <= cur_click; j++)
	{
		//creating a temp vector to put the users
		//in the same click into and then push into
		//click vector
		vector<int> temp;
		//foing through the user vector
		for(int i = 0; i < user_vector.size(); i++)
		{
			//if the current user we are on has the 
			//same click value as the click we are currently on
			//than push the user into the temp vector
			if(user_vector[i].get_click() == j)
			{
				
				temp.push_back(user_vector[i].get_id());				
			}
		}
		//once we have all the users belonging to the same click
		//push them into clicks
		clicks.push_back(temp);
	
	}
	//return clicks
	return clicks;
}
