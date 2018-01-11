/* 
mazeio.cpp

Author: Addison Allred

Short description of this file:
This file will be utilized primarily to read in information about
the maze, to place the information into a data scruture that 
we can use throughout our algorithm, and then finally printing
out what our result is after we run the algorithm.
*/

#include <iostream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from cin into a dynamically allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * such as integers for the size not found.
 *
 * We also pass in two pointers to integers. Fill 
 * the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(int* rows, int* cols) {

	//reading in the row and col from the file provided
	cin >> *rows;
	cin >> *cols;

	//checking if the rows and cols are valid inputs and if so returning null
	if(rows == NULL && cols == NULL)
	{
		return NULL;
	}
	//dynamically allocating an array for the maze to be read into
	//based upon the number of rows and cols that were provided from
	//being read in
	char** maze_map = new char*[*rows];

	for(int i = 0; i < *rows; i++)
	{
		maze_map[i] = new char[*cols];
	}

	//reading in the values from the maze file to the dynamically 
	//allocated array
	for(int i = 0; i < *rows; i++)
	{
		for(int j = 0; j < *cols; j++)
		{
			cin >> maze_map[i][j];
		}
	}
	//returning the maze_map which now stors an array
	//of chars that have the information in regards of 
	//the map such as wall start finish etc. 
	return maze_map;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
	//printing out the number of rows and cols
	cout << rows << " " << cols << endl;
	//iterating through the 2d array and printing out every value 
	//at the position of a specific row and column. 
   for(int i = 0; i < rows; i++)
   {
   	for(int j = 0; j < cols; j++)
   	{
   		cout << maze[i][j];
   	}
   	//printing out a line so that everything will be on a different line
   	cout << endl;
   }

}