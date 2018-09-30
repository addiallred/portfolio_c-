#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;
	private:
		//function for swaping two nodes if they are directly parent/childrem
		void direct_pred_remove(Node<Key, Value>* remove, Node<Key,Value>* pred);
		//recursing to find a node
		Node<Key, Value>* recurseFind(const Key& key, Node<Key, Value>* curr_node) const;
		//recursing to find the smallest vaue
		Node<Key, Value>* SmallestNodeHelper(Node<Key, Value>* curr_node) const;
		//recursive function to adjust the height of the tree
		void adjust_height(Node<Key, Value>* curr_node);
		//setting the root of the tree
		void setRoot(Node<Key, Value>* root);
		//swap two nodes if they are not predecessors of one another
		void swap(Node<Key, Value>* remove, Node<Key, Value>* replace_node);
		//recursive clear function
		void clearHelper(Node<Key, Value>* curr_node);
		//removal function to remove the final node
		void adjustRemoval(Node<Key, Value>* remove);

		//recursive function to check if the tree is balanced
		bool balancedHelper(Node<Key, Value>* curr_node);
		//rcursive function to insert into the tree
		void insertHelper(const std::pair<const Key, Value>& keyValuePair, Node<Key, Value>* curr_node);
	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	if(mRoot != NULL)
	{
		return mRoot->getHeight();
	}
	else
	{
		return 0;
	}
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balancedHelper(Node<Key, Value>* curr_node)
{
	//if the current node is null return true
	if(curr_node == NULL)
	{
		return true;
	}
	//right heigh
	int right_height = 0;
	//if the current nodes right isn't null
	if(curr_node->getRight() != NULL)
	{
		//add the height to the current node from the right child
		right_height += curr_node->getRight()->getHeight();
	}
	//left height
	int left_height = 0;
	//if the current node left isn't null
	if(curr_node->getLeft() != NULL)
	{
		//add the height to the current node from the left child
		left_height += curr_node->getLeft()->getHeight();
	}
	//take the absolute value of the height difference
	int height_diff = abs(left_height - right_height);
	//if it is less than or 1
	if(height_diff <= 1)
	{
		//recurse on the left and right child of the node
		bool right_bal = balancedHelper(curr_node->getRight());
		bool left_bal = balancedHelper(curr_node->getLeft());
		//if either right or left ar false
		if(left_bal == false || right_bal == false)
		{
			//return false
			return false;
		}
		//other wise
		else
		{
			//return true
			return true;
		}
	}
	//if the height is greater
	else
	{
		//return false
		return false;
	}
}
//is balanced function
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	//returing the results from the is balanced function
	bool results;
	results = balancedHelper(mRoot);
	return results;
}

