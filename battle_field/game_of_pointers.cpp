#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

//Warrior struct that we will use throught the program to create
//various instances of the warriors
struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
//this is creatingthe function skirmish which will implement all of the 
//skirmishes that are in the file
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserve, ofstream &output)
{
	//this is creating a boolon, if we ever fine a position where their is no
	//protector than we know that the invaders have won and we will set it equal
	//to true
	bool invader_win = false; 

	//this for loop is looping through every position in a given row or column
	//depending if it is a protector or an invader
	for(int i = 0; i < rows; i++)
	{

		//this is creating instances of the current protector and invador we
		//are on based upon the i value and skirmish row value that we 
		//were given
		Warrior * prot = protectors[i][skirmish_row];
		Warrior * inva = invaders[skirmish_row][i];

		//checking if the invader position is empty, then not doing anything and just
		//outputting no assult in to the file
		if(invaders[skirmish_row][i] == NULL)
		{
			output << "No assult" << endl;
		}

		//checking if the space does not have a protector there, if the proctector
		//is not there than the invaders will win
		else if(protectors[i][skirmish_row] == NULL)
		{

			invader_win = true;
			return invader_win;
		}

		//if the protector's weapon is an axe and the invaders weapon is not
		//an axe than the protector win's
		else if(prot->weapon == "axe" && inva->weapon != "axe")
		{
			//we delete the invader at the current instance we are on
			//set the loction in the array of the invaders to null
			//and print out that we killed the invaders
			delete inva;
			invaders[skirmish_row][i] = NULL;
			output << "Invader killed" << endl;
		}

		//if the invaders weapon is an axe and the protectors weapon is not
		//an axe than the invader win's
		else if(inva->weapon == "axe" && prot->weapon != "axe")
		{
			//creating a bool for if we found a space that we can move the 
			//protector to so that we know to then break out of the for loop
			//and not keep searing for a place to put the protectors 
			bool space_found = false;
			//looping throught the invaders array and seeing if there 
			//is an empty slot that we would be able to put a protector into
			for(int j = 0; j < rows; j++)
			{
				for(int k = 0; k < columns; k++)
				{
					//if the invader slot that we are currenlty on is null,
					//then place the protector in that slot and then
					//set the protectors old location in the array to null
					//and set space found to be true then break out of the loop
					//since we filled in the space that we were looking for
					if(invaders[k][j] == NULL)
					{
						invaders[k][j] = prot;
						protectors[i][skirmish_row] = NULL;
						space_found = true;
						output << "Protector defected" << endl;
						break;
					}	
				}
				if(space_found)
				{
					break;
				}
				
			}

			//if we didn't find a space then we would delete the protector that 
			//we are itterating through and set that space location equal to null
			//in the protectors array
			if(space_found == false)
			{
				delete prot;
				protectors[i][skirmish_row] = NULL;
				output << "Protector killed" << endl;
			}

			//if we have reserves left place them in spots in the protectors side
			if(reserve > 0)
			{
				//if the current protector that we are on is null then we
				//place a new warrior in there and give them new weapons and powers
				//we subtract the amount of reserve we have.
				if(protectors[i][skirmish_row] == NULL)
				{
					protectors[i][skirmish_row] = new Warrior;
					protectors[i][skirmish_row]->power = 100;
					protectors[i][skirmish_row]->weapon = "axe";
					reserve--;
				}
			}
			
			
		}


		//if the invador and the protector have the same weapon then we 
		//compair their power values to determine who wins
		else if(inva->weapon == prot->weapon)
		{
			//if the power of the invader is less than that of the protector
			//than the protector won and we delete the invader
			//and null the location that the invader was at
			if(inva->power < prot->power)
			{
				delete inva;
				invaders[skirmish_row][i] = NULL;
				output << "Invader killed" << endl;
			}

			//if the power of the prtoector is less than that of the invader
			//than the invader one and we executre steps take for when a protector
			//losses a duel

			else if(inva->power > prot->power)
			{
				//creating a bool for if we found a space that we can move the 
				//protector to so that we know to then break out of the for loop
				//and not keep searing for a place to put the protectors 
				bool space_found = false;
				//looping throught the invaders array and seeing if there 
				//is an empty slot that we would be able to put a protector into
				for(int j = 0; j < rows; j++)
				{
					for(int k = 0; k < columns; k++)
					{
						//if the invader slot that we are currenlty on is null,
						//then place the protector in that slot and then
						//set the protectors old location in the array to null
						//and set space found to be true then break out of the loop
						//since we filled in the space that we were looking for
						if(invaders[k][j] == NULL)
						{
							invaders[k][j] = prot;
							protectors[i][skirmish_row] = NULL;
							space_found = true;
							output << "Protector defected" << endl;
							break;
						}	
					}
					//if we found the space that we are looking for than 
					//we break out of the loop because we already filled in a place
					if(space_found)
					{
						break;
					}
								
				}

				//if we didn't find a place, than we kill the protector and set 
				//the protectors location to be null and cout that we killed the protector
				if(space_found != false)
				{
					delete prot;
					protectors[i][skirmish_row] = NULL;
					output << "Protector killed" << endl;
				}

				//if we have reserve left, try to find a place for them to
				//be placed in the protectors place
				if(reserve > 0)
				{
					//if the current protector that we are on is null then we
					//place a new warrior in there and give them new weapons and powers
					//we subtract the amount of reserve we have.	
					if(protectors[i][skirmish_row] == NULL)
					{
						protectors[i][skirmish_row] = new Warrior;
						protectors[i][skirmish_row]->power = 100;
						protectors[i][skirmish_row]->weapon = "axe";
						reserve--;
						break;
					}
					
					
				}
			}
			//if the powers of the protector and the invadors are the same
			//than it results in a draw and nothing happens
			else
			{
				output << "Duel ends in draw" << endl;
			}
		}
		
	}

//return boolean of invader win if it was never reached within the for statement
	return invader_win;
    //returns true if the invaders breach the walls.
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;
  

    //read the input file and initialize the values here.
    //reading in the input from the file and placing into variables

    input >> rows;
    int col_invader;
    col_invader = rows;
    input >> cols;
    int row_invader;
    row_invader = cols;
    input >> reserve;
   	input >> skirmishes;


    //initialize the protectors and invaders here.
   	//creating an array for the warriors with a specific amount of rows in them
   	//by using dynamic allocation
    Warrior ***protectors = new Warrior**[rows];
    for(int i = 0; i < rows; i++)
    {
    	//creating an array for the number of columns that will be int the 
    	//protectors array
    	protectors[i] = new Warrior*[cols];
    	//looping through the amount of cols that we have for the protectors
    	//and creating a new warrior variable to be stored there
    	for(int j = 0; j < cols; j++)
    	{
    		protectors[i][j] = new Warrior;
    		//calculuating what the power of the warrior will be based
    		//upon the i and j calculation
    		protectors[i][j]->power = i * 10 + (j+1) * 10;

    		//if the warrior is in an even row they have an axe, if they are
    		//in an odd the have a sword
    		if(i % 2 == 0)
    		{
    			protectors[i][j]->weapon = "axe";
    		}
    		else 
    		{
    			protectors[i][j]->weapon = "sword";
    		}
    	}
    	
    }


    //creating an array for the invaders to be stored in and creaing
    //it with as many rows as indcated through dynamic memory allocation
    Warrior ***invaders = new Warrior**[row_invader];

    //looping through the rows in the invaders array 
    for(int i = 0; i < row_invader; i++)
    {
    	//placing columns in the specific row of the invaders using dynamic
    	//memory allocation
    	invaders[i] = new Warrior*[col_invader];
    	//looping through the columns to create a warrior at ever slot
    	//in the 2-d array
    	for(int j = 0; j < col_invader; j++)
    	{
    		//creating the new warrior with a power based upon an algorith,
    		//and their weapon is a sword if there row is odd and an axe
    		//if their row is odd
    		invaders[i][j] = new Warrior;
    		invaders[i][j]->power = i * 10 + (j+1) * 10;
    		if(i % 2 == 0)
    		{
    			invaders[i][j]->weapon = "sword";
    		}
    		else
    		{
    			invaders[i][j]->weapon = "axe";
    		}

    	}
    }


    //creaing the boolean for the end result to be stored in
    bool end = false;
    //looping through the number of skirmishes that
    // we have based upon the information
    //from the file that we read in
    for (int i=1; i <= skirmishes; i++)
    {

    	//creating the skirmish row  value and reading it in from the file
        int skirmish_row;
  
        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        //In general, it is bad style to throw everything into your
        // main function
       //making sure that the skirmish row value that we read in is in bounds
        //of hte amount of row and cols that we have
        if(skirmish_row >= 0 && skirmish_row < cols)
        {
        	//calling the skirmish functions  with specific parameters
        	end = skirmish(protectors, invaders, skirmish_row,
        	rows, cols, reserve, output);

        }
       
        
    }
    

    //output the winner and deallocate your memory.

    //if we get that end is true than we know that the invaders won

    if(end)
    {
    	output << "Winner: invaders" << endl;
    }

    //if end is false than we know that he protectors one
    else
    {
    	output << "Winner: protectors" << endl;
    }

    //looping through the protector array
    for(int i = 0; i < rows; i++)
    {
    	for(int j = 0; j < cols; j++)
    	{
    		//if the value at the specific address we are on is not null
    		//than we know there is a protector there and we delete the protector
    		if(protectors[i][j] != NULL)
    		{
    			delete protectors[i][j];
    		}
    		
    	}
    	//after we finish deleteing all the protectors in the cols, we can delete
    	///the cols themselves
    	delete[] protectors[i];
    }

    //now we can delete the array of protectors
    delete[] protectors;

    //looping through the invaders array
    for(int i = 0; i < row_invader; i++)
    {
    	for(int j = 0; j < col_invader; j++)
    	{
    		//if the value at the specific address we are on is not null
    		//than we know there is an invader there and we delete the invader
    		if(invaders[i][j] != NULL)
    		{
    			delete invaders[i][j];
    		}
       	}
       	//after we finish deleting all the protectors in the cols, we can delete
       	//the cols themselves
    	delete[] invaders[i];
    }
    //now we can delete the arra of invaders
    delete[] invaders;
   
    
    return 0;
}
