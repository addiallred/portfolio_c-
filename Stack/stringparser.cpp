#include "stackstr.h"
#include "lliststr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctype.h>
#include <stdio.h>

using namespace std;

//function ot print the results
void print_results(bool proper_word, string final_word, ofstream& out_file)
{
	//if the word is not malformed
	if(proper_word)
	{
		//print it out to the file
		out_file << final_word << endl;
	}
	//if it is malformed print malformed out to the
	//output file
	else
	{
		out_file << "Malformed" << endl;
	}
}

//checking if the operations, such as () and + - are in valid
//order for the word
bool valid_string(string word_check, StackStr* stack)
{
	//boolean to return if the word is true
	bool result = true;
	//stringstream and reading in the word
	stringstream ss2;
	ss2 << word_check;
	//creating a temp char to read the character into
	char temp;
	//creating booleans, if opperation isn't found
	bool opp_not_found = true;
	//if there is a front_brack
	bool front_brack = false;
	//while there is still chars to read in
	while(ss2 >> temp)
	{
		//if we find a ( or a )
		if(temp == '(' || temp == ')')
		{
			// if our temp is ()
			if(temp == '(')
			{
				//we found a front bracked
				front_brack = true;
				//push the (into the stack)
				string emptyvalue = "";
				emptyvalue = emptyvalue + temp;
				stack->push(emptyvalue);
			}
			//if it is a ')'
			else
			{
				//if the stack is empty and the temp is ')', than we know
				//there was no ')' so they don't match return false
				if(stack->empty() && temp == ')')
				{
					result = false;
					return result;
				}

				else
				{
					//if we have that the top item on the stack is '('
					//and ')' is our temp, we know that the partenthesis
					//are in order
					string temp2 = stack->top();
					if((temp == ')') && (temp2 == "("))
					{
						stack->pop();
					}
					//if they aren't in order return false
					else
					{
						result = false;
						return result;
					}
				}
			}
		}
		//if the temp is a operator and we found a front bracket
		//we can have the operationfound opperatornot found is false
		else if((temp == '+' || temp == '-') && front_brack)
		{
			opp_not_found = false;
		}

		//if the temp isn't a lower letter or is any invalid character
		//than the result is false and return it
		else if(!(islower(temp)) && temp != '>' && temp != '<' && temp != '-'
			&& temp != '+')
		{
			result = false;
			return result;
		}
	}

	//if we didn't find an opperator and we didn't find
	//() than the string is in good format
	if(opp_not_found && !front_brack && stack->empty())
	{
		//return true
		result = true;
		return result;
	}

	//if we didn't find an operator but we found a string
	//than the format is invalid
	else if(opp_not_found && front_brack)
	{
		//return false
		result = false;
		return result;
	}
	//if the stack is empty than it is in valid format
	if(stack->empty())
	{
		//return true
		result = true;
		return result;
	}

	//if the stack is not empty than it isn't valid
	//format
	else
	{
		result = false;
		return result;
	}
}

//function to alter the string delete from the front or back
string remove_from_string(string wordsub, StackStr* stack_s)
{
	//while the top of the stack is a subtraction operator
	//continue to delete
	while((stack_s->top() == "<" || stack_s->top() == ">"))
	{
		//only alter if the word length is larger than 1
		if(wordsub.length() > 1)
		{
			//greating a value of the length of the string
			int length_string = 0;
			//if it is the remove from the end operator
			if(stack_s->top()== "<")
			{
				//geting the length of the string, max value
				//of index in the string
				length_string = int(wordsub.length());
				length_string --;
				//getting the new word based of where we want
				//to remove
				wordsub = wordsub.substr(0,(length_string));
				//pop the front word
				stack_s->pop();
			}
			//if it is remove from the start operator
			else
			{
				//get the correct word using the correct indexs
				length_string = int(wordsub.length());
				length_string--;
				wordsub = wordsub.substr(1, length_string);
				stack_s->pop();
			}
		}
		//if the word length is larger than 1, just pop
		//the operator
		else
		{
			stack_s->pop();
		}
	}
	//return the word we got from the operations
	return wordsub;	
}

