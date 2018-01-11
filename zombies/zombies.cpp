/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Addison Allred
 * USC email: aallred@usc.edu
 * Comments (you want us to know):
 *
 *
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
	bool pop[MAXPOP];

 	int k;
 	int m;
 	int N;
 	int seed;

	cout << "Enter the Following: \nN: "<< endl;
 	cin>> N;
 	cout << "k: " << endl;
 	cin >> k;
 	cout <<"m: " << endl;
 	cin >> m;
 	cout << "seed:" << endl;
 	cin>> seed;
 	srand(seed);
 	int maxnights = 0;
 	int minnights = INT_MAX;
 	int totalnights = 0;


	for( int run = 1; run <= m; run++ ) 
	{
		int nights = 0;
  
 		for(int i = 0; i < N; i++)
 		{
    		if(i< k)
  			{
  				pop[i] = true;
  			}
  			else
  			{
  				pop[i] = false;
  			}
 	
		}
		int humans = N-k;
		int zombies = k;
		while(humans !=0)
 		{
 			int numbites = zombies;
 			for(int z = 0; z < numbites; z++)
 			{
 				int y = N;
 				int rand_num = rand() % y + 0;
 				if(!(pop[rand_num]))
 				{
 					pop[rand_num] = true;
 					humans--;
 					zombies++;
 				}
 		
 			}
 			nights++;
 		}
 		totalnights += nights;
 		if (maxnights < nights)
 		{
 			maxnights = nights;
 		}

 		else if(minnights > nights)
 		{
 			minnights = nights;
 		}
 	}

 	double average = 0;
 	average = totalnights/(double) m;

 	cout<<"Average Nights: " << average << endl;
 	cout<< "Max Nights: " << maxnights << endl;
 	cout << "Min Nights: " << minnights<<endl;
  	return 0;


}