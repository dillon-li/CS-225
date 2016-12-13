/* Implements public functions in image.h */

#include "image.h"

void Image::flipleft()
{
	int width = Image::width() - 1;
	int height = Image::height() - 1;
	int flip_line = width/2;
	for(int x = 0; x <= flip_line; x++)
	{
		for(int y = 0; y <= height; y++)
		{
			// declare the pointers for points to be swapped
			RGBAPixel * point = operator()(x,y);
			RGBAPixel * flipped_point = operator()(width - x, y);

			// temp variables
			int temp_red = point->red; 
			int temp_green = point->green;
			int temp_blue = point->blue;

			// swapping the points
			point->red = flipped_point->red;
			flipped_point->red = temp_red;
			point->green = flipped_point->green;
			flipped_point->green = temp_green;
			point->blue = flipped_point->blue;
			flipped_point->blue = temp_blue;
		}
	}			
}

void Image::adjustbrightness(int r, int g, int b)
{
	int width = Image::width();
	int height = Image::height();
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			RGBAPixel * point = operator()(x,y);

			if((point->red + r >= 0) && (point->red + r <= 255))
				point->red = point->red + r;
			else if(point->red + r < 0)
				point->red = 0;
			else 
				point->red = 255;

			if((point->green + g >= 0) && (point->green + g <= 255))
				point->green = point->green + g;
			else if(point->green + g < 0)
				point->green = 0;
			else
				point->green = 255;

			if((point->blue + b >= 0) && (point->blue + b <= 255))
				point->blue = point->blue + b;
			else if(point->blue + b < 0)
				point->blue = 0;
			else 
				point->blue = 255;
		} // end 2nd for
	} // end 1st for
} // end function

void Image::invertcolors()
{
	int width = Image::width();
	int height = Image::height();
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			RGBAPixel * point = operator()(x,y);
			point->red = 255 - point->red;
			point->green = 255 - point->green;
			point->blue = 255 - point->blue;
		}
	}
}
