/* Implementation of scene.h functions/constructors, etc.
	MP2 scene/image manipulation */

#include <iostream>
#include "scene.h"

using namespace std;

// constructor
Scene::Scene(int max)
{
	max_images = max;
	scenes = new Image*[max];
	for(int i = 0; i < max; i++)
		scenes[i] = NULL;
	xcoord = new int[max];
	ycoord = new int[max];
	for(int j = 0; j < max; j++)
	{
		xcoord[j] = -1;
		ycoord[j] = -1;
	}
}

// copy contructor
Scene::Scene(const Scene &source)
{
	copy(source);
	// STILL NEED COORDINATES STUFFS
}

// Destructor
Scene::~Scene()
{
	clear();
}

/* Image manipulation functions */

const Scene & Scene::operator= (const Scene &source) 	
{
	if(this != &source)	// self-assignment check
	{
		clear();
		copy(source);
	}
	return *this;   // might be error here
}

void Scene::changemaxlayers(int newmax)
{
	bool invalid = false;
	if(newmax < max_images)
	for(int index = max_images - newmax - 1; index < max_images; index++)
	{
		if(scenes[index] != NULL)
			invalid = true;
	}
	else
		invalid = false;

	if(invalid)
		cout << "invalid newmax" << endl;
	else
		max_images = newmax;
}

void Scene::addpicture(const char* FileName, int index, int x, int y)
{
	Image* new_picture = new Image();
	new_picture->readFromFile(FileName);
	if(index > (max_images - 1))
		cout << "index out of bounds" << endl;
	else
	{
		scenes[index] = new_picture;
		xcoord[index] = x;
		ycoord[index] = y;
	}	
}

void Scene::changelayer(int index, int newindex)
{
	int proper_index = max_images - 1;
	if(index == newindex)
		return;
	if((index > proper_index) || (newindex > proper_index))
		cout << "invalid index" << endl;
	else
	{
		if(scenes[newindex] != NULL)
			delete scenes[newindex];
		scenes[newindex] = scenes[index];
		xcoord[newindex] = xcoord[index];
		ycoord[newindex] = ycoord[index];
		scenes[index] = NULL;
	}
}

void Scene::translate(int index, int x, int y)
{
	if((index > (max_images-1)) || (scenes[index] == NULL))
		cout << "invalid index" << endl;
	else
	{
		xcoord[index] = x;
		ycoord[index] = y;
	}
}

void Scene::deletepicture(int index)
{
	if((index > (max_images-1)) || (scenes[index] == NULL))
		cout << "invalid index" << endl;
	else
	{
		delete scenes[index];
		scenes[index] = NULL;
		xcoord[index] = -1;  // sets to invalid value
		ycoord[index] = -1;
	}
}

Image * Scene::getpicture(int index) const
{
	if(index > (max_images-1))
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	else
		return scenes[index];	
}

Image Scene::drawscene() const
{
	int width_max = 0;
	int height_max = 0;
	for(int i = 0; i < max_images; i++)
	{
	if(scenes[i] != NULL)
	{
		if(((int)scenes[i]->width() + xcoord[i]) > width_max)
			width_max = (int)scenes[i]->width() + xcoord[i];
		if(((int)scenes[i]->height() + ycoord[i]) > height_max)
			height_max = (int)scenes[i]->height() + ycoord[i];
	}
	}
	Image* whole_scene = new Image();
	whole_scene->resize(width_max, height_max);
	
	for(int k = 0; k < max_images; k++)
	{
	  if(scenes[k] != NULL)
	  {
		for(int x = xcoord[k]; x < (int)scenes[k]->width(); x++)
		{
			for(int y = ycoord[k]; y < (int)scenes[k]->height(); y++)
			{
				RGBAPixel * coordinate = whole_scene->operator()(x,y);
				RGBAPixel * picture_pixel = scenes[k]->operator()(x,y);
				*coordinate = *picture_pixel;
			}
		}
	  }
	} 
//cout << " *****Still Working*****\n" << endl;
return *whole_scene;
}
	

/* Helper Functions */
void Scene::copy(const Scene &source)
{
	max_images = source.max_images;
	scenes = new Image*[max_images];
	for(int i = 0; i < max_images; i++)
		*(scenes[i]) = *(source.scenes[i]);
	for(int j = 0; j < max_images; j++)
	{
		xcoord[j] = source.xcoord[j];
		ycoord[j] = source.ycoord[j];
	}
}

void Scene::clear()
{
	for(int i =0; i < max_images; i++)
		delete scenes[i];
	if(scenes != NULL) 
		delete [] scenes;
	delete [] xcoord;
	delete [] ycoord;
}
