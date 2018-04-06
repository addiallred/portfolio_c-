#include "LengthMismatch.h"
#include <iostream>
#include <string>

using namespace std;
//defining the lengthmismatch constructo, and while constructing it, setting the 
//message to be outputed for length mismatch
LengthMismatch::LengthMismatch(int x, int y) : 
msg("Input data structures have lengths " + to_string(x) + " and " + to_string(y))
{
}
//what function
const char* LengthMismatch::what() const noexcept
{
	//return the message for the specific lengthmismatch exceptino that was called
	return msg.c_str();
}