// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
		// Constructs empty tree
		Quadtree();  
		// Constructs a Quadtree representing the upper-left d by d block of the source image
		Quadtree(const PNG & source, int resolution);
		// Copy Constructor
		Quadtree(Quadtree const & other);
		// Destructor
		~Quadtree();
		/* Deletes the current contents of this Quadtree object, then turns it into a Quadtree object 
		 representing the upper-left d by d block of source. */
		void buildTree(PNG const &source, int resolution);
	
	
	private:
		
	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode(RGBAPixel data);	// Constructor
		
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	
	
	/**** Functions added for testing/grading                ****/
	void clear(QuadtreeNode * current);	// helper function to free memory: used for destructor
	void helperbuildTree(PNG const &source, int resolution, int x, int y); // buildtree helper function
	
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
