# QStack
Template function that can be a stack, a queue or an iterator
 * QStack is implemented as a linked list data structure.
 * For stack operations, call push, pop, top, size and empty.
 * For queue operations, call enqueue, dequeue, bottom, size and empty. 
 * For iterator operations, call reset, next, and at.
 > * 'Reset' sets pointer to top
 > * 'Next' gets an item and increments pointer
 > * 'At' pretends there is an index and searches to that point.
 > * 'Next' and 'at' return boolean. You get the return value by passing a return parameter.
 > * Iterator works from stack perspective: top to bottome
 * 'FlipCopy' returns the same list backwards.
 * 'Disp' works as long as T is printable, a string or number
 * All functions are demonstrated in the test functions in qStack.cpp
