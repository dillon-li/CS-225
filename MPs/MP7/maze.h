#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include "png.h"

using std::vector;

class SquareMaze
{
public:
	// constructor
	SquareMaze();
	// Makes new SquareMaze (deletes old one too)
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();

private:
	vector< vector<int> > Maze;
	int width_maze;
	int height_maze;
};
#endif
