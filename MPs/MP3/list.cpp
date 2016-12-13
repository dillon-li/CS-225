/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
#include <string>

using namespace std;

template <class T>
List<T>::~List()
{
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    ListNode * current = head;
	while(current != NULL)
	{
		ListNode * temp = current->next;
		delete current;
		current = temp;
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    ListNode * newFront = new ListNode(ndata);
	if(head == NULL)
	{
		head = newFront;
		tail = newFront;
	}
	else
	{
		newFront->next = head;
		head->prev = newFront;
		head = newFront;
	}
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    ListNode * newBack = new ListNode(ndata);
	if(tail == NULL)
	{
		tail = newBack;
		head = newBack;
	}
	else
	{
		newBack->prev = tail;
		tail->next = newBack;
		tail = newBack;
	}
	length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	if (!empty())
    {
        ListNode * start = startPoint;                // to change the endPoint to at the end
        ListNode * temp = startPoint->next;
		ListNode * start_next = endPoint->next;
		ListNode * end_before = startPoint->prev;
        while(startPoint != endPoint)
        {
            temp = startPoint->next;
            startPoint->next = startPoint->prev;    // swaps next and previous instances to reverse list
            startPoint->prev = temp;
            startPoint = temp;
        }
		startPoint->next = startPoint->prev;		// must do one more time for last iteration
		startPoint->prev = temp;
        endPoint = start;
		if(start_next != NULL) 						// Fixing pointers outside of startPoint-endPoint
		{	
			endPoint->next = start_next;
			start_next->prev = endPoint;
		}
		else 
		{
			tail = endPoint;
			endPoint->next = NULL;
		}
		if(end_before != NULL)
		{
			startPoint->prev = end_before;
			end_before->next = startPoint;
		} 
		else 
		{
			head = startPoint;
			startPoint->prev = NULL;
		}
    } 
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
	ListNode * curr_start = head;
	ListNode * curr_end = head;
	for(int i = 1; i < n; i++)
		if(curr_end->next != NULL) curr_end = curr_end->next;		// First endpoint
	while(curr_end->next != NULL)
	{
		ListNode * temp = curr_end->next;
		reverse(curr_start, curr_end);
		if(temp != NULL)
		{
			curr_start = temp;
			curr_end = temp;
		}
		for(int j = 1; j < n; j++)
			if(curr_end->next != NULL) curr_end = curr_end->next;	// Sets next endpoints
	}
	reverse(curr_start, curr_end);
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if((head != NULL) && (head->next != NULL))  // there are at least 2 elements in the list
	{
    	ListNode * start = head->next;
		ListNode * temp = (start->next)->next;
	
		while(temp != NULL)
		{
			ListNode * connect_before = start->prev;
			ListNode * connect_after = start->next;
			temp = (start->next)->next;
			tail->next = start;
			start->prev = tail;
			start->next = NULL;
			connect_before->next = connect_after;
			connect_after->prev = connect_before;
			tail = start;
			start = temp;
		}
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	if (empty())
        return NULL;
    ListNode * split_start = start;
	for(int i = 0; i < splitPoint; i++)
		split_start = split_start->next;
	ListNode* end_first = split_start->prev;
	end_first->next = NULL;
	split_start->prev = NULL;
    return split_start; 
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	
	if (empty())
        return NULL;
	ListNode * start = first;
	ListNode * temp = second->next;
	ListNode * link = first;

	while(second != NULL)
	{
		if(second->data < first->data)  
		{
			if(first->prev == NULL) // For first run to set new start pointer
			{
				second->next = first;
				first->prev = second;
				start = first->prev;		// Sets new start pointer
				link = start;				// Set for reference later
				second = temp;
				if(second != NULL) temp = second->next;  // conditional for if there is only 1 element in list2
			}
			else
			{
				link = first->prev;
				link->next = second;
				second->prev = link;
				second->next = first;
				first->prev = second;
				link = second;
				second = temp;
				if(second != NULL) temp = second->next;  // conditional for if there is only 1 element in list2
			}
		}
		else
		{
			if(first->next == NULL)
			{
				first->next = second;
				second->prev = first;
				second = NULL;
			}
			else
				first = first->next;
		}
	}	// end while
	return start;
}

/*
	if (empty())
        return NULL;
	ListNode * start = first;
	ListNode * temp = second->next;
	
	if((first->next == NULL) && (second->next == NULL))
	{
		if(first->data < second->data)
		{
			first->next = second;
			second ->prev = first;
		}
		else
		{
			second->next = first;
			first->prev = second;
			start = second;
		}
		return start;
	}

	while(second != NULL)
	{
		if(second->data < first->data)	// if first element in list2 is less than list1, start will be first element of list2
		{
			second->next = first;
			first->prev = second;
			start = first->prev;
			second = temp;
			if(second != NULL) temp = second->next;
		}
		if(second != NULL)
		{
			while((second != NULL) && (second->data < first->data))	// Adds the rest of list2 that is less than first element of list1
			{
				start->next = second;
				second->prev = start;
				second->next = first;
				first->prev = second;
				second = temp;
				if(second != NULL) temp = second->next;
			}
		}
		while((first->next != NULL) && (second != NULL) && ((first->next)->data < second->data))
		{
			first = first->next;	// Iterates first to element before insertion
		}
		if(second != NULL)
		{
			if((first->data < second->data) && (first->next != NULL))	// Inserts element from list2
			{
				ListNode * temp_first = first->next;
				first->next = second;
				second->prev = first;
				second->next = temp_first;
				temp_first->prev = second;
				second = temp;
				if(second != NULL) temp = second->next;
			}
		}
		if(second != NULL)
		{
			if((first->data < second->data) && (first->next == NULL))	// Rest of list2 is greater than end of list1
			{
				first->next = second;
				second->prev = first;
				second = NULL;	// ends loop once the rest of list2 is attached
			}
		}
	}	// end large while
		
    return start;
*/


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    if(chainLength == 1)
		return start;
	int middle = chainLength/2;
	ListNode * list1 = start;
	ListNode * list2 = split(list1,middle);
	list1 = mergesort(list1, middle);
	list2 = mergesort(list2, chainLength - middle);
	start = merge(list1, list2);
    return start; 
}
