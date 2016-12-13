#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include "rgbapixel.h"
#include <iostream>
using namespace std;

// default constructor
RGBAPixel::RGBAPixel()
{
red = 255;
green = 255;
blue = 255;
alpha = 255;
}

// specified constructor
RGBAPixel::RGBAPixel(unsigned char new_red, unsigned char new_green, unsigned char new_blue)
{
red = new_red;
green = new_green;
blue = new_blue;
}

#endif
