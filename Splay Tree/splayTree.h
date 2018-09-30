#include "rotateBST.h"
#include <iostream>
using namespace std;
//splay class
template<typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
//public functions
public:
	//creating the constructor
	SplayTree();
	//destructor
	~SplayTree();
	//insert function to take pair and makea new node and insert it into the tree
	void insert(const std::pair<const Key, Value>& keyValuePair);
	//removing the node from the tree given a specific key
	void remove(const Key& key);
	//returning an iterator of a node that we are trying to find
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	//find the minimum value that is in the tree and return the iterator
	//to this node
	typename SplayTree<Key, Value>::iterator findMin();
	//find the node with themaximum value in the tree and return an iterator
	//to this node
	typename SplayTree<Key, Value>::iterator findMax();
	//deleting the minimum leaf node in the tree
	void deleteMinLeaf();
	//deletingn the maximmum leaf node in the tree
	void deleteMaxLeaf();
protected:
	//splay function, this will actually splay the tree
	void splay(Node<Key, Value>* r);
private:
	//recursive find, this will find the node in the tree if it isn't in the 
	//tree than it will find the node right before we realized that the 
	//node wasn't in the tree and it will return this node
	Node<Key, Value>* recursiveFind(Node<Key, Value>* curr_node, const Key& key);
};
//splay tree constructor
template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{

}
//destructor of the splay tree
template<typename Key, typename Value>
SplayTree<Key, Value>::~SplayTree()
{
	//clearing the splay tree once we ar done using it
	this->clear();
}
//splay function to splay a node to be the root of the tree
template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>* curr_node)
{
	//if the root is equal to the current node
	if(this->mRoot == curr_node)
	{
		//return
		return;
	}
	//if the current node is null return
	else if(curr_node == NULL)
	{
		return;
	}
	else
	{
		//get the parent of the current node
		Node<Key, Value>* parent = curr_node->getParent();
		//if the parent does not have a parent, so the current node
		//doesn't have a grandparent
		if(parent->getParent() == NULL)
		{
			//if the parents key is greater than the current nodes key
			if(parent->getKey() > curr_node->getKey())
			{
				//rotate the parent to the right 
				this->rightRotate(parent);
			}
			//if the current node is greater than the parent
			else
			{
				//left rotate the parent 
				this->leftRotate(parent);
			}
		}
		//if the parent does have a grandparent
		else
		{
			//get the parent of the parent 
			Node<Key, Value>* g_parent = parent->getParent();
			//if the parents value is less than the current nodes value
			if(parent->getKey() < curr_node->getKey())
			{	
				//if the grandparents key is less than the parents key
				if(g_parent->getKey() < parent->getKey())
				{
					//rotate the grandparent to the left
					this->leftRotate(g_parent);
					//rotate the parent to the left
					this->leftRotate(parent);
					//if the current node is the root return
					if(curr_node == this->mRoot)
					{
						return;
					}
					else
					{
						//if the current node is not the root, than 
						//splay the tree again
						return splay(curr_node);
					}
				}
				//IF THE GRANPARENTS KEY IS GREATER THAN THE PARENTS KEY
				else
				{
					//left rotate the parent
					this->leftRotate(parent);
					//right rotate the grand parent
					this->rightRotate(g_parent);
					//if the current node is now the root return
					if(curr_node == this->mRoot)
					{
						return;
					}
					//otherwise
					else
					{
						//recurse on the splay tree and on the current
						//node again til it is the root
						return splay(curr_node);
					}
				}
			}
			//if the parent key is greater than the current node key
			else
			{
				//if the grandparents key is greater than the parents key
				if(g_parent->getKey() > parent->getKey())
				{
					//right rotate the grandparent
					this->rightRotate(g_parent);
					//right rotate the parent
					this->rightRotate(parent);
					//if the current node is the root return
					if(curr_node == this->mRoot)
					{
						return;
					}
					else
					{
						//if the current node is not the root splay again
						//on the current node
						return splay(curr_node);
					}
				}
				//if the grandparent key is greater than the parents key
				else
				{
					//right rotatate on the parent
					this->rightRotate(parent);
					//left rotate on the grandparent
					this->leftRotate(g_parent);
					//if the current node is the root than return
					if(curr_node == this->mRoot)
					{
						return;
					}
					else
					{
						//if the current node is not the root splay again
						//on the current node
						return splay(curr_node);
					}
				}
			}
		}
	}
}
//recursively finding a node in the tree and either returning the exact node in the tree or the
//node where we ended when we discovered that the node we were searching for was not in our tree
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::recursiveFind(Node<Key, Value>* temp_node, const Key& key)
{
	//if the current nodes temp value is equal to the current nodes value
	if(temp_node->getKey() == key)
	{
		return temp_node;
	}
	//if the temp nodes key value is greater than our goal key
	if(temp_node->getKey() > key)
	{
		//if the left of the temp node is not null
		if(temp_node->getLeft() != NULL)
		{
			//recurse on the temp nodes left value to continue to look for the key
			return recursiveFind(temp_node->getLeft(), key);
		}
		else
		{ 
			//if it is null return this node as the last resulting node
			return temp_node;
		}
	}
	//if the temp nodes key value is les than our goal key
	else
	{
		//if the right of the temp node is not null
		if(temp_node->getRight() != NULL)
		{
			//return recursively on the right of the temp node 
			return recursiveFind(temp_node->getRight(), key);
		}
		else
		{
			//if the temp node doesn't have a right return this value
			return temp_node;
		}
	}
}
//removing a node from the tree
template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	//if the root of the tree is null return nothing to remove
	if(this->mRoot == NULL)
	{
		return;
	}
	//if the key is actually in the tree
	else if(BinarySearchTree<Key, Value>::internalFind(key) != NULL)
	{
		//get the node with the correspoing key value 
		Node<Key, Value>* temp_node = BinarySearchTree<Key, Value>::internalFind(key);
		//if the nodes parent is not null
		if(temp_node->getParent() != NULL)
		{
			//if the node has left and right children
			if(temp_node->getRight() != NULL && temp_node->getLeft() != NULL)
			{
				//get the left child
				Node<Key, Value>* left_remove = temp_node->getLeft();
				//while the right of the left child is not null, continue
				//to find the correct left which will be the predecessor
				while(left_remove->getRight() != NULL)
				{
					if(left_remove->getRight() != NULL)
					{
						left_remove = left_remove->getRight();
					}
				}
				//get the parent of the node that is the predecusor of the node
				//we wish to remove
				Node<Key, Value>* parent_node = left_remove->getParent();
				//if the parent node of the predecessor is the same node
				//as the left remove
				if(parent_node->getKey() == temp_node->getKey())
				{
					//set the parent node of the node to remove to be its predecssor
					parent_node = left_remove;
				}
				//call remove 
				BinarySearchTree<Key, Value>::remove(key);
				//splay the parent node to the root of the tree
				splay(parent_node);
			}
			//if the node has only a left or right child
			else
			{
				//temp node is now the parent of the temp node
				temp_node = temp_node->getParent();
				//call remove on the tree
				BinarySearchTree<Key, Value>::remove(key);
				//splay the parent node of the node we just removed 
				//to now be the root of the tree
				splay(temp_node);
			}
		}
		//if the parent node is null
		else
		{
			//if the temp node has left and right children
			if(temp_node->getLeft() != NULL && temp_node->getRight() != NULL)
			{
				//get the left child
				Node<Key, Value>* left_remove = temp_node->getLeft();
				//while the right of the left child is not null, continue
				//to find the correct left which will be the predecessor
				while(left_remove->getRight() != NULL)
				{
					if(left_remove->getRight() != NULL)
					{
						left_remove = left_remove->getRight();
					}
				}
				//get the parent node of the predecessor we are going to switch
				//our node we want to remove with
				Node<Key, Value>* parent_node = left_remove->getParent();
				//if the parent node and the node to remove are the same
				if(parent_node->getKey() == temp_node->getKey())
				{
					//the parent node is just the left remove node for 
					//the node to remove
					parent_node = left_remove;
				}
				//remove the node we want to get rid off
				BinarySearchTree<Key, Value>::remove(key);
				//splay the parent node to be the roos of the tree
				splay(parent_node);
			}
			else
			{
				//just call binary remove on the tree
				BinarySearchTree<Key, Value>::remove(key);
			}
		}
	}
	//if the key is not in the tree
	else
	{
		//call recursive find to find the node where we find that the node is not in the 
		//tree
		Node<Key, Value>* temp_node = recursiveFind(this->mRoot, key);
		//splay that node to be the root of the tree
		splay(temp_node);
	}
}
//insert function for the splay tree
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//if the key is in the splay tree
	if(BinarySearchTree<Key, Value>::internalFind(keyValuePair.first) != NULL)
	{
		//splay the node that the key is stored at to be the root of the tree
		splay(BinarySearchTree<Key, Value>::internalFind(keyValuePair.first));
	}
	//otherwise
	else
	{
		//insert the key value pair into the insert function from bst
		BinarySearchTree<Key,Value>::insert(keyValuePair);
		//splay the node that we just inserted into the tree to be the 
		//root of the tree
		splay(BinarySearchTree<Key, Value>::internalFind(keyValuePair.first));
	}
}
//delete the max leaf
template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	//if the root is null return
	if(this->mRoot == NULL)
	{
		return;
	}
	else
	{
		//get the root of the tree as the temp node
		Node<Key, Value>* temp_node = this->mRoot;
		//while the temp node's right child is not null
		//continue to set the temp node to the right child until
		//we reach the max value
		while(temp_node->getRight() != NULL)
		{
			if(temp_node->getRight() != NULL)
			{
				temp_node = temp_node->getRight();
			}
		}
		//call the remove function 
		remove(temp_node->getKey());
	}
}
//delte the min leaf in the tree
template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	//if the root is null return
	if(this->mRoot == NULL)
	{
		return;
	}
	else
	{
		//get the root of the tree
		Node<Key, Value>* temp_node = this->mRoot;
		//while the temp node is not the minimum node in the tree
		//continue to look at the left child until the left child is null
		while(temp_node->getLeft() != NULL)
		{
			if(temp_node->getLeft() != NULL)
			{
				temp_node = temp_node->getLeft();
			}
		}
		//call the remove function on the node
		remove(temp_node->getKey());
	}
}
//find function will return an iterator to the key
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	//if the root is null, return null
	if(this->mRoot == NULL)
	{
		return NULL;
	}
	//find the key in the tree by calling internal find
	Node<Key, Value>* temp = BinarySearchTree<Key, Value>::internalFind(key);
	//if the temp node is not null
	if(temp != NULL)
	{
		//get the node with the corresponding find key
		Node<Key, Value>* temp_node = this->internalFind(key);
		//splay that node to the top of the tree
		splay(temp_node);
		//create an iterator to this tree and then return it
		typename SplayTree<Key, Value>::iterator it(this->internalFind(key));
		return it;
	}
	else
	{
		//since the key is not in the  tree call recursive find and 
		//find the node just before we realized that the key is not in the tree
		Node<Key, Value>* temp_node;
		temp_node = recursiveFind(this->mRoot, key);
		//splay this node to be the root of the tree
		splay(temp_node);
		//create an iterator to this node and then return the iterator
		typename SplayTree<Key, Value>::iterator it(temp_node);
		return it;
	}
}
//finding the max value in the tree
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	//if the root is null return null iterator
	if(this->mRoot == NULL)
	{
		return NULL;
	}
	else
	{
		//get a temporary node that is the root
		Node<Key, Value>* temp_node = this->mRoot;
		//while the temp nodes right is not null continue to travers
		//down the right child until we get to the max value
		while(temp_node->getRight() != NULL)
		{
			if(temp_node->getRight() != NULL)
			{
				temp_node = temp_node->getRight();
			}
		}
		//splay the max node to the root of the tree
		splay(temp_node);
		//get an iterator of the max node and return it
		typename SplayTree<Key, Value>::iterator it(temp_node);
		return it;
	}
}
//find the minum node in the tree
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	//if the root of the tree is null return null
	if(this->mRoot == NULL)
	{
		return NULL;
	}
	else
	{
		//get a temp node that is currently the root of the tree
		Node<Key, Value>* temp_node = this->mRoot;
		//continue to traverse the left child until we get to a node
		//that does not have any left children, this node will be our 
		//min node 
		while(temp_node->getLeft() != NULL)
		{
			if(temp_node->getLeft() != NULL)
			{
				temp_node = temp_node->getLeft();
			}		
		}
		//splay the min node to the root of the tree
		splay(temp_node);
		//return an iterator to the min node and return it
		typename SplayTree<Key, Value>::iterator it(temp_node);
		return it;
	}
}