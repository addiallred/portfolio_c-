#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
//addison allred
using namespace std;

//creating the user class and its functions
class User {
 public:
 	//defining the actual user object that will be used
 	//in the constructor
 	User(int _id, int _year, string _name, int _zip);
 	//destructor
 	~User();
 	//creating the function to add friend for an individual
 	void add_friend(int _id);
 	//creating the function to delete friend from an individuals
 	//friends list
 	void delete_friend(int _id);
 	//getting the users id
 	int get_id();
 	//geting the users number of friends they have
 	int get_numfriends();
 	//geting the users zipcode
 	int get_zip();
 	//getting the year of birth for the usre
 	int get_year();
 	//getting the list of friends of the user
 	vector<int>* get_friends();
 	//getting the name of the user
 	string get_name();
 	//getting the preddecessor of the user
 	int get_pred();
 	//getting the depth of the user
 	int get_depth();
 	//setting pred
 	void set_pred(int pred_id);
 	//setting the depth
 	void set_depth(int depth_val);
 	//setting the score of the user
 	void set_score(int score_val);
 	//getting the score of the user
 	int get_score();
 	//setting the click value of the user
 	void set_click(int click_val);
 	//getting the click value of the user
 	int get_click();


 private:
 	//creating the private functions 
 	int _id;
 	int _year;
 	string _name;
 	int _zip;
 	vector<int> _friends;
 	int _depth;
 	int _pred;
 	int _score;
 	int _click;
};

#endif