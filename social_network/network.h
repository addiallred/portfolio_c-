#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "user.h"
//addison allred


//creating the network class
class Network {
 public:
 //defining a network constructor
  Network();
  //defining a deconstructor for the network
  ~Network();
  //defining the method to read in the information from the file
  //that has user content
  int read_friends(const char *filename);
  //defining the method to write out the file to the given
  //file name
  int write_friends(const char *filename);
  //defining the method to add a new user to the network
  void add_user(User temp);
  //adding a connection between two friends by the given
  //names
  int add_connection(std::string name1, std::string name2);
  //deleting a friend connection between two friends by the
  //given name
  int remove_connection(std::string name1, std::string name2);
  //getting the id of a user based on their string name
  int get_id(std::string username);
  //getting the number of users in the network
  int get_numusers();
  //defining a function to print all information of 
  //the users out
  void print_everything();
  //defingn a function to print out the list of friends
  //of a specific user
  void print_friends(std::string name1);

  //creating a function to get the name of a user based on
  //their id
  std::string get_usname(int id);
  
  //creating the shortest path function to take in two users id
  //and find the shortest path between them
  std::vector<int> shortest_path(int from, int to);

  //creating teh groups function, does breadth search on 
  //input and tells how many different groups of social 
  //networks there are
  std::vector<vector<int> > groups();

  //creating the suggest friends function, takes in a user
  //looks at friends 2 depth away from them, and see
  //how many friends they have incommon to suggest who the best 
  //score is for a suggestion
  std::vector<int> suggest_friends(int who, int& score);

  //creating the bfs function to be utilized to go through the networks
  //and set the depth and pred of users to deterimne the connections
  //between user and the structur of the network
  void bfs(int start, int end);

 private:
  //defining the private vector
  std::vector<User> user_vector;

  
};


#endif