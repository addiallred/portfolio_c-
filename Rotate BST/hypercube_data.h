#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include "node.h"
#include "comparator.h"
#include <set>
//creating a hyper cube class
class HyperCube
{
	//public members
public:
	//constructor
	HyperCube(std::string begin, std::set<std::string>& valid_);
	//destructor
	~HyperCube();
	//function astar,this will execute the algorithm a*
	void a_star();
	//this will create the graph, which will contain a string, and the
	//corresponding valid neighbors to the specified node
	void construct_graph();
	//returning if there is a path
	bool found_path();
	//returning the expansion value
	int return_expand();
	//once we reach the end, from the end node, back track to the predecessor of each
	//node till we get to the begining, this will give us a vector with the path
	void back_trace(Node* curr_node);
	//returning the found path
	std::vector<std::string> return_path();
private:
	//start value
	std::string start;
	//node objectof start node
	Node* start_node;
	//end value
	std::string end;
	//if we found the end in a star
	bool found_end;
	//stores the final path
	std::vector<std::string> final_path;
	//number of expansions made
	int expansion;
	//map to store the value of the node and the corresponding
	//node object that are the valid nodes
	std::map<std::string, Node*> valid_nodes;
	//total distance from start to end
	int total_distance;
	//map that will have node and all of its corresponding neigbor nodes
	std::map<std::string, std::set<Node*> > graph;
	//the priority que to execute astar on
	std::priority_queue<Node*, std::vector<Node*>, Comparator> hyper_queue;
};