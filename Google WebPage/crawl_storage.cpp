#include "crawl_storage.h"
#include <vector>
#include <iostream>

using namespace std;

Crawl_storage::Crawl_storage()
{

}
Crawl_storage::~Crawl_storage()
{

}
Crawl_storage::insert_link(const string& word)
{
	links_to.push_back(word);
}
