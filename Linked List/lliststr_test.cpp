#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

//checking if empty
void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

//my own function that I created. this will
//pritn out all of the words that are in the list
void print_all_words(LListStr *list)
{
	//gets the size of the list
	int size = list->size();
	//iterates through the list until we reach the end
	//prints out all of the values in the list by using the get
	//function
	for(int i = 0; i < size; i++)
	{
		string str = list->get(i);
		cout << str << " ";
	}
	cout << endl;
}
void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

int main() {
	LListStr* list = new LListStr();

	// Check if the list is initially empty.
	checkEmpty(list, true);
	checkSize(list, 0);

	// Insert an item at the head.
	list->insert(0, "CSCI104");

	// Verify the list is not empty
	checkEmpty(list, false);
	checkSize(list, 1);

	// Check if the value is correct.
	checkGet(list, 0, "CSCI104");

	//inserting at the end of the list
	list->insert(1,"World");
	
	//checking that the size is correct
	checkSize(list,2);
	
	//making sure that the value at 1 is correct
	checkGet(list, 1, "World");
	
	//setting the value of the head to be hello
	list->set(0, "Hello");
	
	//making sure that the set function worked
	checkGet(list, 0, "Hello");
	
	//inserting at index 1 
	list->insert(1,"New");
	
	//making sure the size is correct
	checkSize(list, 3);

	//making sure that the value at the index is the correct one
	checkGet(list, 1, "New");

	//inserting at the end of the list
	list->insert(3, "My");

	//checking the size of the list
	checkSize(list, 4);

	//making sure that the value at index 3 is correct
	checkGet(list, 3, "My");

	//making sure that the list isn't empty
	checkEmpty(list, false);

	//printing all of the words in the list
	print_all_words(list);

	//renoving at the front of the list
	list->remove(0);

	//printing our all of the words and making sure the size is correct
	print_all_words(list);
	checkSize(list, 3);

	//removing element at 2
	list->remove(2);

	//printing all of the words in the list
	print_all_words(list);

	//removing the word at index 0
	list->remove(0);
	//printing out all of the words in the life
	print_all_words(list);

	//removing the only element left in the function
	list->remove(0);
	//checking if the list is empty
	checkEmpty(list, true);
	//doing an insert that should fial
	list->insert(10, "fail");
	//making sure the size is correct
	checkSize(list, 0);

	//creating a list size to loop through with a for loop
	int list_size = 5;
	//creating a string to put in the insert function
	string str = "a";
	for(int i = 0; i <= list_size; i++)
	{
		//inserting values into the list, and adding a
		//so that the string that we are adding increases each time
		list->insert(i, str);
		str += "a";
	}

	//printing out all of the words in the list
	print_all_words(list); 

	//setting the value at index 1, to be hello
	list->set(1,"hello");
	//inserting at index 2
	list->insert(2, "world");
	//making sure that the size is the correct size
	checkSize(list, 7);

	//printing out all of the words
	print_all_words(list);

	
	//removing various elements from the from middle and end 
	//and then printing out the results after each removal
	list->remove(5);
	print_all_words(list);
	list->remove(5);
	print_all_words(list);
	list->remove(5);
	print_all_words(list);
	list->remove(3);

	print_all_words(list);

	//checking that the size is the correct value
	checkSize(list, 4);
	//setting the value at index 2
	list->set(2, "CSCI104");
	print_all_words(list);
	//removing the last element in the list
	list->remove(3);
	
	//making sure the size is correct
	checkSize(list, 3);
	//printing after removal
	print_all_words(list);
	//inserting two values at the head and then printing out the values
	list->insert(0,"addison");
	list->insert(0,"Allred");
	print_all_words(list);


	// Clean up memory.
	delete list;
}