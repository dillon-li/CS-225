#ifndef _SCENE_H_
#define _SCENE_H_

#include "image.h"

class Scene
{
	public:
		Scene(int max); 			// constructor
		~Scene();					// destructor
		Scene(const Scene &source); // copy constructor
		
	// The assignment operator for the Scene class:
		const Scene & operator= (const Scene &source);

	// Modifies the size of the array of Image pointers without changing their indices:
		void changemaxlayers(int newmax);

	// Adds a picture to the scene by placing it in the array cell corresponding to the given index and storing its x and y coordinates: 
		void addpicture(const char *FileName, int index, int x, int y);

	// Moves an Image from one layer to another. 
		void changelayer(int index, int newindex);

	// Changes the x and y coordinates of the Image in the specified layer. 
		void translate(int index, int x, int y);

	// Deletes the Image at the given index. 
		void deletepicture(int index);

	// This function will return a pointer to the Image at the specified index, not a copy of it.
		Image * getpicture(int index) const;

	// Draws the whole scene on one Image and returns that Image by value. 
		Image drawscene() const;

	// Variables for Scene class
		int max_images;
		Image ** scenes;  // array of image pointers
		int *xcoord;
		int *ycoord;

	private:
		
 		// Helper functions
		void clear();
		void copy(const Scene &source);
};
#endif
