#ifndef NODE_H
#define NODE_H

//node struct
struct Node{
	//binary value
	std::string value;
	//if it has been explored
	bool explored;
	//calculated heuristic
	int heuristic;
	//is the distance in binay from the start
	int g_length;
	//g + h
	int f_calc;
	//its predecessor in the search
	std::string pred;
};
#endif