#include "hypercube_data.h"
#include <set>
#include <vector>
#include <iostream>
#include "comparator.h"
#include <queue>
#include <map>
using namespace std;

//hypercube constructor taking in the begin string and the set of strings that 
//are the valid nodes that we can move over
HyperCube::HyperCube(string begin, set<string>& valid_)
{
	//setting the start string of the binary string
	start = begin;
	//getting a string to construct the end
	string construct_end;
	//itearte over the length of the start length and add a 1 since
	//the construct end will be the came length as the start but all 1
	for(int i = 0; i < int(start.length()); i++)
	{
		construct_end += '1';
	}
	//set the end to the end we constructed
	end = construct_end;
	//get a set to iterate over the valid values from the set
	set<string>::iterator it;
	for(it = valid_.begin(); it != valid_.end(); it++)
	{
		//set the heuristic equal to 0 for every node at first
		int temp_herus = 0; 
		//set the distance from the start to be 0
		int distance_start = 0;
		//have the string of the binary value be the derefferenced value
		string curr_node = *it;
		//for all of the charactures in the current binary value
		for(int i = 0; i < int(curr_node.length()); i++)
		{
			//temp string so we aren't altering the actual value of *it
			string temp_string = *it;
			//if it is 0, increase the distance it is from the end
			if(temp_string[i] == '0')
			{
				temp_herus++;
			}
			//if the temp string does not equal the start char at the same
			//location, increase the distance it is from start
			if(temp_string[i] != start[i])
			{
				distance_start++;
			}
		}
		//this is the f value that we will use to prioritize nodes
		int calc_val = distance_start + temp_herus;
		//create a new node
		Node* new_node = new Node;
		//set the heuritic to the calculated temp_herus
		new_node->heuristic = temp_herus;
		//set the g length from the calculateddistancestart
		new_node->g_length = distance_start;
		//set f value from the calculated f
		new_node->f_calc = calc_val;
		//set the value to be the binary value of the current string in the set
		new_node->value = *it;
		//set explored to be false
		new_node->explored = false;
		//constructing the map
		valid_nodes[*it] = new_node;
		//if the string for this node is equal to the startstring
		if(*it == start)
		{
			//this node is the start node
			start_node = new_node;
		}
	}
	//set expansion to be 0
	expansion = 0;
	//call the construct graph function to construct the graph 
	//for the hypercube
	construct_graph();
	//push the strat node onto the queue since this should be the first
	//value that we call and set its value to be true
	hyper_queue.push(start_node);
	start_node->explored = true;
}
//destructor for hypercube
HyperCube::~HyperCube()
{
	//for all of the nodes that we dynamically created
	map<string, Node*>::iterator it;
	for(it = valid_nodes.begin(); it != valid_nodes.end(); it++)
	{
		//delete them
		delete it->second;
	}
}
//construct the graph for the hypber cube so we know what nodes
//we can go between
void HyperCube::construct_graph()
{
	//iterate over the valid nodes
	map<string, Node*>::iterator it;
	for(it = valid_nodes.begin(); it != valid_nodes.end(); it++)
	{
		//get the binary value of the node that we are on
		string temp_s = it->first;
		//set neighbors, will store all of the valid neighbors of the
		//node in here
		set<Node*> neighbors;
		//iterate over the size of the binary value
		for(int i = 0; i < int(temp_s.length()); i++)
		{
			//if at the i location it is 0
			if(temp_s[i] == '0')
			{
				//create a temp string, switch the i value to 1 so 
				//it is only different by one bit
				string temp = temp_s;
				temp[i] = '1';
				//if we can find it in the map
				if(valid_nodes.find(temp) != valid_nodes.end())
				{
					//set the temp node to be the actual node from the valid nodes
					//from searching for temp in valid nodes
					Node* temp_node = valid_nodes.find(temp)->second;
					//insert the temp node int the neighbor vector
					neighbors.insert(temp_node);
				}
			}
			//if at i it is 1
			if(temp_s[i] == '1')
			{
				//get a temp string so we aren't changing temp_s
				string temp = temp_s;
				//change it by one bit by fliping the 1 to a 0
				temp[i] = '0';
				//if we can find this new temp in the valid nodes map
				if(valid_nodes.find(temp) != valid_nodes.end())
				{
					//get the node that coresponds to if
					Node* temp_node = valid_nodes.find(temp)->second;
					//insert it into the neighbor set
					neighbors.insert(temp_node);
				}
			}
		}
		//construct the graph for each of the valid nodes
		graph[temp_s] = neighbors;
	}
}
//a star, function to execute the search
void HyperCube::a_star()
{
	//get the top value from the queue
	Node* top = hyper_queue.top();
	//pop it from the queue
	hyper_queue.pop();
	//set for the neighbors of the top
	set<Node*> top_neighbors;
	//top binary string value
	string top_value = top->value;
	//if it is equal to the end then return becaue we found
	//path from start to end
	if(top_value == end)
	{
		//push back the top value onto the vector
		final_path.push_back(top_value);
		//found is now true
		found_end = true;
		return;
	}
	//increase the number of expansions since we are now expanding on the top
	expansion++;
	//get the top neighbors from the graph constructed
	top_neighbors = graph.find(top_value)->second;
	//iterate over all of the neighbors of the top
	set<Node*>::iterator it;
	for(it = top_neighbors.begin(); it != top_neighbors.end();it++)
	{
		//get a temp node of it
		Node* temp_node = *it;
		//get the binary value of the current node
		string temp_value = temp_node->value;
		//if the temp value is the end
		if(temp_value == end)
		{
			//have the predecesor of the temp node be the top value
			temp_node->pred = top_value;
			//set found end to true
			found_end = true;
			//call backtrace to construct vector from end to start
			back_trace(temp_node);
			return;
			break;
		}
		//if the temp node is not explored
		if(!temp_node->explored)
		{
			//set the predecessor of the temp node to be the top
			//value and push the node to the queue
			temp_node->pred = top_value;
			hyper_queue.push(temp_node);
		}
	}
	//while the queue is not empty
	while(!hyper_queue.empty())
	{
		//get the top item from the queue and then pop it
		Node* temp_top = hyper_queue.top();
		hyper_queue.pop();
		//increase the number of expansions since we are about to expand on the 
		//current node
		expansion++;
		//we have explored it so it is true
		temp_top->explored = true;
		//get the temp string binary value
		string temp_value = temp_top->value;
		//if it is the same as the end value
		if(temp_value == end)
		{
			//reduce the number of expansions because we don't expand on the end node
			expansion--;
			//set found path to be true
			found_end = true;
			//then back_trace so that we can construct the vector for 
			//the path
			back_trace(temp_top);
			return;
			break;
		}
		//get the neighbors of the current node that we are on from the
		//priority queue
		set<Node*> temp_neighbors;
		temp_neighbors = graph.find(temp_value)->second;
		//iterate over all of the neighbors
		set<Node*>::iterator it;
		for(it = temp_neighbors.begin(); it != temp_neighbors.end(); it++)
		{
			//getting a temp node for the current neighbor
			Node* neighbor_node = *it;
			//if the neighbor value is the same as the end value
			string neighbor_val = neighbor_node->value;
			if(neighbor_val == end)
			{
				//set the end predecessor to be the temp value, the value we 
				//poped from the queue
				neighbor_node->pred = temp_value;
				//set found to be true and then backtrace to construct the vector path
				found_end = true;
				back_trace(neighbor_node);
				return; 
				break;
			}
			//if the neighbor has not been explored
			if(!neighbor_node->explored)
			{
				//set the predecessor of the neighbor to be the currrnt node 
				//we got from the top of the queue
				neighbor_node->pred = temp_value;
				//push the node on to the queue to be explored
				hyper_queue.push(neighbor_node);
			}
		}
	}
}
//back trace start with the end and work backwords to create the correct path function
void HyperCube::back_trace(Node* curr_node)
{
	//ifthe current value equals the start value
	if(curr_node->value == start)
	{
		//add the current value to the vector and return
		final_path.push_back(curr_node->value);
		return;
	}
	//otherwise
	else
	{
		//push back the current node value onto the final path vector
		final_path.push_back(curr_node->value);
		//get the predecesor of the current node
		string pred_ = curr_node->pred;
		//get the node of the predecesor from find in valid nodes
		Node* pred_node = valid_nodes.find(pred_)->second;
		//recurse on the predecesor
		return back_trace(pred_node);
	}
}
//return if you found the path 
bool HyperCube::found_path()
{
	return found_end;
}
//return the finalpath vector
vector<string> HyperCube::return_path()
{
	return final_path;
}
//return the int number of expansions
int HyperCube::return_expand()
{
	return expansion;
}