//parsing the string we were given 
void pars_string(string par_word, StackStr* stack, ofstream& out_file)
{
	//checking if the string passed in is a valid string
	bool proper_string = valid_string(par_word, stack);
	if(par_word == "")
	{
		proper_string = false;
		print_results(proper_string, par_word, out_file);
		return;
	}

	//boolean to make sure the word was added
	bool added = false;
	//creating a temp word to combine all the letters together
	string temp_word = "";
	//if the string is a proper string from the format
	//we checked
	if(proper_string)
	{
		//create a stringstream 
		stringstream ss;
		//read the word into the stringstream
		ss << par_word;
		//create a temp char to read the string char by char
		char temp;
		//while we can still read from the word
		while(ss >> temp)
		{
			//if the temp is alpha
			if(isalpha(temp))
			{
				//add it to the end of hte tempword
				//and added is true
				temp_word += temp;
				added = true;
			}
			//otherwise
			else 
			{
				//if the length of the word isn't one then push it to the stack
				if(temp_word.length() != 0)
				{
					temp_word = remove_from_string(temp_word, stack);
					stack->push(temp_word);
					//reset the tempword to be empty and added to be false
					temp_word = "";
					added = false;
				}
				
			}
			//if the temp is anything but a ) and a letter
			if(temp != ')' && (!isalpha(temp)))
			{
				//turn the char into a string and push 
				//it into the stack
				string empty = "";
				empty += temp;
				stack->push(empty);
			}

			//if the temp is a ')' and isn't a alphabet letter
			else if(temp == ')' && (!isalpha(temp)))
			{
				//create the string operator to be an arbitrary
				//operator so that we know if it is ever changed
				//we can only use the operator it is changed to
				string operation = "?";
				//create values to pop the function into 
				string pop1 = "";
				string pop2 = "";
				string pop3 = "";
				int count_int = 0;
				bool op_found = false;
				//only do while the top and pop values aren't ()
				while(stack->top() != "(" && pop1 != "(" && pop2 != "(" && pop3 != "(")
				{
					//get the values from the top of the stack and pop them
					pop1 = stack->top();
					stack->pop();
					pop2 = stack->top();
					stack->pop(); 
					//if the pop2 is a (
					if(pop2 == "(" && op_found)
					{
						//if the stack isn't empty pop1 and makesure
						//the ordering of the string is correct and then push it
						//to the stack
						if(!(stack->empty()))
						{
							pop1 = remove_from_string(pop1, stack);
						}
						stack->push(pop1);
					}
					else if(pop2 == "(" && !op_found)
					{
						proper_string = false;
					}
					//if pop2 isn't (
					else if(pop2 != "(")
					{
						//pop a third value
						pop3 = stack->top();
						stack->pop();
						//if pop1 is an operation, we know this is incorrect
						//format so it is malformed so proper_string is false
						if(pop1 == "-" || pop1 == "+")
						{
							proper_string = false;
							break;
						}
						else if(pop3 == "-" || pop3 == "+")
						{
							proper_string = false;
							break;
						}
						//if pop2 isn't an operation, we know this is also incorrect
						//so it is malformed
						else if(pop2 != "-" && pop2 != "+")
						{
							proper_string = false;
							break;
						}
						//if we have operation set to ?, we know we haven't
						//came accross an operation so set the operation to be
						//the operation we poped so we don't do two different operations
						//together that we aren't supposed to do
						if(operation == "?")
						{
							operation = pop2;
						}
						//if pop2 does not equal the operator that we can use
						//than the string is in malformed
						else if(pop2 != operation)
						{
							proper_string = false;
							break;
						}
						//if the pop2 is add
						if(operation == "+")
						{
							op_found = true;
							count_int++;
							//if the third pop is not a closing break
							//it is a word so add the pop1 and pop3 
							//together
							if(pop3 != "(")
							{
								//push temp new word to stack
								string temp_pop = pop3 + pop1;
								stack->push(temp_pop);
							}
							//if it is a opening braket, than the
							//string is malformed
							else if(pop3 == "(")
							{
								proper_string = false;
								break;
							}
						}
						//if we want to use subtraction
						else if(operation == "-" && count_int <1)
						{
							//we found an operation so increase the count
							op_found = true;
							count_int++;
							//if the third pop is not a opening braket
							if(pop3 != "(")
							{
								//get the lengthof the words
								int len_pop1 = int(pop1.length());
								len_pop1--;
								int len_pop3 = int(pop3.length());
								len_pop3--;
								//making sure that the word in pop1
								//is in pop3
								if(pop3.find(pop1) != string::npos)
								{
									//getting the index where the word of 
									//pop1 starts in pop3
									int n = 0;
									n = int(pop3.find(pop1));
									string new_push = "";
									//if pop1 starts at the beginining of pop3
									if(n == 0)
									{
										//put the correct parmmeters into
										//the substring function on the word pop3
										new_push = pop3.substr(len_pop1 + 1, len_pop3);
									}
									//if n starts at the end of pop3 and goes all the
									//way until the end of pop3
									else if((n + len_pop1) == len_pop3)
									{
										//get the pop3 without the last part of pop1
										new_push = pop3.substr(0, n);
									}
									//here the word would start in the middle and end int
									//the middle
									else
									{
										//create two temp words to push together 
										string temp2 = "";
										temp2 = pop3.substr(0,n);
										new_push = pop3.substr(len_pop1 + 2, len_pop3);
										//concatenate the two words together after getting 
										//the subsrings and the temp2
										new_push = temp2 + new_push;
									}
									//take the new word we found and push it in to the stack
									if(new_push != "")
									{
										stack->push(new_push);
									}
									//if the string is empty, then it is malformed
									else
									{
										proper_string = false;
									}
									
								}
								//if pop1 is not found in pop3
								else
								{
									//just push pop3 into the stack unmodified
									stack->push(pop3);
								}
							}
							//if pop3 is a opening braket, than we have a improper string
							else if(pop3 == "(")
							{
								proper_string = false;
								break;
							}	
						}
						//if the operation is an invalide operation than it is malformed
						else if(operation != "+" && operation != "-")
						{
							proper_string = false;
							break;
						}
						else if(count_int >= 1)
						{
							proper_string = false;
							break;
						}
					}
				}
			}

		}
		//if the string was never added to the stack add it
		if(added)
		{
			//if the stack is empty, just push the word
			//and it is in good format
			if(stack->empty())
			{
				stack->push(temp_word);
				proper_string = true;
			}
			//if the stack isn't empty
			else
			{
				//pass the temp word into remove from funciton to make sure
				//nothing needs to be removed from the front or back
				temp_word = remove_from_string(temp_word, stack);
				//push the temp word onto the stack
				stack->push(temp_word);
			}
		}

	}
	//get a string for the final word
	string final_word = " ";
	//if proper_string is true
	if(proper_string)
	{
		//the final word is on the top of the stack 
		final_word = stack->top();
		//pop so the stack is now empty
		stack->pop();
	}
	//if the stack isn't empty then it is malformed
	if(!(stack->empty()))
	{
		proper_string = false;
	}
	
	//call print results by passing in if it is a proper string
	//the final word we got, and the output file that was originally passed in. 
	print_results(proper_string, final_word, out_file);
	return;	
}

//reading fromteh file
string read_file(ifstream& infile)
{
	//getting the first line from the file
	string retrived;
	getline(infile, retrived);
	//returning the string
	return retrived;
}

int main(int argc, char* argv[])
{
	//if not enough parameters are passed in exit the program
	if(argc < 3)
	{
		cout << "Please provide an input and an output file" << endl;
		return -1;
	}
	//getting the input and output file from the argv passed in
	ifstream input_file(argv[1]);
	ofstream output_file(argv[2]);
	//while we can continue to read in from the file
	while(!(input_file.fail()))
	{
		//create a new stack
		StackStr* stack_ = new StackStr();
		//get the word we want to analysie by 
		//reading it in from the input file with the funciton
		//read
		string word_pars;
		word_pars = read_file(input_file);
		if(!(input_file.fail()))
		{
			pars_string(word_pars, stack_, output_file);
		}
		
		//while the stack is not empty, pop all items
		while(!(stack_->empty()))
		{
			stack_->pop();
		}
		//once everything is removed from the stack, delete the stack
		delete stack_;
	}	
}