template<typename Key,typename Value>
void BinarySearchTree<Key,Value>::setRoot(Node<Key, Value>* rootv)
{
	mRoot = rootv;
	return;
}
//adjust height function, this will adjust the height
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::adjust_height(Node<Key, Value>* curr_node)
{
	//if the current node is the root
	if(curr_node == mRoot)
	{
		//get ints to calculate the temp height
		int temp_height = 0;
		int right_child_h = 0;
		int left_child_h = 0;
		//if its right child isn't null
		if(curr_node->getRight() != NULL)
		{
			//add the right child value to the height of its right child
			right_child_h += curr_node->getRight()->getHeight();
		}
		//if its left child isn't null
		if(curr_node->getLeft() != NULL)
		{
			//add the left child height of the left node
			left_child_h += curr_node->getLeft()->getHeight();
		}
		//take the max of the right and left height
		temp_height = std::max(right_child_h, left_child_h);
		//set the current node height to be this value plus 1
		curr_node->setHeight(temp_height+1);
		return;
	}
	else
	{
		//get a temp value of the current nodes parent
		Node<Key, Value>* temp = curr_node->getParent();
		//get left and right ints
		int right_child_h = 0;
		int left_child_h = 0;
		//if the curren't nodes right isn't null
		if(curr_node->getRight() != NULL)
		{
			//add the curren't nodes right child to right
			right_child_h += curr_node->getRight()->getHeight();
		}
		//if current nodes->getleft isn't null
		if(curr_node->getLeft() != NULL)
		{
			//set the left child height to be the current nodes
			//left height
			left_child_h += curr_node->getLeft()->getHeight();
		}
		//have the temp height be the max of both
		int temp_height = std::max(right_child_h, left_child_h);
		//set current nodes height to be temp height + 1
		curr_node->setHeight(temp_height +1);
		//call adjust height again because we are not at the node
		adjust_height(temp);
	}
}
//insert helper recursive to insert a node
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insertHelper(const std::pair<const Key, Value>& keyValuePair, Node<Key, Value>* curr)
{
	//if the key is greater than the current ey
	if(keyValuePair.first > curr->getKey())
	{
		//if the right isn't null
		if(curr->getRight() != NULL)
		{
			//call insert on the right node
			insertHelper(keyValuePair, curr->getRight());
		}
		else
		{
			//create a new node with the required values and paramters
			Node<Key, Value>* N = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
			N->setLeft(NULL);
			N->setParent(curr);
			N->setRight(NULL);
			N->setHeight(1);
			curr->setRight(N);
			//adjust the height of the function
			adjust_height(curr);
			return;
		}
	}
	else
	{
		//if the left node isn't null
		if(curr->getLeft() != NULL)
		{
			//call the function recursivly on the left
			insertHelper(keyValuePair, curr->getLeft());
		}
		else
		{
			//create a new node with the required parameters
			Node<Key, Value>* N = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
			curr->setLeft(N);
			N->setLeft(NULL);
			N->setParent(curr);
			N->setRight(NULL);
			N->setHeight(1);
			//adjust the height so that it is correct
			adjust_height(curr);
			//return
			return;
		}
	}
}
/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
//insert a node
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//if the root is null
	if(mRoot == NULL)
	{
		//create a new node with the specified values set the root to be the new nod
		Node<Key, Value>* N = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		mRoot = N;
		//set the values
		mRoot->setParent(NULL);
		mRoot->setLeft(NULL);
		mRoot->setRight(NULL);
		mRoot->setHeight(1);
	}
	else if(internalFind(keyValuePair.first) == NULL)
	{
		insertHelper(keyValuePair, mRoot);
	}
}
/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
//adjusting the removal so that we complete it and remove the node
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::adjustRemoval(Node<Key, Value>* remove)
{
	//if the node has no childerm
	if(remove->getRight() == NULL && remove->getLeft() == NULL)
	{
		//if its parent isn't null
		if(remove->getParent() != NULL)
		{
			//get the parent 
			Node<Key, Value>* parent = remove->getParent();
			//if the parents left isn't null and if it is remove
			if(parent->getLeft() != NULL)
			{
				if(parent->getLeft() == remove)
				{	
					//parents left child is null
					parent->setLeft(NULL);
				}
			}
			//if the parents right isn't null and if it is remove
			if(parent->getRight() != NULL)
			{
				if(parent->getRight() == remove)
				{
					//parents right child is null
					parent->setRight(NULL);
				}
			}
			//adjust the height based on the parent
			adjust_height(parent);
		}
		//delete the node
		delete remove;
		
	}
	//if the left child isn't null but the right is
	else if(remove->getLeft() != NULL && remove->getRight() == NULL)
	{
		//getthe left child of the remove node
		Node<Key, Value>* left_node = remove->getLeft();
		//if the remove node parent isn't null
		if(remove->getParent() != NULL)
		{
			//get the parent and set lefts parent to be the
			//parent node
			Node<Key, Value>* parent = remove->getParent();
			left_node->setParent(parent);
			//if the parents left is remove
			if(parent->getLeft() == remove)
			{
				//parent left is the left node
				parent->setLeft(left_node);
			}
			else
			{
				//parents right is the left node
				parent->setRight(left_node);
			}
			
		}
		else
		{
			//left nodes parent is null and is now the root
			left_node->setParent(NULL);
			mRoot = left_node;
		}
		//delete the node to remove
		delete remove;
		//adjust the hieghts based of of the left node
		adjust_height(left_node);
		
	}
	//if it only has a right child
	else if(remove->getLeft() == NULL && remove->getRight() != NULL)
	{
		//get the right child
		Node<Key, Value>* right_node = remove->getRight();
		//if its parent isn't null
		if(remove->getParent() != NULL)
		{
			//get the parent node and set the right nodes parent to be
			//removes parent
			Node<Key, Value>* parent = remove->getParent();
			right_node->setParent(parent);
			//if parents left is remove set parents left to be the right
			//node
			if(parent->getLeft() == remove)
			{
				parent->setLeft(right_node);
			}
			else
			{
				//set parents right to be the right node
				parent->setRight(right_node);
			}
		}
		else
		{
			//right nodes parent is null
			right_node->setParent(NULL);
			mRoot = right_node;
		}
		//delete the node to remove
		delete remove;
		//call adjust height on the right node
		adjust_height(right_node);
	}
}
//swap function to swap two nodes in a tree
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::swap(Node<Key, Value>* remove, Node<Key, Value>* replace_node)
{
	//get two new nodes that will be copies of both remove and replace node
	//and set their values to be the same as removes and replace
	Node<Key, Value>* temp = new Node<Key, Value>(0, 0, replace_node->getParent());
	Node<Key, Value>* remove_t = new Node<Key, Value>(0, 0, remove->getParent());
	remove_t->setLeft(remove->getLeft());
	remove_t->setRight(remove->getRight());
	remove_t->setHeight(remove->getHeight());
	remove_t->setParent(remove->getParent());
	temp->setLeft(replace_node->getLeft());
	temp->setRight(replace_node->getRight());
	temp->setHeight(replace_node->getHeight());
	temp->setParent(replace_node->getParent());
	//if the remove does have a parent
	if(remove->getParent() != NULL)
	{
		//if the parents left is remove 
		if(remove->getParent()->getLeft() == remove)
		{
			//set parents left to be the replace node
			remove->getParent()->setLeft(replace_node);
		}
		else
		{
			//set parents right to be the replace node
			remove->getParent()->setRight(replace_node);
		}
	}
	//if the replace node has a parent
	if(replace_node->getParent() != NULL)
	{
		//if paren'ts left is replace nod
		if(replace_node->getParent()->getLeft() == replace_node)
		{
			//parnest left to be remove
			replace_node->getParent()->setLeft(remove);
		}
		else
		{
			//set parent or replace node right to be remove
			replace_node->getParent()->setRight(remove);
		}
	}
	//if removes parent isn't null
	if(remove_t->getParent() != NULL)
	{
		//set replace node parent to be remove's parent
		replace_node->setParent(remove_t->getParent());
	}
	else
	{
		//replace node parent is null and is now the 
		//root since remove is the root
		replace_node->setParent(NULL);
		mRoot = replace_node;
	}
	//if the temp parent isn't null
	if(temp->getParent() != NULL)
	{
		//set remove to parent to be temps parent
		remove->setParent(temp->getParent());
	}
	else
	{
		//set remove to be null if remp has no parent
		remove->setParent(NULL);
	}
	//if remove get left isn't null
	if(remove_t->getLeft() != NULL)
	{
		//set removes left parent to be the replace node for the left
		//replace nodesleft to be removes left child
		remove_t->getLeft()->setParent(replace_node);
		replace_node->setLeft(remove_t->getLeft());
	}
	else
	{
		//remove has no left child so set left to be null
		replace_node->setLeft(NULL);
	}
	//if removes right isn't null
	if(remove_t->getRight() != NULL)
	{
		//set remvoes righ child parent to be replace node and replace
		//node right child to be removes right
		remove_t->getRight()->setParent(replace_node);
		replace_node->setRight(remove_t->getRight());
	}
	else
	{
		//remove has no righ child so right is null
		replace_node->setRight(NULL);
	}
	//if the replace node right child isn't null
	if(temp->getRight() != NULL)
	{
		//have the right child of the replace node have its parent be remove
		//and remove's right be the right child of replace
		temp->getRight()->setParent(remove);
		remove->setRight(temp->getRight());
	}
	else
	{
		//removes right is null
		remove->setRight(NULL);
	}
	//if replaces left isn't null
	if(temp->getLeft() != NULL)
	{
		//set replace left child parent to be remove
		//and removes left child to be replace left child
		temp->getLeft()->setParent(remove);
		remove->setLeft(temp->getLeft());
	}
	else
	{
		//remove left is null
		remove->setLeft(NULL);
	}
	//delete the two nodes allocated
	delete remove_t;
	delete temp;
}
//direct pred, this is if the node we are going to swap the remove node is the direct
//left child of the remove node
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::direct_pred_remove(Node<Key, Value>* remove, Node<Key,Value>* pred)
{
	//get a temp copy of the node's we want to remove
	Node<Key, Value>* temp_r = new Node<Key, Value>(0,0, remove->getParent());
	//initalize all of the values of the temp removeso they match with removes
	temp_r->setParent(remove->getParent());
	temp_r->setLeft(remove->getLeft());
	temp_r->setRight(remove->getRight());
	//if removes parent isn't null
	if(remove->getParent() != NULL)
	{
		//get the parent
		pred->setParent(remove->getParent());
		//if the parent get left isn't null
		if(remove->getParent()->getLeft() != NULL)
		{
			//if remove's parent get left is remove
			//set remove's parent's left to be the predecessor, node we are swaping with
			if(remove->getParent()->getLeft() == remove)
			{
				remove->getParent()->setLeft(pred);
			}
		}
		//if remove's parents right child isn't null 
		if(remove->getParent()->getRight() != NULL)
		{
			//if the parents right child is remove
			if(remove->getParent()->getRight() == remove)
			{
				//set the parents right child to be the predecessor
				remove->getParent()->setRight(pred);
			}
		}
	}
	//other whise
	else
	{
		//set the root to be pred since only one node can have a null parent
		mRoot = pred;
		//set parent to be null
		pred->setParent(NULL);
	}
	//the parent of remove will be the pred since it is the exact value it needs to swap with
	remove->setParent(pred);
	//if the right of the pred is not null
	if(pred->getRight() != NULL)
	{
		//set removes right to be preds right and have preds right update
		//the parent to be remove
		pred->getRight()->setParent(remove);
		remove->setRight(pred->getRight());
	}
	else
	{
		//if no right child set remove right to be null
		remove->setRight(NULL);
	}
	//if preds left isn't null
	if(pred->getLeft() != NULL)
	{
		//remove left child to be pred's left child and have
		//pred's left child update its parent to be remove
		pred->getLeft()->setParent(remove);
		remove->setLeft(pred->getLeft());
	}
	else
	{
		//if no left child set remove left to null
		remove->setLeft(NULL);
	}
	//the predecessors left will be the remove
	pred->setLeft(remove);
	//if the right of the remove value isn't null
	if(temp_r->getRight() != NULL)
	{
		//have the pred right be the removes original right
		//and update this nodes parent to be the pred
		pred->setRight(temp_r->getRight());
		temp_r->getRight()->setParent(pred);
	}
	else
	{
		//otherwise pred is null
		pred->setRight(NULL);
	}
	//deallocate the temp copy
	delete temp_r;
}
//remove function, given a key, remove a specific node
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	//if we can only find the key in the tree
	if(internalFind(key) != NULL)
	{
		//get the node that we will remove
		Node<Key, Value>* remove = internalFind(key);
		//if the node is the root
		if(remove == mRoot && remove->getRight() == NULL && remove->getLeft() == NULL)
		{
			//set the root to be null and delete the node
			mRoot = NULL;
			delete remove;
		}
		//other wise
		else
		{
			//if the left and right are null
			if(remove->getRight() == NULL && remove->getLeft() == NULL)
			{
				//call adjust removal, don't need to worry about changing
				//with predecessory
				adjustRemoval(remove);
			}
			//if the node is the smalles node
			else if(remove == getSmallestNode())
			{
				//just call adjust removal because if will only have one child
				adjustRemoval(remove);
			}
			//if the node only have one child
			else if(remove->getLeft() != NULL && remove->getRight() == NULL)
			{
				//if it is the root
				if(remove == mRoot)
				{
					//set the root of the tree to be the left child
					mRoot = remove->getLeft();
				}
				//adjust the tree to remove the node
				adjustRemoval(remove);
			}
			//if the node has only one child on the right
			else if(remove->getRight() != NULL && remove->getLeft() == NULL)
			{
				//if the node is the root
				if(remove == mRoot)
				{
					//set the root to be the right child
					mRoot = remove->getRight();
				}
				//adjust the tree to remove the node
				adjustRemoval(remove);
			}
			//if it has two child
			else
			{
				//get the left child
				Node<Key, Value>* left_remove = remove->getLeft();
				//while the right of the left child is not null, continue
				//to find the correct left which will be the predecessor
				while(left_remove->getRight() != NULL)
				{
					if(left_remove->getRight() != NULL)
					{
						left_remove = left_remove->getRight();
					}
				}
				//if the predecesor isn't the same as the remove lefts' call swap
				if(left_remove->getKey() != remove->getLeft()->getKey())
				{
					swap(remove, left_remove);
				}
				//if the predecesor is the same as the remove left
				else
				{
					//call direct pred since the node to switch with is a direct
					//predecesor
					direct_pred_remove(remove, left_remove);
				}
				//call adjust removal
				adjustRemoval(remove);
			}
		}
	}
}
/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
//clearing the tree 
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* curr_node)
{
	//if the current node get left is not null than recurse on the function
	//using the get left of the cur node
	if(curr_node->getLeft() != NULL)
	{
		clearHelper(curr_node->getLeft());
	}
	//if the current node get right is not null, than recurse on the function 
	//using get right on the current node
	if(curr_node->getRight() != NULL)
	{
		clearHelper(curr_node->getRight());
	}
	//once we get to the correct node delete it
	delete curr_node;
}
//clear the tree created
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	//if the root is not null recurse on clear with the root
	if(mRoot != NULL)
	{
		clearHelper(mRoot);
	}
	//set mRoot to be null
	mRoot = NULL;
}

