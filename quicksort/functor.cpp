#include "functor.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include "ctype.h"
using namespace std;
//defining the function
bool NumStrComp::operator()(const string& lhs, const string& rhs)
{
	//setting the sum of the values to 0 originally
	int lhs_sum = 0;
	int rhs_sum = 0;
	//temporary string for the string we are working on
	string cur_string;
	//for loop to work on the first stringand then the second string
	for(int i = 0; i < 2; i++)
	{
		//if i is 0 or cur string is the left hand side
		if(i == 0)
		{
			cur_string = lhs;
		}
		//otherwish it is the righthand side
		else
		{
			cur_string = rhs;
		}
		//temporarry sum is 0
		int temp_sum = 0;
		//for all of hte characters in the string
		for(int j = 0; j < int(cur_string.length()); j++)
		{
			//get the current character of the value that we are on
			char cur_char = cur_string[j];
			//if the character is lower change it to upper
			if(islower(cur_char))
			{
				cur_char = char(toupper(cur_char));
			}
			//if the charagter is digit
			if(isdigit(cur_char))
			{
				//add the digit value ot the temporary sum
				temp_sum += int(cur_char) - 48;
			}
			//if the character is a letter
			else if(isupper(cur_char))
			{
				//add the character value to the temporary sum
				temp_sum += int(cur_char) - 55;
			}
		}
		//if i is 0 than we set left sum to temp sum
		if(i == 0)
		{
			lhs_sum = temp_sum;
		}
		//if i is 1, than we set right sum to temp sum
		else if(i == 1)
		{
			rhs_sum = temp_sum;
		}
	}
	//if the sums are equal
	if(lhs_sum == rhs_sum)
	{
		//convert the sum so that they are all upper case for comparision
		string up_lhs = "";
		string up_rhs = "";
		for(int i = 0; i < int(lhs.length()); i++)
		{
			char temp = char(toupper(lhs[i]));
			up_lhs += temp;
		}
		for(int i = 0; i < int(rhs.length()); i++)
		{
			char temp = char(toupper(rhs[i]));
			up_rhs += temp;
		}
		//return comparition of left ot right
		return up_lhs < up_rhs;
	}
	//if they are not equal
	else
	{
		//return the left sum compared to right sum
		return lhs_sum < rhs_sum;
	}
}