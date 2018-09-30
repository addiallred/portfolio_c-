#include <iostream>
#include <string>
#include <stdexcept>
#include "splayTree.h"

//creating the cache class
template<typename Key, typename Value>
class cacheLRU
{
	//public members
public:
	//constructor of the cache
	cacheLRU(int capacity);
	//destructor for the cache
	~cacheLRU();
	//put function, insert a key value pair into the cache
	void put(const std::pair<const Key, Value>& keyValuePair);
	//get the pair key value set based off of a given key
	std::pair<const Key, Value> get(const Key& key);
	
private:
	//current cache capacity
	int curr_capacity;
	//the maximum capacity of the cache
	int max_capacity;
	//a splay tree that will be mainly used to implement the cache
	SplayTree<Key, Value> cache_splay;
};
//cache constructor
template<typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int passed_in_capacity)
{
	//setting the maximum capacity of the cache
	max_capacity = passed_in_capacity;
	curr_capacity = 0;
}
//creating the cache destructor
template<typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU()
{

}
//put function, place the key value pair into the cache 
template<typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair)
{
	//if the node is already in the tree just splay it to the root
	if(cache_splay.find(keyValuePair.first) != NULL)
	{
		if(cache_splay.find(keyValuePair.first)->first == keyValuePair.first)
		{
			cache_splay.insert(keyValuePair);
			return;
		}
	}
	//if the current capacity of the cache is less than the maximum capacity that 
	//the cache can have
	if(max_capacity > curr_capacity)
	{
		//if the key we are trying to insert into the cache isn't already in the cache
		//increase the current capacity
		if(cache_splay.find(keyValuePair.first) == NULL)
		{
			curr_capacity++;
		}
		//if the key of the node returned is not the key of the value we want to 
		//insert increast the capacity
		else if(cache_splay.find(keyValuePair.first)->first != keyValuePair.first)
		{
			curr_capacity++;
		}
		//insert the key value pair into the cache
		cache_splay.insert(keyValuePair);
	}
	//if the max capcity is already reached
	else
	{
		//delete the min leaf of the tree
		cache_splay.deleteMinLeaf();
		//decrease the capacity of the cache
		curr_capacity--;
		//if the key we are trying to insert into the cache isn't already in the cache
		//increase the current capacity
		if(cache_splay.find(keyValuePair.first) == NULL)
		{
			curr_capacity++;
		}
		//if the key of the node returned is not the key of the value we want to 
		//insert increast the capacity
		else if(cache_splay.find(keyValuePair.first)->first != keyValuePair.first)
		{
			curr_capacity++;
		}
		//insert the key value pair into the cache
		cache_splay.insert(keyValuePair);
	}
}
//returning the key value pair of a key
template<typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key)
{
	//if we try to find the key in the splay tree and it is null
	if(cache_splay.find(key) == NULL)
	{
		//throw an error
		throw typename std::logic_error("Error");
	}
	//if the key retruned when calling find 
	//does not equal the key we want throw an error
	else if(cache_splay.find(key)->first != key)
	{
		throw typename std::logic_error("Error");
	
	}
	//if we were able to find the key
	else
	{
		//get the iterator of the key and return the key value pair by 
		//dereferencing te iterator
		typename SplayTree<Key, Value>::iterator it = cache_splay.find(key);
		return *it;
	}
}