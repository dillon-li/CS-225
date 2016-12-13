/** Dillon Li - li160
 * @file main.cpp
 * A simple C++ program that rotates an image 180 degrees.
 */
#include <algorithm>
#include <iostream>

#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H


#include "png.h"

using namespace std;

/**
 * The main function in this program (the starting point of the execution of our
 * code).
 *
 * @return An integer indicating whether execution was successful.
 */
int main()
{
    // Open a new PNG image from the file in.png
    PNG image("in.png");

	// Retrieving hieght and width of image
    int height = image.height() - 1;
	int width = image.width() - 1;

	PNG newImage = image; // new image to output
	for(int x = 0; x <= width; x++)
	{
		for(int y = 0; y <= height; y++)
		{
			RGBAPixel * point = newImage(x,y);                         /* swaps the color values with the appropriate positions */
			RGBAPixel * point2 = image(width - x, height - y);
			point->red = point2->red;
			point->green = point2->green;
			point->blue = point2->blue;
			point->alpha = point2->alpha;
		}
	}
    // Save the modified image to a file called out.png, overwriting the file
    // if it already exists.
    newImage.writeToFile("out.png");

    return 0;
}
#endif

/*
	// Rotating the image
	for(int x = 0; x <= width; x++)
	{
		for(int y = 0; y <= height/2; y++)
		{			
			RGBAPixel * point1;
		}
	}
	*/
