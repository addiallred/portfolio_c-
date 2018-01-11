/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Addison Allred
 * USC email: aallred@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);



/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
	for(int i = 51; i > 0; i--)
	{
		
		int j;
		j = rand() % (i+1); // getting random value 
		int temp = cards[j]; 
		// storing a temp value so that when swapping j isn't written over
	
		cards[j] = cards[i];
		cards[i] = temp;
		
	}

	// this shuffles the cards using the fisher-yates algorithm
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{	
 	char num;
 	num = type[id%13][0]; 
 	// gives the type of value by using mod on the id, this gives
 	//the first value at the index id%13
 	char suit_type;
 	suit_type = suit[id/13];
 	 // gives the type of suit by dividing the id
 	if(num == '1')
 	{
 		cout << 10 << '-' << suit_type;
 		 // if the first pointer points to a value of one
 		//we know that the first pointer is pointing to 1 so the number printed out
 		//needs to be 10
 	}
 	else{
 		cout << num << "-" << suit_type; // printing out the results
 	}
 	
  /******** You complete ****************/

}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
	int num_value = 0;
	num_value = value[id%13]; 
	// moding the id and returning the number value based
	//upon the mod id index in the array value
	return num_value;

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
	int id; 
	// defines an id for what will be passed into print cards
	for(int z = 0; z < numCards; z++)
	{
		
		
		id = hand[z]; 
		// gets the number depending upon the hand value at that index
		printCard(id); //printing the id out
		cout << " " ; // putting a space
	}

	cout << endl;

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
	
  /******** You complete ****************/
  int total = 0;
  int card = 0;
  int nother = 0;
  int total2 = 0;
  int sum = 0;
  for(int i = 0; i < numCards; i++)
  // this for loop goes through all cards and adds up the value
  //of the cards
  {
  	card = hand[i];
  	total = cardValue(card);
  	sum += total;
  }
  if(sum > 21) 
  // seeing if the sum if larger than 21
  	{
  		
		for(int k = 0; k < numCards; k++)
		//going through all cards
  		{
  			nother = hand[k];
  			total2 = cardValue(nother);
  			
  			if(total2 == 11 && sum > 21)
  			// seeing if there is an ace in the hand and if the 
  				//sum is still greater than 21
  			{
  				sum -= 10;
  				//subtract 10 because aces schould be treated as 1 when 
  				//they were treated as 11 originially
  			}
  		
  		}
  		
  	}
  	
  return sum;//returns the sum

}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  while(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;//making sure that a seed is provided
  }
  int seed = atoi(argv[1]);
  srand(seed);//taking in the value and seeing srand

  int cards[52];//defining the size of the card deck
  
 
  
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  string play = "y";
  //initializing play
  while(play == "y")// play the game while the player returns y
  {
  	int dealer[21];
  	int player[21];
  	for(int i = 0; i < 52; i++)// initializing the values of the cards
  	{
  		cards[i] = i;
  	}
  	shuffle(cards);//calling the shuffle function
  	
  	
  	player[0] = cards[0];
  	dealer[0] = cards[1];
  	player[1] = cards[2];
  	dealer[1] = cards[3];
  	//defining the first card values for the player and the dealer



  	int cards_index = 3;// the index the array is filled up to
  	int player_index = 1;//the index that the array is filled up to
  	int dealer_index = 1; // the index the array is filled up to

  	int player_numcards = 2;// how many cards the player has

  	cout << "Dealer: ? "; // prints out a ? for the first card
	 
	
	printCard(dealer[1]); //printing the id out of the card
	cout << endl ; // putting a space

  	cout << "Player: ";

  	printHand(player, player_numcards); //printing out hte players cards


  	int dealer_numcards = 2; // how many cards the dealer has

  	bool end_game = false;

  	while(getBestScore(player, player_numcards) <= 21 && !(end_game)) 
  	//playing the game while
  		//the player has a score smaller than 21 and end_game is false
  	{
  		string hors;
  		bool perfect_score = false;

  		if(getBestScore(player, player_numcards) != 21)
  		 // this is if the player doesn;t
  		//have a score of exactly 21
  		{
  			
  			cout << "Type 'h' to hit and 's' to stay: " << endl;
  			cin >> hors;
  		}
  		
  		if(getBestScore(player,player_numcards) == 21)
  		{
  			perfect_score = true;
  		}

  		

  		if(hors == "h")
  		{
  			cards_index++;
  			player_index++;
  			player[player_index] = cards[cards_index];
  			player_numcards++;
  			cout << "Player: ";
  			printHand(player, player_numcards);

  		}

  		else if(hors == "s" || perfect_score)
  		{
  			
  			while(getBestScore(dealer, dealer_numcards) < 17)

  			{
  				cards_index++;
  				dealer_index++;
  				dealer[dealer_index] = cards[cards_index]
  				;//assigns the next available card
  				//to the dealers hand
  				dealer_numcards++;
  				// increases the number of cards the dealer hands
  			} // does this while loop while the dealers score is less than 17, 
  			//and while the player doesn't have a perfect score


  			cout << "Dealer: ";

  			printHand(dealer, dealer_numcards);

  			int player_score;
  			int dealer_score;

  			player_score = getBestScore(player, player_numcards);
  			dealer_score = getBestScore(dealer,dealer_numcards);
  			//getting the scores
  			
  			
  			if(dealer_score > 21)
  			{
  				cout << "Dealer bust" << endl;
  				cout << "Win " << player_score << " " << dealer_score << endl;
  				end_game = true;
  			}
  			else if(player_score < dealer_score)
  			{
  				cout << "Lose " << player_score << " " << dealer_score << endl;
  				end_game = true;
  			}
  			else if(player_score > dealer_score)
  			{
  				cout << "Win " << player_score << " " << dealer_score << endl;
  				end_game = true;
  			}
  			else if(player_score == dealer_score)
  			{
  				cout << "Tie " << player_score << " " << dealer_score << endl;
  				end_game = true;
  			}
  			//above are several of the different conditions that can happen from the game
  			//the dealer can bust, the dealer can have a higher score than the player
  			// the dealer can have a lower score than the player
  			// the dealer and the player can have the same score
  		}
  	}

  	if(getBestScore(player, player_numcards) > 21) 
  	{
  		cout << "Player bust" << endl;
  		cout << "Lose " << getBestScore(player, player_numcards) << " ";
  		cout << getBestScore(dealer, dealer_numcards) << endl;
  	}
  	// seeing if the player bust and printing out correct results
  	
  	cout<< "Play again?[y/n]" << endl; //asking if want to play again
  	cin >> play;

  	
  }




  return 0;
}