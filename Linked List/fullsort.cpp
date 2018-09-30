

//the struct of the node
struct Node {
	int value;
	Node *next;
};

//creating the functionfind node, given specific parameters
//trying to find the 
Node* find_insert(Node* insert_node, Node* cur, Node* head)
{
	//if the current value's next is the null pointer,
	//than we know to insert the node at the end of the list
	if(cur->next == nullptr)
	{
		//setting currents next to be the node to insert
		cur->next = insert_node;
		//setting the insert nodes next to be the nullptr so itis
		//at the end of the list
		insert_node->next = nullptr;
		//the head value stays the same so just return the head
		return head;
	}

	//if the value to insert is larger than the head value and the insert node
	//is less than the head's next value, insert it between the two
	else if(insert_node->value > head->value && insert_node->value < head->next->value)
	{
		//having the current's next be the head's next
		cur->next = head->next;
		//the head next value is now the current. 
		head->next = cur;
		//return the head
		return head;
	}

	//if the insert node value is less than the current next value
	else if(insert_node->value < cur->next->value)
	{
		//if the current value that we are on is the head
		if(cur == head)
		{
			//than the new value is the head, so insert next
			//is the current andthe head is now the insert node
			insert_node->next = cur;
			head = insert_node;
		}

		//otherwise it is in the middle of the list
		else
		{
			//have the insert node's next be the current's next 
			//and set current next to be the not to insert
			insert_node->next = cur->next;
			cur->next = insert_node;
		}

		//return the head
		return head;
	}
	
	//otherwise
	else
	{
		//return the recursive function of the same node to insert, the head
		//and currents next value as the value to be used as current
		return find_insert(insert_node, cur->next, head);
		
	}
}

//this is the function unsorted, here we are finding
//where the unsorted insex is in the node, 
//we are given a start value and the cur value to track through out
Node* unsorted_index(Node* start, Node* cur)
{	
	//setting the head to be the cur, this way we will
	//be able to return head and update it throughout the program
	Node* head = cur;
	//if the next node is null, return null
	if(start->next == nullptr)
	{
		return nullptr;
	}

	//if the start value is larger than its next value in the list
	else if(start->value > start->next->value)
	{
		//have the node out of order be the start value
		Node* out_of_order_val = start;
		//set the head to be the next node
		head = start->next;
		//call find insert with the given values to return the head
		head = find_insert(out_of_order_val, cur, head);
		return head;
	}

	//if the starts next value is greater than the starts next next value
	else if((start->next->value) > (start->next->next->value))
	{
		//if start value is less than or equal to start next next value
		if(start->value <= start->next->next->value)
		{
			//than our node that is out of order is start next
			Node* out_of_order_val = start->next;
			//start next is now start next next
			start->next = start->next->next;
			//call find insert to find what the head is with the given input
			head = find_insert(out_of_order_val, cur, head);
			
		}

		//if start value is larger than start next next vlaue
		else if(start->value >= start->next->next->value)
		{
			//than we know that the node out of order is start next next 
			//we set start's next next to be start next next next. 
			Node* out_of_order_val = start->next->next;
			start->next->next = start->next->next->next;
			//than we will call find insert to compute what the head is so we
			//have the correct input
			head = find_insert(out_of_order_val, cur, head);
		}
		//return the head
		return head;

	}

	//other wise
	else
	{
		//call unsorted index on itself and retun. 
		return unsorted_index(start->next, cur);
		
	}

}

//returns true or false for if the function is already sorted or not
bool all_ready_sorted(Node*in, bool sorted)
{
	//if the next value is null
	if(in->next == nullptr)
	{
		//return the sorted boolean
		return sorted;
	}
	//if the in value is less than or equal to the next
	//value, we know these are in order
	else if(in->value <= in->next->value)
	{
		//sorted is true in this senario
		sorted = true;
		//call all_ready_sorted with the in->next 
		//node to iterate through the whole list to 
		//make sure it is all sorted
		return all_ready_sorted(in->next, sorted);
	}

	//if the in value is larger than its next vale
	//than it isn't sorted
	else
	{
		//have sorted be false
		//and return sorted
		sorted = false;
		return sorted;
	}

}

//fullsort, here we willc all fullsort with the input
//nodeand then we will return a completely sorted list
Node* fullsort(Node* in)
{
	bool results = true;
	//if the value that is inputed, return the nullptr pointer
	//since there is no list to reverse
	if(!in)
	{
		return nullptr;
	}

	//calling all ready sorted with in and results for the input bool
	//if this function returns true than we know that we don;t need to 
	//attempt to sort the list and we can just return in which is the head
	else if(all_ready_sorted(in, results))
	{
		return in;
	}

	//if in is not nullptrr
	else
	{
		//create a node cur and set it to in
		Node* cur = in;
		//create the node head
		Node* head;
		//we will return the head node after this functin
		//of unsorted is executed
		head = unsorted_index(in, cur);
		
		//return the head of the fully sorted list
		return head;
	}
}
