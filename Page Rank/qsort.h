#include <iostream>
#include <vector>
//using namespace std;
//having the function use the template so we can implement the function with
//any type
template <class T>
//swap function to swap in variables
void swap(std::vector<T> &myArray, int first_value, int second_value)
{
	//getting the temp variable in the array that is at the first index
	//that is passed into swap
	T temp = myArray[first_value];
	//setting the value in the array at the first value index location
	//to be the value in the array at the second index location
	myArray[first_value] = myArray[second_value];
	//setting the array of the second value index location to be the
	//temp value, which was the original value at the first value
	//index
	myArray[second_value] = temp;
};
//template class and passing in the comparator used 
template <class T, class Comparator>
//function to calculate the pivot
int find_pivot(std::vector<T> &myArray, Comparator comp, int start, int end)
{
	//getting the start value for the value at the start index
	T start_val = myArray[start];
	//geting the end vale for the value at the end index
	T end_val = myArray[end];
	//calculating the middle index from adding the start and end together
	//and dividing it by 2
	int middle_index = (end + start)/2;
	//geting the middle value from the array at the middle index
	T middle_val = myArray[middle_index];
	//set the pivot equal to 0
	int pivot = 0;
	//if the start value is true when compared to the
	//end value
	if(comp(start_val, end_val))
	{
		//if the comparison of the middle value and the end value is true
		if(comp(middle_val, end_val))
		{
			//if the comparison of the start value to the middle value is true
			if(comp(start_val,middle_val))
			{
				//our pivot is thereby the middle value at the 
				//middle index
				pivot = middle_index;
			}
			//if the comparisn of start value to the middle value is false
			else
			{
				//the pivot is the value at the starting index
				pivot = start;
			}		
		}
		//if the comparision of the middle value and the end value is false
		else
		{
			//our pivot is the end index, which is the end value
			pivot = end;
		}
	}
	//jif the comparision of the start value and the end value is false
	else
	{
		//if the comparision of the start value and middle value is true
		if(comp(start_val, middle_val))
		{
			//or pivot is the value at the start index
			pivot = start;
		}
		//if the comparision of the start value and the middle value is false
		else
		{
			//if the comparision of the middle value and the end value is true
			if(comp(middle_val, end_val))
			{
				//our pivot is the value and the end index 
				pivot = end;
			}
			//if the comparision of the middle value and the end value is false
			else
			{
				//our pivot is the value and the middle index
				pivot = middle_index;
			}
		}
	}
	//return the pivot we just found
	return pivot;
};
//creating the function that will implement quicksort using templates
//so we can use any type of the array and the comparator passed int
template <class T, class Comparator>
void implement_quicksort(std::vector<T> &myArray, Comparator comp, 
int start, int end, int pivot, int& pivot_location)
{
	//this gets the pivot value at the pivot index
	T pivot_value = myArray[pivot];
	//swap the pivot and the end value so that our pivot is at the 
	//end of the array
	swap(myArray,pivot, end);
	//our left partition is our start value
	int left_partition = start;
	//right partition is the end minues 1 since we already 
	//switched the pivot the the end of the array and we dont need to 
	//compare the pivot to itself
	int right_partion = end-1;
	//while the left partition is less than the right partion
	while(left_partition < right_partion)
	{
		//if when comparing the left partion index value in the array
		//to the pivot value in the array is true
		if(comp(myArray[left_partition], pivot_value))
		{
			//we know that the value is in the correct place
			//so we can increase the left partition so we can move on the the next
			//value to check if it is in place
			left_partition++;
		}
		//if when comparing the left partion index value in the array
		//to the pivot value in the array is false
		else
		{
			//if the value is false when compared to the pivot, we know that
			//it is in the wrong location, so we will switch it with the value of
			//the right position so that it is placed in the right location in the
			//array
			swap(myArray,left_partition, right_partion);
			//since we swapped the left partion value with the right partition
			//value, decrease the right partion since we no longer need to 
			//evaluate this value in the array
			right_partion--;	
		}
	}
	//if the pivot value when compared to the value in the array 
	//at the left partition is true
	if(comp(pivot_value, myArray[left_partition]))
	{
		//we know that this is the location that we should place the partition
		//since when compared to the left partition it is true
		swap(myArray, end, left_partition);
		//set the pivot location to be that of the left partition since we just
		//placed the pivot value in the left partition index
		pivot_location = left_partition;
	}
	//if the pivot value when compared to the value in the array 
	//at the left partition is false
	else
	{
		//increase the value of the left partition so that it 
		//is a value that when compared to the partition is 
		//true since we know that it is in the right location because we 
		//are no longer in the while loop and know that the value in the
		//array just past the left partion is true when compared to 
		//the pivot value, myArray[left_partition]
		left_partition +=1;
		//swap the end value and the left partition so the partion
		//is in the correct location
		swap(myArray, end, left_partition);
		//update the pivot loation to be the left partition since this is
		//where we just switched the parition to. 
		pivot_location = left_partition;
	}
};
template <class T, class Comparator>
void quicksort_helper(std::vector<T> &myArray, Comparator comp, int start, int end)
{
	//if start is less than end
	if(start < end)
	{
		//the pivot index get from the find pivot function
		int pivot = find_pivot(myArray, comp, start, end);
		//pivot location so we know what to recurse over next time so we know the 
		//location where we already placed values greater than and less than it
		//on left or right side
		int pivot_location = pivot;
		//call function implement quicksort to sort the array with the 
		//following paramaters
		implement_quicksort(myArray, comp, start, end, pivot, pivot_location);
		//recurse on quick sort helper, with the same start value
		//but the end being the location of the pivot minus one
		//since we know the pivot is already in the correct location'
		//and we need to sort the values on the left side of the pivot
		quicksort_helper(myArray, comp, start, pivot_location-1);
		//recurse on quick sort helper with the start value being the 
		//pivot plus 1 since we need to sort all of the elements to the
		//right of the pivot and go all the way to the end of the
		//array
		quicksort_helper(myArray,comp, pivot_location+1, end);
	}
};
//creating the quicksort function, using template so we can have any type of vector
//and can use any comparator passed in
template <class T, class Comparator>
void QuickSort(std::vector<T> &myArray, Comparator comp)
{
	//the max index is the size of the array minus 1
	int max_index = int(myArray.size()) -1;
	//start value is 0
	int start = 0;
	//call to the quicksort helper
	quicksort_helper(myArray, comp, start, max_index);
};