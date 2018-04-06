#include <string>
//creating the functor class
struct NumStrComp
{
	//compare operation of the class
	bool operator()(const std::string& lhs, const std::string& rhs);
};