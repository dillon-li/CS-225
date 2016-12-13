#include "dsets.h"


void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++)
		sets.push_back(-1);
} 

int DisjointSets::find(int elem)
{
	if(sets[elem] < 0) 
		return elem;
	else	
		return sets[elem] = find(sets[elem]);
}

void DisjointSets::setunion(int a, int b)
{
	int root1 = find(a);
	int root2 = find(b);
	int newsize = sets[root1] + sets[root2];
	if(-1*sets[root2] > -1*sets[root1])
	{
		sets[root1] = root2;
		sets[root2] = newsize;
	}
	else
	{
		sets[root2] = root1;
		sets[root1] = newsize;
	}
}
