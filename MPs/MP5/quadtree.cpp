// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

// Constructor for an empty tree
Quadtree::Quadtree()
{
root = NULL;
root->nwChild = NULL;
root->neChild = NULL;
root->swChild = NULL;
root->seChild = NULL;
//root->element;	Not entirely sure what to do with this yet. We'll see
}

Quadtree::Quadtree(const PNG & source, int resolution)
{
}

// Destructor
Quadtree::~Quadtree()
{
	clear(root);
}

// Helper function for the destructor
void Quadtree::clear(QuadtreeNode * current)
{
	if(current == NULL)
		return;
	clear(current->nwChild);
	clear(current->neChild);
	clear(current->swChild);
	clear(current->seChild);
	delete current;
}

/* Deletes the current contents of this Quadtree object, then turns it into a Quadtree 
 object representing the upper-left d by d block of source. */
void buildTree(PNG const &source, int resolution)
{
}

Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel data)
{
	nwChild = NULL;
	neChild = NULL;
	swChild = NULL;
	seChild = NULL;
	element = data;
}
/*
void Quadtree::helperbuildTree(PNG const &source, int resolution, int x, int y)
{
	if(resolution == 1)
	{
		QuadtreeNode* leaf = new QuadtreeNode(source(x,y)); */
