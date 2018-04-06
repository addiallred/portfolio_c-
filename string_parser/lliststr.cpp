#include "lliststr.h"
#include <iostream>

using namespace std;

//initializing the constructor
LListStr::LListStr()
{
	size_ = 0;
	head_ = NULL;
	tail_ = NULL;
}

//creating the destroctore
LListStr::~LListStr()
{
	//if the list is empty than we don't need to deallocate 
	//any mempry
	if(empty())
	{
		return;
	}
	//if the list is not epty
	else
	{
		//create a temp item to point to the item next
		//after the head
		Item* curr = head_->next;
		//while we continue to move the current item
		//and it is not equal to the head
		while(curr != head_)
		{
			//creating the temp variable to delte
			//and setting it to the curr value
			Item* temp_curr = curr;
			//updating the curr value so that next time
			//we use it it will be pointin gto the correct 
			//next variable
			curr = curr->next;
			//deleting the temperary variable
			delete temp_curr;


		}
		//once everything is deleted delete the head
		//whioch is the lead item in the list
		delete head_;
	}
}

//returning the size
int LListStr::size() const
{
	return size_;
}


//returning if empty or not when called
bool LListStr::empty() const
{
	//if the size is equal to 0
	//than return that the list is emtpy
	if(size() == 0)
	{
		return true;
	}

	//else if the list isn't empty
	//return false
	else
	{
		return false;
	}
}

//creating the function to see if it is a valid location
bool LListStr::valid_location(int location, bool insert_type) const
{
	//if we are wanting to insert into the list entere here
	//to see if the location provided is valied
	if(insert_type)
	{
		//if the location is greater that or equal to 0
		//or is less than or equal to the size of the list
		//return true that the location entered is valid
		if(location >= 0 && location <= size())
		{
			return true;
		}
		//if it isn't a valid location return false
		else
		{
			return false;
		}
	}

	//if we are not trying to insert
	else
	{
		//if the location provided is equal to 0 or greater than 0
		//and it is less than the size, return true for the location
		//inputed as a valid location
		if(location >= 0 && location < size())
		{
			return true;
		}

		//if the location provided is out of bounds return false 
		else
		{
			return false;
		}
	}
	
}

//creating the fucntion to insert based off of a given
//location and a string value that was inputed. 
void LListStr::insert(int location, const string &value)
{
	//setting the insert value to true so we know when checking 
	//if the location entered is a valid location
	bool insert_type = true;

	//if the list is empty and the locaiton is larger than any
	//value except 0, return because we can't add 
	//at a invalid location to a list that isn't 
	//a valid location because no location exist 
	//for an empty list if it isn't 0
	if(empty() && location > 0)
	{
		return;
	}

	//if the list is empty and the location input is
	//0 than this is a valid location so we can
	//start the list
	else if(empty() && location == 0)
	{
		//creating a new node to insert into the list
		Item* new_node = new Item;
		//setting the values of the new node to be the
		//input value and setting the next values to 
		//point to itself since it is a doubly
		//linked list setting the head and tail
		//to the new node created and increasing the 
		//size
		new_node->val = value;
		new_node->next = new_node;
		new_node->prev = new_node;
		head_ = new_node;
		tail_ = new_node;
		size_++;
	}

	//if the location is 0 and the list isn't empty
	//meaning that we are trying to insert at the head
	else if(location == 0 && (!empty()))
	{
		//create a new node updating the size of the list
		//and setting the value of the new node we created
		//then updating the next and prev value of the new
		//node and then updating the correct values of the 
		//head and the tail so that we can insert the
		//new node to be in the front
		//then setting the head equal to the new node
		Item* new_node = new Item;
		size_++; 
		new_node->next = head_;
		new_node->val = value;
		new_node->prev =  tail_;
		tail_->next = new_node;
		head_->prev = new_node;
		head_ = new_node;
	}

	//if the location inputted is a valid location
	//and it is not attempting to insert in the front
	else if(valid_location(location, insert_type))
	{
		//creating a new node
		Item* new_node = new Item;
		//setting the new node value to the input value
		new_node->val = value;
		//getting the Item at the input location
		//for where we are going to input the new node
		Item* replace_node = location_to_implement(location, insert_type);
		//updating the values of the new node to have
		//its next value be the item's next
		// item at the locaiton 
		//we are looking to place the new node at
		//and its previous value to be the replacement
		//node. 
		new_node->next = replace_node->next;
		new_node->prev = replace_node;
		//updating the replacement nodes next previous
		//to be the new node and the replacement node next
		//to be the new node
		replace_node->next->prev = new_node;
		replace_node->next = new_node;
		//if the location is equal to the size of the list,
		//than the new node is  the tail
		if(location == size())
		{
			tail_ = new_node;
		}

		//now updating the size of the list
		//since we added an item
		size_++;
	}
}

