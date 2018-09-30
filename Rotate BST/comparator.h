#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <iostream>
#include "node.h"
//comparator for the priority queue
struct Comparator
{
	//overloading the () for comparision
	bool operator()(Node* lhs, Node* rhs);
};
//comparison overload of () taking two nodes and comparing them
bool Comparator::operator()(Node* lhs, Node* rhs)
{
	//if the f value of the left is less than the right
	if(lhs->f_calc < rhs->f_calc)
	{
		return false;
	}
	//if the f value of right is less than that of left
	else if(lhs->f_calc > rhs->f_calc)
	{
		return true;
	}
	//if the f value are equal for both nodes
	else if(lhs->f_calc == rhs->f_calc)
	{
		//look at the heuristic and return true if h of l is greater than r
		//false if other way around
		if(lhs->heuristic < rhs->heuristic)
		{
			return false;
		}
		else if(lhs->heuristic > rhs->heuristic)
		{
			return true;
		}
		//if h of lhs and rhs are equal to one another
		else if(lhs->heuristic == rhs->heuristic)
		{
			//get the string values, binary string, of both nodes
			std::string value1 = lhs->value;
			std::string value2 = rhs->value;
			//iterate over the strings and determin which one is bigger
			//based on which string you see a 1 in first
			for(int i = 0; i < int(value1.length()); i++)
			{
				if(value2[i] == '1' && value1[i] != '1')
				{
					return lhs < rhs;
					break;
				}
				else if(value1[i] == '1' && value2[i] != '1')
				{
					return lhs > rhs;
					break;
				}
			}
		}
	}
	//if we reached the end return true nothing to compare
	//return true;
};

#endif