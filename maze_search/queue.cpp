/* 
queue.cpp

Author: Addison Allred 

Short description of this file:
This file helps create that tools that we are able
to utilize by creating the queue. these tools will
help us to know what locations we have in our queue
and moer in general where we are, what location, 
and if our queue is empty
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete[] contents;
}

// insert a new Location at the end/back of our list   
void Queue::add_to_back(Location loc) {
	//saying that the tail, the new item being but in
	//to the queue is the location being passed through
	//we then increment tail by one so that it is 
	//at the correct index of an open index in contenets
	contents[tail] = loc;
	tail++;
   
}

// return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {

	//increasing the value of the head, by doing so we are
	//moving the value of which we are evaluating to the 
	//next item in the array of contents. 
	//so we are not actually removing anything from the array, 
	//however we are moving what we are looking at so in 
	//some indirect way what was originally our head is now
	//out of our scope
	head++;
	//returning the content value of what we were just on
	//beore we increased the hea value
	return contents[head-1];
	 
}

// is this Queue empty? (did we extract everything added?)
// this is complete, you don't need to change it.
bool Queue::is_empty() {
   return head == tail;
}