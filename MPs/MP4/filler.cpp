/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
	solidColorPicker Malphite(fillColor);
	animation solid = filler::dfs::fill(img, x, y, Malphite, tolerance, frameFreq);
    return solid;
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
	gridColorPicker minesweep(gridColor, gridSpacing);
	animation grid = filler::dfs::fill(img, x, y, minesweep, tolerance, frameFreq);
    return grid;
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
	gradientColorPicker Gradius(fadeColor1, fadeColor2, radius, x, y);
	animation gradient = filler::dfs::fill(img, x, y, Gradius, tolerance, frameFreq);
    return gradient;
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
	animation Fulfilling = filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);	
    return Fulfilling;
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
	solidColorPicker Malphite(fillColor);
    animation b_solid = filler::bfs::fill(img, x, y, Malphite, tolerance, frameFreq);
    return b_solid;
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    gridColorPicker minesweep(gridColor, gridSpacing);
    animation b_grid = filler::bfs::fill(img, x, y, minesweep, tolerance, frameFreq);
    return b_grid;
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    gradientColorPicker Gradius(fadeColor1, fadeColor2, radius, x, y);
    animation b_gradient = filler::bfs::fill(img, x, y, Gradius, tolerance, frameFreq);
    return b_gradient;
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
   	animation Fulfilling = filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);	
    return Fulfilling;
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {	
	PNG Dillon;
	Dillon.resize(img.width(), img.height());	// use the red value to check if a pixel has been "processed"
	animation Michelle;
	int count = 0;		// for adding frames
	OrderingStructure<int> x_store;
	OrderingStructure<int> y_store;
	x_store.add(x);
	y_store.add(y);
/*	int peeked = x_store.peek();
	int peeked2 = y_store.peek();
	cout << " x stack is " << peeked << endl;
	cout << " y stack is " << peeked2 << endl;	*/
	int orig_red = img(x,y)->red;
	int orig_green = img(x,y)->green;
	int orig_blue = img(x,y)->blue;
	
	while((!x_store.isEmpty()) && (!y_store.isEmpty()))
	{
//		cout << "Entering while" << endl;
		int tempx = x_store.remove();
		int tempy = y_store.remove();
//		cout << tempx << tempy << endl;
		int red_diff = pow((img(tempx, tempy)->red - orig_red), 2);
		int green_diff = pow((img(tempx, tempy)->green - orig_green), 2);
		int blue_diff = pow((img(tempx, tempy)->blue - orig_blue), 2);
//		cout << (int)img(tempx, tempy)->red << (int)img(tempx, tempy)->blue << (int)img(tempx, tempy)->green << endl;
//		cout << orig_red << orig_blue << orig_green << endl;
		int sum_diffs = red_diff + green_diff + blue_diff;
//		cout << "sum diffs = " << sum_diffs << endl;
//		cout << "tolerance = " << tolerance << endl;
		if((sum_diffs <= tolerance) && (Dillon(tempx,tempy)->red != 0))
		{ 
			Dillon(tempx,tempy)->red = 0;	// processed
			*img(tempx,tempy) = fillColor(tempx,tempy);
			count++;
	//		cout << "count is " << count << endl;
			if(count % frameFreq == 0)
				Michelle.addFrame(img);
			if(img.width() > tempx+1)
			{
				x_store.add(tempx+1);	// right
				y_store.add(tempy);
			}
			if(img.height() > tempy+1)
			{
				x_store.add(tempx);		// down
				y_store.add(tempy+1);
			}
			if(tempx-1 >= 0)
			{
				x_store.add(tempx-1);	// left
				y_store.add(tempy);
			}
			if(tempy-1 >= 0)
			{		
				x_store.add(tempx);		// up
				y_store.add(tempy-1);
			} 
		}// end big if
	} // end while
	
    return Michelle;	
}
