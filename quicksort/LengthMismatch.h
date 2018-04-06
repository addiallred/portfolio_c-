#include <iostream>
#include <stdexcept>
//creating the class length mismatch which will inherit from the 
//parent exception class
class LengthMismatch : public std::exception
{
public:
	//creating the constructor for lengthmismatch
	LengthMismatch(int x, int y);
	//what function, which will return the message when what is called
	const char* what() const noexcept;

private:
	//storing the private message for the exception function
	//lengthmismatch
	std::string msg;
};
