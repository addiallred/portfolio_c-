#include <iostream>
#include "user.h"
#include <vector>
#include <string>
//addison allred
using namespace std;

//defining the constructor for the user object
User::User(int id, int year, string name, int zip)
{
	_id = id;
	_year = year;
	_name = name;
	_zip = zip;
}

//defining the destructor for hte user
User::~User()
{

}
//defining the add friend function that is to be implemented
//by the user class
void User::add_friend(int id)
{
	//defing a bool for if we already found 
	//the friend in the list
	bool found = false;
	//looping htrough the friends vector too see if the
	//id of the new user we are trying to add is already
	//in the current users list of friend
	for(int i = 0; i < _friends.size(); i++)
	{
		if(_friends[i] == id)
		{
			found = true;
		}
	}
	//if the friend is not already in the friend list
	//then you add them to the friends vector
	if(!found)
	{
		_friends.push_back(id);
	}
}

//defining the delete friend function that is implemented
//by the user class
void User::delete_friend(int id)
{
	//initializing an index value so that if we do find
	//the friend at that specific id, we can access their
	//index in the friend array
	int index = 0;
	//creating a boolen so if the friend does exist
	//we delete the friend from the friend list
	//if it doesn't exist we wont attempt to delet a value that
	//isn' in the friend list
	bool friend_exist = false;
	//looping through the users friend value
	for(int i = 0; i < _friends.size(); i++)
	{
		//seeing if the id of the current friend wwe are on
		//is equal to the value that we want to delete
		if(_friends[i] == id)
		{
			//setting the index to the index of the
			//friend in the friend array
			//that has the same id as the passed in
			//id so that we can delete the correct friend
			index = i;
			//setting the friend value to exist if we find the 
			//id of hte friend we want to delete in the friends
			//vector
			friend_exist = true;
		}
	}

	//if we found that the friend we want to delete is in the 
	//users friend vector, enter the statement to delete it
	if(friend_exist)
	{
		//starting on the index of the friend that we want
		//then moving all of the friends afterwards up one
		//to replace over the friend that we want to delete
		for(int i = index; i <_friends.size()-1; i++)
		{
			_friends[i] = _friends[i+1];
		}
		//removing the last friend from the list so that we 
		//don't have the same person ant at the end of the
		//friends vector twice
		_friends.pop_back();
	
	}
	

}

//returing the id of the user
int User::get_id()
{
	return _id;
}

//returing the number of friends of the user
int User::get_numfriends()
{
	return _friends.size();
}

//returning the name of the the user
string User::get_name()
{
	return _name;
}

//returing the zipcode of the user
int User::get_zip()
{
	return _zip;
}

//returing the year of the user
int User::get_year()
{
	return _year;
}

//returning the preddecessor or the user
int User::get_pred()
{
	return _pred;
}

//returning hte depth of the user
int User::get_depth()
{
	return _depth;
}

//returning the friends vector of the user
vector<int>* User::get_friends()
{
	return &_friends;
}

//taking in an id and setting it as the users preddecessor
void User::set_pred(int pred_id)
{
	_pred = pred_id;
}

//taking in a depth value and setting it as the users depth
void User::set_depth(int depth_val)
{
	_depth = depth_val;
}

//setting the score of the user to another user
// by taking in a score
void User::set_score(int score_val)
{
	_score = score_val;
}

//getting the users score to another user
int User::get_score()
{
	return _score;
}

//setting the click value of the user by taking in a click val
void User::set_click(int click_value)
{
	_click = click_value;
}

//returing the clique value that the user belongs to
int User::get_click()
{
	return _click;
}