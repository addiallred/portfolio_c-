 
/*maze.cpp

Author: Addison Allred

Short description of this file:
This file is the main implementation of all the other
files that we will use to complete this project. 
We utilize the functions, structs, queues, and arrays that
were established in the other files, and then run them through
the bellow algorithm sequence to discover the path out of the maze
and the most efficent path out of the maze
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;
   
   //getting the maze from the function read maze, passing in
   //the addresses of rows and cols since read_maze requires pointers
   mymaze = read_maze(&rows, &cols);
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   //getting the results from maze search after the maze_search
   //function has been run
   result = maze_search(mymaze, rows, cols);
 
   

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      //printing out the maze if their is a path that has been found
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   //deallocating the memory that I got to story the 
   //maze array in from mazeio
   for(int i = 0; i < rows; i++)
  {
   
   delete[] mymaze[i];

  }

  delete[] mymaze;




   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
   //creating a start and finish struct from the use of loction
   Location start;
   Location finish;

   //defining a que that is the maximum size which is rows times cols
   Queue loc_maze(rows * cols);
   
  

   //dynamically allocating the predecessor
   Location** predecessor = new Location*[rows];
   for(int i = 0; i < rows; i++)
   {
      predecessor[i] = new Location[cols];
   }

   //setting the values of the predecessor to -1 and -1, so
   //that we know when we have already visited it or not. 
   for(int i = 0; i < rows; i++)
   {
      for(int j = 0; j < cols; j++)
      {
         predecessor[i][j].row = -1;
         predecessor[i][j].col = -1;
      }
   }
   //setting values for start and finish to check if there
   //is more than one start or not even a start
   int num_Start = 0;
   int num_Finish = 0;
   //this is going through the maze and finding the start and finish postion
   for(int i = 0; i < rows; i++)
   {
      for(int j = 0; j < cols; j++)
      {
         if(maze[i][j] == 'S')
         {
            //increasing the value of starts because we found a start value
            num_Start++;

            //if we find the starting position and there are not 
            //multiple starts go through and create the 
            //instances for row and column of the location struct
            //and add it to the maze, then incriment the number
            //of starts found so we make sure that we never have
            //more than one

            if(num_Start < 2)
            {
               start.row = i;
               start.col = j;
               loc_maze.add_to_back(start);
               
            }

           //if we find another start return -1 because maze isn't a good format
            // deallocate the memory given to the predecessor since we no longer
            // need it
            else if(num_Start > 1)
            {
               for(int k = 0; k < rows; k++)
               {
   
                  delete[] predecessor[k];

               }

               delete[] predecessor;

               
               return -1;
            }

         }

         //if the current index that we are looping through is equal to f
         if(maze[i][j] == 'F')
         {
            //increase the number of finishes that we have found
            num_Finish++;

            //set the row and column for the struct finish equal to the current 
            //value that we are iterating through by the for loop and increase
            //finish numbers so that we make sure that we only have one f in
            // our 
            //maze
            if(num_Finish < 2)
            {
               finish.row = i;
               finish.col = j;  
               
            }
            //if we found more than one f return -1 so that it will know it is
            // bad imput
            //deallocate the memory stored by predecessor since we no longer need it
            else if(num_Finish > 1)
            {
                  for(int k = 0; k < rows; k++)
                  {
   
                     delete[] predecessor[k];

                  }

                  delete[] predecessor;

               return -1;
            }
            
         }
      }
   }

   //if there were no starts found at all return -1 so we know it is a bad maze
   // and can't be
   //solved
   //deallocated the memory stored by predecessor since we no longer need it
   if(num_Start == 0)
   {
      for(int k = 0; k < rows; k++)
      {
   
         delete[] predecessor[k];

      }

       delete[] predecessor;

      return -1;
   }

   //if there were no finishes found at all, return -1 so we know we can't
   // solve the maze
   //because there is no finish point
   //deallocated the memory stored by predecessor since we no longer need it
   if(num_Finish == 0)
   {
      for(int k = 0; k < rows; k++)
      {
   
         delete[] predecessor[k];

      }

      delete[] predecessor;
      return -1;
   }

   //setting  bool to see if we are able to success fully find a path way
   // to f, where
   //the wals aren't blocked off
   bool found = false;
   //while the queue defined as loc_maze has locations in it,
   //continue to search for the finish
   while (!(loc_maze.is_empty()))
   {
      //creating a struct for the current location that we are on
      Location curr;

      //defining the current location as the location at the front of the
      // loc_maze queue
      curr = loc_maze.remove_from_front();

      //if the position that we are currently on in the maze is f than exit
      // the while loop
      //so that we can start back tracking. 
      if(maze[curr.row][curr.col] == 'F')
      {
         found = true;
         break;
      }

      //creating a astruct location for the value north of the current location
      Location north;
      //the row is going to the just one above so we subtract 1 from the current
      // row
      //and the col will be the same
      north.row = curr.row-1;
      north.col = curr.col;
      //making sure that the number row is inbounds of the grid
      if(north.row != -1)
      {
         //seeing if the value at that col and row in the maze is not a wall
         if(maze[north.row][north.col] != '#')
         {
            //making sure that the value at the north col and row is an address
            // of -1 so 
            //we know it hasn't been visited yet
            if(predecessor[north.row][north.col].row == -1 )
            {
               //add in the location strucr of north to the que
               loc_maze.add_to_back(north);
               //place the current row and col into the predecessor position of the
               //location north of the current position so that we know the position
               // we 
               //came from to get to the current position that we are at
               predecessor[north.row][north.col].row = curr.row;
               predecessor[north.row][north.col].col = curr.col;
               
            }
         }
      }

      //creating a struct location for the value west of the current location
      Location west;
      //the row is going to be the same and the col is going to be to the left of
      //the current so we subtract 1 from col
     
      west.row = curr.row;
      west.col = curr.col - 1;
      //making sure thta the number number is in bounds and is a valid selection
      //to take a position with in the maze
      if(west.col != -1)
      {
         //making sure that the current location that we are at isn't a wall
         if(maze[west.row][west.col] != '#')
         {
            //making sure that the current location has -1 as the row predecessor
            //which means that the current location hasn't not been visited yet
            if(predecessor[west.row][west.col].row == -1)
            {
               //adding the current poisition to the queue at the end of it
               loc_maze.add_to_back(west);
               //setting the value of the predecessor at the location west of the
               // current
               //location is the address of the current location so that we know
               // how we
               //got to the address just west of it
               predecessor[west.row][west.col].row = curr.row;
               predecessor[west.row][west.col].col = curr.col;
               

            }
         }
      }
      //defining a struct that will be south of our current location
      Location south;
      //setting the row of the position south of the current to be plus 1 from the
      // currents
      //row as it will be the value directly below it, and setting south col as the
      // curr col
      //since it will be the same
      south.row = curr.row + 1;
      south.col = curr.col;
      //making sure that the row is inbounds
      if(south.row != rows)
      {
         //making sure that the position isn't a wall
         if(maze[south.row][south.col] != '#')
         {
            //making sure that the position hasn't already been visited
            if(predecessor[south.row][south.col].row == -1 )
            {
               //adding the south lcoatino struct to the back of the queue
               loc_maze.add_to_back(south);
               //setting the predecessor of the south item from current to be the 
               //currents row and col
               predecessor[south.row][south.col].row = curr.row;
               predecessor[south.row][south.col].col = curr.col;
               
            }
         }
      }

      //creating an east struct which will be directly to the right of current

      Location east;
      //setting the row and col of east, we know that row will be the same but col
      //will be current col + 1 because it is directly to the right of current
      east.row = curr.row;
      east.col = curr.col + 1;
      //making sure tht the col of the east isn't outside of the bound of th
      //map
      if(east.col != cols)
      {
         //making sure that the east current location isn't a wall
         if(maze[east.row][east.col] != '#')
         {
            //making sure that we haven't already visited the east location
            if(predecessor[east.row][east.col].row == -1)
            {
               //adding the east current location to the back of the queue
               loc_maze.add_to_back(east);
               //setting the predecessor value at the current east position
               //to hold the values of the current row and col so that we know where
               //we came from
               predecessor[east.row][east.col].row = curr.row;
               predecessor[east.row][east.col].col = curr.col;
               
            }
         }
      }

   }

   //creating a location struct for the current location we are at
   Location current_loc;
   //initializing the current_loc to be the row and col of the finish struct
   current_loc.row = finish.row;
   current_loc.col = finish.col;
   //creating a previous location struct
   Location previous_loc;
   // checking to see if we found f is true, if it is than we know that
   // we found the 
   //finish position from the starting position and that the maze is solveable
   if(found)
   {

      //keep tracing back which our current location isn't s, once it is s we know
      //we are back to the start
      while(maze[current_loc.row][current_loc.col] != 'S')
      {
         //setting the previous loc row and colum to be the current row and col    
         previous_loc = predecessor[current_loc.row][current_loc.col];
         
         //if the current position we are at is not f
         if(maze[current_loc.row][current_loc.col] != 'F')
         {
            //change the value of the current position to be equal to 
            // * so that it will indicate the shortest path
            maze[current_loc.row][current_loc.col] = '*'; 
         }
         //settting the current location to the previous location 
         current_loc = previous_loc;
        
         
         
      }
      //return 1 so that it will exit and execut the corret map
      //deallocate the memory allocated by predecessor since we no longer need it
      for(int k = 0; k < rows; k++)
      {
   
      delete[] predecessor[k];

      }

      delete[] predecessor;
      return 1;
   } 

   //if we didn't find f than we know that the maze isn't solvable
   //deallocate the memory allocated by predecessor since w e no longer need it
   else
   {
      for(int k = 0; k < rows; k++)
      {
   
         delete[] predecessor[k];

      }

      delete[] predecessor;
      return 0;
   } 

}