template<typename Key, typename Value>
//finding the smalles node for the function recursively
Node<Key, Value>* BinarySearchTree<Key, Value>::SmallestNodeHelper(Node<Key, Value>* curr_node) const
{
	//if the current nodes get left is null, than it is the smallest node
	if(curr_node->getLeft() == NULL)
	{
		return curr_node;
	}
	else
	{
		//recurse on the left node to continue to find the smallest node
		if(curr_node->getLeft() != NULL)
		{
			Node<Key, Value>* left = curr_node->getLeft();
			return SmallestNodeHelper(left);	
		}
		else
		{
			return curr_node;
		}
	}
}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
//get smallest value
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	//calling recursive helper function for the smallest node
	if(mRoot != NULL)
	{
		Node<Key, Value>* smallest = SmallestNodeHelper(mRoot);
		return smallest;
	}
	else
	{
		return NULL;
	}
	
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
//recurse find helper
Node<Key, Value>* BinarySearchTree<Key, Value>::recurseFind(const Key& key, Node<Key, Value>* curr_node) const
{
	//if the current node is null 
	if(curr_node == NULL)
	{
		//return
		return NULL;
	}
	//if the key is the current nodes key return the current node
	else if(key == curr_node->getKey())
	{
		return curr_node;
	}
	else
	{
		//ifthe key is lessthan the current node and the current node left isn't null
		if(key < curr_node->getKey() && curr_node->getLeft() != NULL)
		{
			//recurse on the left child
			return recurseFind(key, curr_node->getLeft());
		}
		//if the key is greater than the current node and thecurrent node right isn't null
		else if(key > curr_node->getKey() && curr_node->getRight() != NULL)
		{
			//reucrse on the right child
			return recurseFind(key, curr_node->getRight());
		}
		//if otherwise
		else
		{
			//return null
			return NULL;
		}
	}
}
template<typename Key, typename Value>
//internal find function
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	//calling the recursive helper on the root and the povided key it will return
	//a node 
	Node<Key, Value>* result = recurseFind(key, mRoot);
	return result;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif