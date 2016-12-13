/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
#include <iostream>
using namespace std;

template <typename T>
T QuackFun::sum(stack<T> & s)
{
    if(s.empty())
		return 0;
	T temp = s.top();
	T total;
	s.pop();
	total = temp + sum(s);
	s.push(temp);
	return total;

				// stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
    stack<T> Dillon;
    queue<T> Michelle;	
	int counter = 1;	// for how many numbers reversed or put back into queue normally
	int end = q.size();	// iterator for while loop
	while(end != 0)
	{
		if((counter % 2) != 0)
		{
			for(int i = counter; i > 0; i--)
			{
				if(end != 0)
				{
					Michelle.push(q.front());
					q.pop();					
					q.push(Michelle.front());
					Michelle.pop();					
					end--;
				}	
			}
		}
		else
		{
			for(int i = counter; i > 0; i--)
			{
				if(end != 0)
				{
					Dillon.push(q.front());
					q.pop();				
					end--;
				}
			}
			while(!Dillon.empty())
			{
				q.push(Dillon.top());
				Dillon.pop();
			}

		}
		counter++;
	}	// end while1

}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{ 
	bool coolz;
	if(s.empty())				// base case
	{
		coolz = true;
		return coolz;
	}
	else
	{
    	T stack_item = s.top(); 		// Used to restore stack later
		s.pop();						// Will remove until bottom of stack is accessed for base case
		coolz = verifySame(s,q);		// recursive call
		s.push(stack_item);				// Will restore stack with memory at the current recursive call
		T queue_item = q.front();
		q.pop();
		q.push(queue_item);				// Iterates the queue
		if((stack_item == queue_item) && (coolz == true))	// Compares stack with queue, starting from bottom of stack
			coolz = true;
		else
			coolz = false;
    	return coolz;
	}
}

