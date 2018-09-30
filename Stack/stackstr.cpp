#include <iostream>
#include "stackstr.h"


using namespace std;
//constructor
StackStr::StackStr()
{

}
//destructor
StackStr::~StackStr()
{

}
//definig the empty function
bool StackStr::empty() const
{
	//getting if it is empty fron the list empty funcion
	return list_.empty();
}
//defining the size function
int StackStr::size() const
{
	//getting the size from the list function
	return list_.size();
}
//pushing onto the stack
void StackStr::push(const string &str)
{
	//we will always push onto the stack
	//using insert of the list at index 0 because 
	//stacks are always pushed on from the front
	list_.insert(0, str);
}

//getting from the top of the stack
string StackStr::top()const
{
	//getting the item that is at the top
	//of the list
	return list_.get(0);
}
//removing from the top of the stack
void StackStr::pop()
{
	//if the stack isn't empty
	if(!empty())
	{
		//remove from the top
		//stacks can only pop from the top so 
		//we remove from the top
		list_.remove(0);
	}
}