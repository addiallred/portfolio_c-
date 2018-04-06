#include "LengthMismatch.h"
#include "qsort.h"
#include <iostream>

using namespace std;
//defining the function assignPlates which will create the plates
//to be served so that each plate has the same amount of calories
vector<pair<int, int> > assignPlates(vector<int> turkeys, vector<int> potatoes)
{ 
	//creating the vector which will have pairs of the turkey callori and the
	//potatoe callori. 
	vector<pair<int, int> > pair_plates;
	//getting the number of turkeys based of the size of the turkey vector
	int number_turkey = int(turkeys.size());
	//geting the number of potatoes based of the size of the potatoes vector
	int number_potatoes = int(potatoes.size());
	//if the number of potatoes we have was different from the number of turkey
	//we know that we can not make a correct pairing of plates
	if(number_potatoes != number_turkey)
	{
		//throw the exception mismatch because there was
		//a different amount of turkey and potatoes so you can't construct
		//the plates
		throw LengthMismatch(number_turkey, number_potatoes);
	}
	//use quicksort to sort the turkeys from least to greates
	QuickSort(turkeys, less<int>());
	//use quicksort to sort the potatoes from gretaest to least. 
	QuickSort(potatoes, greater<int>());
	//since we know that we must be able to construct plates 
	//all with the same calorie amount, and since
	//the greatest amount of potatoes calories 
	//has to go with the least amount of turkeys calories
	//the required calorie amount can be considered as the first turkeys
	//calorie plus the second potatoes calories which will be the greatest
	//calorie count for the potatoes. 
	int required_cal = turkeys[0] + potatoes[0];
	//this will keep track if we found any  pairing that doesn't meat the 
	//required calorie amount 
	bool correct_pairing = true;
	//iterate of the number of turkey(which is also the same number)
	//of potatoes since they have to be the same amount
	//in order to have a correct pairing
	for(int i = 0; i < number_turkey; i++)
	{
		//the current turkey cal and potatoe cal is 
		//the ith index in the sorted turkeys and potatoes vector
		int turkeys_cal = turkeys[i];
		int potatoes_cal = potatoes[i];
		//if the turkey cal plus potatoe cal is the required calorie
		//count required
		if((turkeys_cal + potatoes_cal) == required_cal)
		{
			//create a temporary pair of that calorie of 
			//potatoe and turkey
			pair<int, int> temp(turkeys_cal, potatoes_cal);
			//add the temp pairing to the vector
			pair_plates.push_back(temp);
		}
		//if they are not the required calorie count 
		else
		{
			//we know that this fails the requirment
			//so there is no correct pairing of the plates
			// so that the plates all have the same calorie count
			correct_pairing = false;
			//break out of the for loop so you don't continue to 
			//see if items are pairings since you already know it cannot be a pairing
			//since it entered into this else statement
			break;
		}
	}
	//if we don't have a correct paing
	if(!correct_pairing)
	{
		//remove all of the pairs from the pair vector
		//so the vector is empty
		for(int i = 0; i < int(pair_plates.size()); i++)
		{
			pair_plates.pop_back();
		}
	}
	//return the pair vector
	return pair_plates;
}


