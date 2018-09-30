#include <iostream>
#include <vector>
#include "bst.h"
//rotate class that will inherit from binary search tree
template<typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
	//public members
public:
	//checking if two trees have the same keys
	bool sameKeys(const rotateBST& t2) const;
	//treansforming one tree into this tree
	void transform(rotateBST& t2)const;
	//rotation to left on node
	void leftRotate(Node<Key, Value>* r);
	//rotation to right on node
	void rightRotate(Node<Key, Value>* r);
	
protected:
	
private:
	//if the trees are equal
	bool equal_tree(Node<Key, Value>* node1, Node<Key, Value>* node2) const;
	//getting the inorder vector for the tree to check if the trees are equal
	void inorder(Node<Key, Value>* curr_node, std::vector<Key>& list) const;
	//same tree, checks ifthe tree are the same
	bool same_tree(rotateBST& t2) const;
	//rotation helper make sure all of the nodes align with one another
	void rotate_transform_helper(rotateBST& t2, Node<Key, Value>* expected, Node<Key, Value>* actual) const;
	//get it into a linked list
	void transform_helper(rotateBST& t2, Node<Key, Value>*curr_node) const;
	//requirsive function to see if the trees have the same keys
	bool equal_helper(Node<Key, Value>* node1, Node<Key, Value>* node2) const;
	//adjust height function
	void adjust_height(Node<Key, Value>* curr_node);
};
//adjust the height of the tree
template<typename Key, typename Value>
void rotateBST<Key,Value>::adjust_height(Node<Key, Value>* curr_node)
{
	//if the current node is the root
	if(curr_node == this->mRoot)
	{
		//get right and left child tmep ints
		int temp_height = 0;
		int right_child_h = 0;
		int left_child_h = 0;
		//if the right isn't null add the height of the right child
		//to the int
		if(curr_node->getRight() != NULL)
		{
			right_child_h += curr_node->getRight()->getHeight();
		}
		//if the left child isn't null add the height of the right
		//child to the int
		if(curr_node->getLeft() != NULL)
		{
			left_child_h += curr_node->getLeft()->getHeight();
		}
		//take the max of the left and right height
		temp_height = std::max(right_child_h, left_child_h);
		//add one to the temp height and set this as current nodes height
		curr_node->setHeight(temp_height+1);
		return;
	}
	else
	{
		//get the parent of the current node
		Node<Key, Value>* temp = curr_node->getParent();
		//temp values for the left and right child
		int right_child_h = 0;
		int left_child_h = 0;
		//if the right child isn't null add the height of the right child
		if(curr_node->getRight() != NULL)
		{
			right_child_h += curr_node->getRight()->getHeight();
		}
		//if the left hcild isn't null add the heigh of the left child
		if(curr_node->getLeft() != NULL)
		{
			left_child_h += curr_node->getLeft()->getHeight();
		}
		//get the max heigh of the two
		int temp_height = std::max(right_child_h, left_child_h);
		//set current height to be the max of left and right plus 1
		curr_node->setHeight(temp_height +1);
		//recurse on the parent
		adjust_height(temp);
	}
}
//check if the trees are equal to one another
template<typename Key, typename Value>
bool rotateBST<Key, Value>::equal_helper(Node<Key, Value>* node1, Node<Key, Value>* node2) const
{
	//if both nodes are null return true
	if(node1 == NULL && node2 == NULL)
	{
		return true;
	}
	//if the keys are node the same return false
	if(node1->getKey() != node2->getKey())
	{
		return false;
	}
	//if the right node equals node of one tree but the other isn't null
	//return false
	if(node1->getRight() != NULL && node2->getRight() == NULL)
	{
		return false;
	}
	//if the right of a node is null but the other isn't return false
	if(node1->getRight() == NULL && node2->getRight() != NULL)
	{
		return false;
	}
	//if they are both not null
	if(node1->getRight() != NULL && node2->getRight() != NULL)
	{
		//if their keyes do not match return false
		if(node1->getRight()->getKey() != node2->getRight()->getKey())
		{
			return false;
		}
	}
	//if the left is null for one of the nodes
	//but not the other return false
	if(node1->getLeft() != NULL && node2->getLeft() == NULL)
	{
		return false;
	}
	if(node1->getLeft() == NULL && node2->getLeft() != NULL)
	{
		return false;
	}
	//if both nodes are null
	if(node1->getLeft() != NULL && node2->getLeft() != NULL)
	{
		//if the keys are not equal to one another return false
		if(node1->getLeft()->getKey() != node2->getLeft()->getKey())
		{
			return false;
		}
		
	}
	//if all of left and right are null return true
	if(node1->getLeft() == NULL && node2->getLeft() == NULL && node1->getRight() == NULL
		&& node2->getRight() == NULL)
	{
		return true;
	}
	else
	{
		//recurse on equal helper with the right node for both trees of the 
		//current node
		bool right = equal_helper(node1->getRight(), node2->getRight());
		//recurse on equal helper with the left node for both trees of the 
		//current node
		bool left = equal_helper(node1->getLeft(), node2->getLeft());
		//if left or rightis false return false
		if(!right || !left)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

}
//same tree function
template<typename Key, typename Value>
bool rotateBST<Key, Value>::same_tree(rotateBST& t2) const
{
	//get the roots of the two tree
	Node<Key, Value>* root2 = t2.mRoot;
	Node<Key, Value>* root1 = this->mRoot;
	//if the roots are the same call the equal helper and 
	//return the results
	if(root1->getKey() == root2->getKey())
	{
		bool results = equal_helper(root1, root2);
		return results;
	}
	else
	{
		//return false otherwise
		return false;
	}
	
}
//left rotation
template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* rotate_node)
{
	//if the node is null return
	if(rotate_node == NULL)
	{
		return;
	}
	//if the nodes right child is null return
	else if(rotate_node->getRight() == NULL)
	{
		return;
	}
	else
	{
		//get the right chil
		Node<Key, Value>* right_child = rotate_node->getRight();
		//if the rotate nodes parent isn't null
		if(rotate_node->getParent() != NULL)
		{
			//get the parent
			Node<Key, Value>* parent = rotate_node->getParent();
			//if the parents value is largerthan the rotate nodes key
			if(parent->getKey() > rotate_node->getKey())
			{
				//parents left is the right child
				parent->setLeft(right_child);
			}
			else
			{
				//parents right is the right child
				parent->setRight(right_child);
			}
			//set right childs parent to ge the parent
			right_child->setParent(parent);
			//if the right childs left isn't null
			if(right_child->getLeft() != NULL)
			{
				//get the left child and set the rotate nodes
				//right to be the left child and left child parent to 
				//be rorate node
				Node<Key,Value>* left_child = right_child->getLeft();
				rotate_node->setRight(left_child);
				left_child->setParent(rotate_node);
			}
			else
			{
				//rotate nodes right is null
				rotate_node->setRight(NULL);
			}
			//right childs left is the rotate node
			right_child->setLeft(rotate_node);
		}
		else
		{
			//right child parent is null
			right_child->setParent(NULL);
			//if the right child left isn't null
			if(right_child->getLeft() != NULL)
			{
				//get the left child of the right child
				//set the rotate nodes right to be the left child'
				//and the left childs parent to be the rorate node
				Node<Key, Value>* left_child = right_child->getLeft();
				rotate_node->setRight(left_child);
				left_child->setParent(rotate_node);
			}
			else
			{
				//set the right ofrotate to be null
				rotate_node->setRight(NULL);
			}
			//set the left to be the rotate node 
			right_child->setLeft(rotate_node);
			//the root is not right child since rotatenode
			//had no parent
			this->mRoot = right_child;
		}
		//rotate nodes parent is its right child now
		//adjsut the height of fromthe roate node
		rotate_node->setParent(right_child);
		this->adjust_height(rotate_node);
	}
}
//right rotation
template<typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key, Value>* rotate_node)
{
	//if the rotation node is null return
	if(rotate_node == NULL)
	{
		return;
	}
	//if its left is null return 
	else if(rotate_node->getLeft() == NULL)
	{
		return;
	}
	else
	{
		//get the left child
		Node<Key, Value>* left_child = rotate_node->getLeft();
		//if the rorate nodes parent isn't null
		if(rotate_node->getParent() != NULL)
		{
			//get the parent of the rotate node
			Node<Key, Value>* parent = rotate_node->getParent();
			//if the parents key is greater than the rotate node
			if(parent->getKey() > rotate_node->getKey())
			{
				//set the parents left to be the left child
				parent->setLeft(left_child);
			}
			else
			{
				//parents right is the left child
				parent->setRight(left_child);
			}
			//the parent of the left child is not the parent of the rotate node
			left_child->setParent(parent);
			//if the left childs right isn't null
			if(left_child->getRight() != NULL)
			{
				//get the right child and set the rotate node 
				//left to be the right child and the right childs
				//parent to be the rotate node
				Node<Key,Value>* right_child = left_child->getRight();
				rotate_node->setLeft(right_child);
				right_child->setParent(rotate_node);
			}
			else
			{
				//rotate node left is null
				rotate_node->setLeft(NULL);
			}
			//left child right child is the rotate node
			left_child->setRight(rotate_node);
		}
		else
		{
			//left childs parent is null
			left_child->setParent(NULL);
			//if the left child has right children
			if(left_child->getRight() != NULL)
			{
				//get the right child and set the rotate node 
				//left to be the right child and the right childs
				//parent to be the rotate node
				Node<Key, Value>* right_child = left_child->getRight();
				rotate_node->setLeft(right_child);
				right_child->setParent(rotate_node);
			}
			else
			{
				//other wise rotate node left is null
				rotate_node->setLeft(NULL);
			}
			//set the right child of left to be the rotate node
			left_child->setRight(rotate_node);
			//set the root to be the left child
			this->mRoot = left_child;
		}
		//rotates node parent is the left child
		rotate_node->setParent(left_child);
		//adjust the height from the rotate node
		this->adjust_height(rotate_node);
	}
}
//inorder traversal
template<typename Key, typename Value>
void rotateBST<Key,Value>::inorder(Node<Key, Value>* curr_node, std::vector<Key>& listing) const
{
	//if the curr is null return
	if(curr_node == NULL)
	{
		return;
	}
	//recurse on the left
	inorder(curr_node->getLeft(), listing);
	//push key to vector
	listing.push_back(curr_node->getKey());
	//recurse to the right
	inorder(curr_node->getRight(), listing);
}
//check if the tress have the same keys 
template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
	//get the root of the other tree
	Node<Key, Value>* BST_2root = t2.mRoot;
	//get vectors for both trees
	std::vector<Key> results2;
	std::vector<Key> results_this;
	//call in order on both of the trees
	inorder(BST_2root, results2);
	Node<Key, Value>* this_root = this->mRoot;
	inorder(this_root, results_this);
	//if the vector size are different return false
	if(results2.size() != results_this.size())
	{
		return false;
	}
	else
	{
		//recurse over the vectors and see if every index
		//has the same key, if so return true if not false;
		for(int i = 0; i < int(results2.size()); i++)
		{
			if(results2[i] != results_this[i])
			{
				return false;
			}
		}
	}
	return true;
}
//transform helper, this will assist with transform with making sure no nodes
//have left children
template<typename Key, typename Value>
void rotateBST<Key, Value>::transform_helper(rotateBST& t2, Node<Key, Value>*curr_node) const
{
	//if the current node is null return
	if(curr_node == NULL)
	{
		return;
	}
	else
	{
		//if the nodes left isn't null
		if(curr_node->getLeft() != NULL)
		{
			//recurse on the left of the tree
			transform_helper(t2, curr_node->getLeft());
		}
		//if the right isn't null
		if(curr_node->getRight() != NULL)
		{
			//recurse on the right
			transform_helper(t2, curr_node->getRight());
		}
		//while the current node left isn't null
		while(curr_node->getLeft() != NULL)
		{
			//perform a right rotation
			t2.rightRotate(curr_node);
		}
	}
}
//
template<typename Key, typename Value>
void rotateBST<Key, Value>::rotate_transform_helper(rotateBST& t2, Node<Key, Value>* expected, Node<Key, Value>* actual) const
{
	//if they are the same tree return
	if(same_tree(t2))
	{
		return;
	}
	//if the nodes are null return
	else if(expected == NULL || actual == NULL)
	{
		return;
	} 
	//if the keys are the same
	else if(expected->getKey() == actual->getKey())
	{
		//if expected left isn't null
		if(expected->getLeft() != NULL)
		{
			//while the keys do not match for expected and actual
			while(expected->getLeft()->getKey() != actual->getLeft()->getKey())
			{
				//perform a right rotation on actuals left child
				t2.rightRotate(actual->getLeft());
			}
			//recurse on tranform helper on the right and left of expected and actual
			rotate_transform_helper(t2, expected->getLeft(), actual->getLeft());
			rotate_transform_helper(t2, expected->getRight(), actual->getRight());
		}
		//if expected right isn't null
		if(expected->getRight() != NULL)
		{
			//while expected right and leftare not the same key do a left rotation on 
			//the right child of actual
			while(expected->getRight()->getKey() != actual->getRight()->getKey())
			{
				t2.leftRotate(actual->getRight());
			}
			//recurse on transform helper on the left and right of expected and actual
			rotate_transform_helper(t2, expected->getLeft(), actual->getLeft());
			rotate_transform_helper(t2, expected->getRight(), actual->getRight());
		}
	}
}
//transform function
template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
	//get a boolean for if the trees have the same keys
	bool same_node = sameKeys(t2);
	//if they don't have the same keys return
	if(!same_node)
	{
		return;
	}
	else
	{
		//if the root is null return 
		if(this->mRoot == NULL)
		{
			return;
		}
		//get the root of the tree passed in
		Node<Key, Value>* root_bst2 = t2.mRoot;
		//while the left node of the root isn't right
		while(t2.mRoot->getLeft() != NULL)
		{
			if(t2.mRoot->getLeft() != NULL)
			{
				//get the root and perform a right
				//rotation on the root
				root_bst2 = t2.mRoot;
				t2.rightRotate(root_bst2);
			}
		}
		//if the right of the root does not equal null
		if(t2.mRoot->getRight() != NULL)
		{
			//get the right child
			Node<Key, Value>* right_child = t2.mRoot->getRight();
			//perform rotations on this child until it is in a linked list through
			//transform helper
			transform_helper(t2,right_child);
		}
		//get the root of the tree
		Node<Key, Value>* requried_root = this->mRoot;
		//while the root of the tree and t2 tree are different
		//do left roations on t2
		while(t2.mRoot->getKey() != requried_root->getKey())
		{
			t2.leftRotate(t2.mRoot);
		}
		//if the are not the same tree
		if(!(same_tree(t2)))
		{
			//call rotate_transform halper function
			rotate_transform_helper(t2, this->mRoot, t2.mRoot);
		}
	}
}