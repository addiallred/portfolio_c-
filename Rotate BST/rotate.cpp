#include "rotateBST.h"
 #include "bst.h"
 #include <iostream>
 using namespace std;
 
 template<typename Key, typename Value>
 class InheritedRotate : public rotateBST<Key, Value>
 {
 public:
 	Node<Key, Value>* getRoot() { return this->mRoot; }
 };
 
 int main(int argc, char* argv[])
{
 	InheritedRotate<int, int> bst;
 	bst.insert(make_pair(10,0));
	bst.insert(make_pair(9,0));
	bst.insert(make_pair(8, 0));
 	bst.rightRotate(bst.internalFind(10));
 	bst.rightRotate(bst.internalFind(9));
 	bst.remove(8);
 	bst.rightRotate(bst.internalFind(11));
 	cout << bst.getRoot()->getKey() << endl;
 	bst.print();
}