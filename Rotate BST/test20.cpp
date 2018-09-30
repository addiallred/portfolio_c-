#include "rotate.h"
using namespace std;
template<typename Key, typename Value>
void InsertRandom(StressBST& bst, size_t size, std::mt19937& g, InsSeq<StressKey, StressValue>& seq)
{
	for (size_t i = 0; i < size; ++i)
	{
		seq.push_back(std::make_pair(static_cast<StressKey>(g()), 0));
		bst.insert(seq.back());
	}
}

template<typename Key, typename Value>
void InsertInTree(BinarySearchTree<Key, Value>& bst, const InsSeq<Key, Value>& ins)
{
	for (const auto& kv : ins)
	{
		bst.insert(kv);
	}
}
template<typename Key, typename Value>
void CompareTreeStructure(Node<Key, Value>* r1, Node<Key, Value>* r2)
{
	if (r1 != nullptr && r2 != nullptr)
	{
		EXPECT_EQ(r1->getKey(), r2->getKey());
		EXPECT_EQ(r1->getHeight(), r2->getHeight());
		CompareTreeStructure(r1->getLeft(), r2->getLeft());
		CompareTreeStructure(r1->getRight(), r2->getRight());
	}
	else
	{
		EXPECT_EQ(r1, r2);
	}
}
int main(int argc, char* argv[])
{
	cout << "here now" << endl;
	StressBST t1, t2, copy;
	std::mt19937 g(1942);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 10, g, ins);
	InsertInTree(copy, ins);
	std::shuffle(ins.begin(), ins.end(), g);
	InsertInTree(t2, ins);
	cout << "inside of here" << endl;
	t1.transform(t2);
	CompareTreeStructure(copy.getRoot(), t1.getRoot());
	CompareTreeStructure(copy.getRoot(), t2.getRoot());
}