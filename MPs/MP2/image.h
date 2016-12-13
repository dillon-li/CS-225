/* Image header file from doxygen for mp2 */

#include "png.h"
#ifndef EIMAGE_H
#define EIMAGE_H

class Image : public PNG
{
public:
	void flipleft();
	void adjustbrightness(int r, int g, int b);
	void invertcolors();
};

#endif
