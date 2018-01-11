/*********************************************************************
 File:     chromakey.cpp

 Author:   Addison Allred

 Email address: aallred@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);
	

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory. 
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }

  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
	
  threshold = atof( argv[3]);

  // Call Method 1 Function
  method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask,inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage, chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask,inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char image[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{
	int num = 0;
	int red = 0;
	int blue = 0;
	int green = 0;
	//below we are taking all of the pixels on the corner of the picture
	//by doing so we are able to get the average RGB value of a green pixel
	//so that later on we can compare every pixel to this average green color
	//top of image
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num++;
		}
	}
	//left side of the image
	for(int i = 0; i < SIZE; i++)
	{

		for(int j = 0; j < 25 ; j++)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}
	//right side of the image
	for(int i = 0; i < SIZE; i++)
	{
	

		for(int j = SIZE; j > SIZE - 25; j--)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}
	//since we know that the bottom right corner of the picture
	// will always be green this is sampling
	//the colors of the bottom right corner
	for(int i = SIZE-10; i < SIZE; i++)
	{
	

		for(int j = SIZE; j > SIZE - 25; j--)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}

	//this is taking the sum of all the red green and blue
	// values from all of the pixels that 
	//we sampled in the for loop above and then dividing 
	//it by the number of pixel that we sampeled
	//so that we will be able to get the average RGB value of the green color in the 
	//provided image
	double dist = 0;
	red = red/num;
	blue = blue/num;
	green = green/num;

	//this is looping through every pixel in the provided image
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			
			//here we are getting the individual RBG values
			// for the one pixel that we are currently on
			//due to the itteration by the for loop
			int redpix = image[i][j][0];
			int greenpix = image[i][j][1];
			int bluepix = image[i][j][2];

			//this calculates the distance between the average
			// green value and the current pixel
			//that we are on
			dist = sqrt(pow((redpix - red), 2) + pow((bluepix - blue), 2)
			 + pow(greenpix - green,2));

			//this takes the distance of the pixel
			// that we are on and sees if it is 
			//larger than the threshold value that the
			// user puts in if it is greater than the 
			//threshold than the max value at that index becomes true,
			// if the distance is less than the
			//threshold provided by the user than that specific pixel becomes false. 
			if(dist > threshold)
			{
				mask[i][j] = true;
			}
			else if(dist < threshold)
			{
				mask[i][j] = false;
			}
		}
		}


}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char image[][SIZE][RGB], 
	     bool mask[][SIZE]) 	
{
	double threshold;
	int num = 0;
	int red = 0;
	int blue = 0;
	int green = 0;
	//below we are taking all of the pixels on the corner of the picture
	//by doing so we are able to get the average RGB value of a green pixel
	//so that later on we can compare every pixel to this average green color
	//top of image
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num++;
		}
	}
	//this samples the left side of the image
	for(int i = 0; i < SIZE; i++)
	{

		for(int j = 0; j < 5 ; j++)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}
	//This samples the right side fo the image pixels
	for(int i = 0; i < SIZE; i++)
	{
	

		for(int j = SIZE; j > SIZE - 10; j--)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}

	// this is sampling the bottom right side of the image because we know thta 
	//the bottom right side of the image will
	// be green as it is a very small part of the right
	//bottom corner
	for(int i = SIZE-10; i < SIZE; i++)
	{
	

		for(int j = SIZE; j > SIZE - 25; j--)
		{
			red += image[i][j][0];
			green += image[i][j][1];
			blue += image[i][j][2];
			num ++;
		}
	}

	//this is taking the sum of all the red green and blue values
	// from all of the pixels that 
	//we sampled in the for loop above and then dividing it by
	// the number of pixel that we sampeled
	//so that we will be able to get the average RGB value
	// of the green color in the 
	//provided image
	red = red/num;
	blue = blue/num;
	green = green/num;

	


	double dist2 = 0;
	
	int red1 = 0;
	int blue1 = 0;
	int green1 = 0;
	double dist_tot = 0.0;
	double max = 0.0;
	double min = 100.0;
	int times = 0;

	//this is looping through every pixel in the image
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			//this is getting the RGB values of the current
			// pixel that we are itterating through
			red1 = image[i][j][0];
			green1 = image[i][j][1];
			blue1 = image[i][j][2];

			//calculating the disctance between the average
			// green pixel and the value of the 
			//RGB values of the pixel that we are itterating
			// betwen by the for loop
			dist2 = sqrt(pow((red1 - red), 2) + pow((blue1 - blue), 2)
			 + pow(green1 - green,2));

			//this is getting the sum of the distance of every pixel
			// from the average green pixel
			dist_tot += dist2;

			//this provides the number of pixels that we itterate through. 
			times++;

			//looking if the distance calculated above is greater than the max value
			//if it is that distance becomes the new maximum vaue
			if(dist2 > max)
			{
				max = dist2;
			}
			// if the distance is less than the minimum value than that
			// becomes the new minimum value
			else if(dist2 < min)
			{
				min = dist2;
			}
		}
	}
	
	//calculating the average between the min and the max
	double average = (max+min)/2;

	//calculating the average total distance by taking the sum
	// distance of every pixel
	//and dividing it by the total amount of pixels in the image. 
	double dist_avg = dist_tot/times;
	
	//this is the calculation of the threshold using the numbers provided to us 
	//by the computations of the pixels and the information regarding the image
	//such as the max, min, dist_avg, the size,and
	 //the complexity of 2 arrays vs 
	//three aray
	threshold = (((max + min)/((dist_avg)/(average/(dist_avg/max)))))/(SIZE/2.5);
	
	
	//looping through every pixel
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			double dist = 0;
			//getting the RBG value of current pixel we are on
			red1 = image[i][j][0];
			green1 = image[i][j][1];
			blue1 = image[i][j][2];

			//calculating the distance of the pixel we are on by comparing it to the 
			//average green value pixel
			dist = sqrt(pow((red1 - red), 2) + pow((blue1 - blue), 2)
			 + pow(green1 - green,2));

			//if the distance is greater than the calculated threshold it is true at 
			//that pixel value, if the distance is less than the caluclated threshold
			//it is false at that pixel value in mask image, this will later be used 
			// by the replace function to determine if that pixel will be used as a 
			// pixel from the for ground image or the background image
			if(dist > threshold)
			{
				mask[i][j] = true;
			}
			else if(dist < threshold)
			{
				mask[i][j] = false;
			}
		}
	}


}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			//going through the rgb value of the pixel at i j location
			for(int k=0;k<3;k++) 
			{ 
				// if the mask pixel at that index of i j is true that
				// the outimage takes the pixel of the inimage
				//if the mask pixel at that index of i j is false, 
				// then that pixel of the outimage at location i
				// j is from the background image
				if(mask[i][j])
				{
					outImage[i][j][k] = inImage[i][j][k];

				}

				else
				{
					outImage[i][j][k] = bgImage[i][j][k];
				}
			}
		}
	}


}