//deffing the function for remove given a location
void LListStr::remove(int location)
{
	//since we aren't inserting, we set insert
	//to false so we can have the correcrt calculation
	//for valid location and returning an item
	bool insert_type = false;
	//if the list is empty or the location
	//placed in is not a valid location
	//than return and don't execute any removals
	if(empty() || (!valid_location(location, insert_type)))
	{
		return;
	}

	//if we are trying to remove from the front
	else if(location == 0)
	{
		//getting the item that we should remove based on the 
		//location and the function we are trying to 
		//get the item for
		Item* remove_ = location_to_implement(location, insert_type);
		//setting the head to be the removes next
		head_ = remove_->next;
		//updating the removes previous next to be the removes next
		remove_->prev->next = remove_->next;
		
		remove_->next->prev = remove_->prev;
		//deleting the value of remove
		delete remove_;
		
		//lowering the size of the 
		size_--;
	}

	//if we are trying to remove from the back
	else if(location == size_-1)
	{
		//getting the item that we should remove based
		//on the location and the function we are trying to
		//execute
		Item* remove_ = location_to_implement(location, insert_type);
		//setting the tail to be the previous element of remove
		tail_ = remove_->prev;
		//updating the values of the other elements
		//in the linked list so that the 
		//element we are trying to remove is no longer
		//in the list by prevs and next
		remove_->prev->next = remove_->next;
		remove_->next->prev = remove_->prev;
		//deleting the element we want to remove
		delete remove_;
	
		//reducing the size
		size_--;
	}

	//other wise we are trying to remove from
	//the middle
	else
	{
		//getting the element that we want to remove based
		//off of the location that was pased in
		Item* remove_ = location_to_implement(location, insert_type);
		//updating hte removes previous and next values
		//so that they go to the correct values so that
		//remove node is not in the list anymore
		remove_->prev->next = remove_->next;
		remove_->next->prev = remove_->prev;
		//delete the remove node
		delete remove_;
		
		//decrease the size
		size_--;
		
	}
}

//define the function set so given a location and string
//we can update the value at that location
void LListStr::set(int location, const string &value_new)
{
	//have insert be false because we aren't inserting
	bool insert_type = false;
	//if the list is empty or the location isn't valid
	//return
	if(empty() || (!valid_location(location, insert_type)))
	{
		return;
	}

	else
	{
		//other wise get the item we want to update
		//by calling the implementation function with
		//the proper location
		Item* update_value = location_to_implement(location, insert_type);
		//update the value of the node by setting it equal
		//to the value passed in
		update_value->val = value_new;

	}
}

//defining the function to return the value at a location
string LListStr::get(int location) const
{
	//have insert be false because we are not trying to 
	//insert
	bool insert_type = false;
	//if the list is empty or the locaitn isn't valid
	//than return an empty string
	if(empty() || (!valid_location(location, insert_type)))
	{
		return " ";
	}
	
	//other wise
	else
	{
		//get the item that we want to update
		//by implementing the location function
		Item* out_put_value = location_to_implement(location, insert_type);
		//returning the output item value
		return out_put_value->val;
	}
}

//defining the location to implement function
//this takes in a given location value and what type
//of function we want by true or false and returns the
//desired item
LListStr::Item* 
LListStr::location_to_implement(int location, bool insert_type) const
{
	//set the current location to be 0
	int curr_location = 0;
	//setting the item to return to be the head
	Item* return_item = head_;
	//if we are trying to insert into the list
	if(insert_type)
	{
		//while location -1 does not equal the current
		//location, update the return item
		//to be the return items next and update the 
		//current location value
		while(location-1 != curr_location)
		{
			return_item = return_item->next;
			curr_location++;
		}
	}

	//other wise enter here if we are trying to do any other 
	//function
	else
	{
		//while the location is not equal to current
		//locatin, update the return item to be the return
		//items next and then increase the value of the curr
		//location
		while(location != curr_location)
		{
			return_item = return_item->next;
			curr_location++;
		}
	}	
	//return the item we want to use for the function
	return return_item;
}