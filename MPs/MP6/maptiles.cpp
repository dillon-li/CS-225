/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    // Black mosaic
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas * finalImage = new MosaicCanvas(rows,columns);
    /* Create a vector of points representing the average colors of the tiles
    And creates a mapping from RGBAPixels to the indices of the tile vector */
    vector< Point<3> > avgColors;
    map<RGBAPixel, int> tile_avg_map;
    for(int numTile=0; numTile<theTiles.size(); numTile++)
    {
    	// Average color of the tile
    	RGBAPixel tempPix=theTiles[numTile].getAverageColor();
    	
    	// Map that color to the index
    	tile_avg_map[tempPix]=numTile;
    	Point<3> tempPoint(tempPix.red, tempPix.green, tempPix.blue);
    	
    	// Add point to vector
    	avgColors.push_back(tempPoint);
    }
    // Construct a KDTree that represents the tiles' average colors
    KDTree<3> tree(avgColors);
    
    // Find the tile that fits each region
    for(int i=0; i<rows; i++)
    {
    	for(int j=0; j<columns; j++)
    	{
    		// Get the tile whose average color is closest to the region's color
    		const TileImage * matchTile=get_match_at_idx(tree, tile_avg_map, theTiles, theSource, i,j);
    		// Set the tile into the mosaic
    		finalImage->setTile(i,j,*matchTile);
    	}
    }
	return finalImage;
}

const TileImage * get_match_at_idx(const KDTree<3> &tree, map<RGBAPixel, int> tile_avg_map, const vector<TileImage> &theTiles, const SourceImage &theSource, int row, int col)
{
	// Source image region's color
    RGBAPixel regionColor=theSource.getRegionColor(row,col);
    
    // Convert the pixel to a point
    Point<3> regionPoint(regionColor.red, regionColor.green, regionColor.blue);
    
    // Return the nearest neighbor value from the tile tree
    Point<3> NNPoint=tree.findNearestNeighbor(regionPoint);
    
    // Convert the point to a pixel
    RGBAPixel mapPixel(NNPoint[0],NNPoint[1],NNPoint[2]);
    
    // Map the pixel to an index in the tile vector
    int tileIdx=tile_avg_map[mapPixel];
    
    // Create a pointer to matched tile
    const TileImage * ret=&theTiles[tileIdx];
    
	return ret;
}
