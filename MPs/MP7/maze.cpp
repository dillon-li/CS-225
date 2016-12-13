#include "maze.h"

SquareMaze::SquareMaze()
{
	width_maze = 0;
	height_maze = 0;
}

void SquareMaze::makeMaze(int width, int height)
{
	
	width_maze = width;
	height_maze = height;
	Maze.resize(width);
	for(int i = 0; i < width; i++)
		Maze[i].resize(height);
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y <height; y++)
		{
			Maze[x][y] = 2;
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
if(dir == 0)		// Step to the right
{
	if(x >= width_maze)
		return false;
	if((Maze[x][y] == 0) || (Maze[x][y] == 2))	// Has right or both walls
		return true;
	else
		return false;
}
else if(dir == 1)	// Step downwards
{
	if(y >= height_maze)
		return false;
	if((Maze[x][y] == 1) || (Maze[x][y] == 2))	// Has down or both walls
		return true;
	else
		return false;
}
else if(dir == 2)	// Step to the left
{
	if(x <= 0)
		return false;
	if((Maze[x-1][y] == 0) || (Maze[x-1][y] == 2))	// Coord to left has right or both walls
		return true;
	else
		return false;
}
else	// dir == 3 Step upwards
{
	if(y <= 0)
		return false;
	if((Maze[x][y-1] == 1) || (Maze[x][y-1] == 2))	// Coord above has bottom or both walls
		return true;
	else
		return false;
}
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
}

vector<int> SquareMaze::solveMaze()
{
vector<int> coolz;
return coolz; 
}

PNG * SquareMaze::drawMaze() const
{
	PNG * maze_image = new PNG(width_maze*10 + 1, height_maze*10 + 1);
	// Blacken first row except entrance
	(*maze_image)(0,0)->red = 0;
	(*maze_image)(0,0)->green = 0;
	(*maze_image)(0,0)->blue = 0;
	for(int i = 10; i < (*maze_image).width(); i++)
	{
		(*maze_image)(i,0)->red = 0;
		(*maze_image)(i,0)->green = 0;
		(*maze_image)(i,0)->blue = 0;
	}
	for(int x = 0; x < width_maze; x++)
	{
		for(int y = 0; y < height_maze; y++)
		{
			if((Maze[x][y] == 0) || (Maze[x][y] == 2))	// right wall or both exist
			{
				for(int k = 0; k <= 10; k++)
				{
					(*maze_image)((x+1)*10,y*10+k)->red = 0;
					(*maze_image)((x+1)*10,y*10+k)->green = 0;
					(*maze_image)((x+1)*10,y*10+k)->blue = 0;
				}
			}
			if((Maze[x][y] == 1) || (Maze[x][y] == 2))	// bottom wall or both exist
			{
				for(int k = 0; k <= 10; k++)
				{
					(*maze_image)(x*10+k,(y+1)*10)->red = 0;
					(*maze_image)(x*10+k,(y+1)*10)->green = 0;
					(*maze_image)(x*10+k,(y+1)*10)->blue = 0;
				}
			}
		}
	}
return maze_image;
}

PNG * SquareMaze::drawMazeWithSolution()
{
PNG* cool = new PNG;;
return cool;
}


