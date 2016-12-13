/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <math.h>
#include <iostream>

using namespace std;

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
	if(first[curDim] == second[curDim])
		return (first < second);	// tiebreaker
	else
		return (first[curDim] < second[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{ 
	int currentDistance = 0;
	int potentialDistance = 0;
    for(int i = 0; i < Dim; i++)
	{
		currentDistance += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
		potentialDistance += (potential[i]-target[i])*(potential[i]-target[i]);
	}
	
    return (potentialDistance < currentDistance);
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	points = newPoints;
	BuildTree(points, 0, points.size()-1, 0); 
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & point_list,int left, int right, int pivotIndex, int curDim)
{
	Point<Dim> pivotValue = point_list[pivotIndex];
	int storeIndex = left;
	point_list[pivotIndex] = point_list[right];
	point_list[right] = pivotValue;	// Move pivot to the end
	
	for(int i = left; i < right; i++)
	{
		Point<Dim> temp = point_list[i];
		if(smallerDimVal(point_list[i], pivotValue, curDim))
		{
			point_list[i] = point_list[storeIndex];
			point_list[storeIndex] = temp;
			storeIndex++;
		}
	}
	Point<Dim> temp2 = point_list[right];
	point_list[right] = point_list[storeIndex];
	point_list[storeIndex] = temp2;
	return storeIndex;	
}

template<int Dim>
Point<Dim> KDTree<Dim>::select( vector< Point<Dim> > & point_list, int left, int right, int k, int curDim)
{
	if(left >= right)
		return point_list[right];
	int pivotIndex = (left+right) / 2;
	int pivotNewIndex = partition(point_list, left, right, pivotIndex, curDim);
	int pivotDist = pivotNewIndex - left + 1;
	if(pivotDist == k)
		return point_list[pivotNewIndex];
	else if(k < pivotDist)
		return select(point_list, left, pivotNewIndex-1, k, curDim);
	else
		return select(point_list, pivotNewIndex+1, right, k-pivotDist, curDim);
}

template<int Dim>
void KDTree<Dim>::BuildTree(vector< Point<Dim> > & pointsList, int left, int right, int curDim)
{
	int n = right - left;
	if(left > right) return;
	int median = floor(n / 2) + 1;
	Point<Dim> temp = select(pointsList, left, right, median, curDim);
	int newIndex = floor((right+left)/2);
	BuildTree(pointsList, left, newIndex-1, (curDim+1)%Dim);
	BuildTree(pointsList, newIndex+1, right, (curDim+1)%Dim);	

}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
   return NearestNeighborHelper(query, 0, points.size()-1, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::NearestNeighborHelper(const Point<Dim> & query, int left, int right, int curDim) const
{
	if(left >= right)
		return points[left];
	Point<Dim> currentBest;
	int newIndex = floor((left+right)/2);
	if(smallerDimVal(query, points[newIndex], curDim))  // left
		currentBest = NearestNeighborHelper(query, left, newIndex-1, (curDim+1)%Dim);
	else
		currentBest = NearestNeighborHelper(query, newIndex+1, right, (curDim+1)%Dim);
	if(shouldReplace(query, currentBest, points[newIndex]))
		currentBest = points[newIndex];
	int distance_subtree = (query[curDim] - (points[newIndex])[curDim])*(query[curDim] - (points[newIndex])[curDim]);
	int distance_curBest = (query[curDim] - currentBest[curDim])*(query[curDim] - currentBest[curDim]);
	if(distance_subtree <= distance_curBest)
	{
		Point<Dim> potential;
		if(smallerDimVal(points[newIndex], query, curDim))
			potential = NearestNeighborHelper(query, left, newIndex-1, (curDim+1)%Dim);
		else
			potential = NearestNeighborHelper(query, newIndex+1, right, (curDim+1)%Dim);
		if(shouldReplace(query, currentBest, potential))
			currentBest = potential;
	}
	return currentBest;
}
	
