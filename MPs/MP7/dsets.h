#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>
using std::vector;

class DisjointSets
{
public:
	// Creates n unconnected root nodes at the end of the vector. 
	void addelements(int num);
	// This function should compress paths and works as described in lecture. 
	int find(int elem);
	// This function should be implemented as union-by-size. 
	void setunion(int a, int b);

private:
	vector<int> sets;
};

#endif
