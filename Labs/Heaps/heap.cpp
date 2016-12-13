/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <math.h>  // for floor function
#include <iostream>

using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return 2*currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
	if(2*currentIdx > _elems.size()-1)
    	return false;
	else
		return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	if(higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
    	return leftChild(currentIdx);
	else
		return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    /// @todo Implement the heapifyDown algorithm.
	if(!hasAChild(currentIdx))
		return;
	size_t childIdx = maxPriorityChild(currentIdx);
	if(higherPriority(_elems[childIdx], _elems[currentIdx]))
	{
		std::swap(_elems[childIdx], _elems[currentIdx]);
		heapifyDown(childIdx);
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems.push_back(0); // index at 1
	
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
	_elems.push_back(0);
	for(int j = 0; j < elems.size(); j++)
		_elems.push_back(elems[j]);
	for(int i = parent(_elems.size()-1); i > 0; i--)
		heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
	T root_popped = _elems[root()];
	_elems[root()] = _elems[_elems.size()-1];
	_elems.pop_back();
	heapifyDown(root());
    return root_popped;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    T min = _elems[root()];
    return min;
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
//	if(_elems.size() == _elems.max_size())
//		_elems.resize(_elems.size()+1);
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
	
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
	if(_elems.size() == 1)
		return true;
	else
		return false;
}
