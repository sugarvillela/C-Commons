/* Template function that can be a stack, a queue or an iterator.

    Copyright (C) <2018>  <David Swanson>
    https://github.com/sugarvillela

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
 * QStack is implemented on a linked list data structure.
 * For stack operations, call push, pop, top, size and empty.
 * For queue operations, call enqueue, dequeue, bottom, size and empty. 
 * For iterator operations, call reset, next, and at.
 * 'Reset' sets pointer to top and 'next' gets an item and increments pointer
 * 'At' pretends there is an index and searches to that point.
 * 'Next' and 'at' return boolean. The return value is a 'reference' parameter.
 * 'FlipCopy' returns the same list backwards.
 * 'Disp' works as long as T is printable, a string or number
 * All functions are demonstrated in the test functions in qStack.cpp
 */
#pragma once
#include <iostream>
using namespace std;

template<class T>
struct Node{
	Node(){ }
    Node(T val) {
		data = val;
		next = NULL;
		prev = NULL;
	}
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template<class T>
class QStack{
public:
	QStack();
	~QStack(void);
	/* Stack functions */
	void push(T);
	T pop();
	T top();
	int size();
	bool empty();
	/* Queue functions */
	void enqueue( T value );
	T dequeue();
	T bottom();
	/* Iterative functions */
	void reset();
	int itrDone();
	int next( T &returnMe );
	int at( int index, T &returnMe );
	/* Misc functions */
	void flipCopy(QStack &nu);
	void disp(string label);
	
private:
	int length;
	Node<T>* sTop;//stack top
	Node<T>* sBot;//stack bottom = dequeue point
	Node<T>* curr;//iterator pointer
};

template<class T>
QStack<T>::QStack(){
	sTop = sBot = curr = NULL;
	length = 0;
}
template<class T>
QStack<T>::~QStack(){
	for (Node<T>* victim=sTop; victim != NULL; victim=sTop){
		sTop = sTop->next;
		delete victim;
	}
}

template<class T>
void QStack<T>::push(T value){//stack push or queue enqueue
	Node<T>* temp = new Node<T>(value);
	temp->data = value;
	temp->next = sTop;
	if(length == 0){//bottom for dequeue
	    sBot = temp;
	}
	else{
	    sTop->prev=temp;
	}
	sTop = temp;    //top for stack pop
	length++;
}

template<class T>
T QStack<T>::pop(){//returns a value and deletes top
    if(!sTop){ return NULL; }
	T ret = sTop->data;
	Node<T>* victim = sTop;
	sTop = victim->next;
	victim->next = NULL;
	delete victim;
	length--;
	if(!length){
	    sBot=NULL;
	}
	return ret;
}
template<class T>
T QStack<T>::top(){//returns a value and leaves top
	return (sTop)? sTop->data : NULL;
}
template<class T>
int QStack<T>::size(){
	return length;
}
template<class T>
bool QStack<T>::empty(){
	return (length == 0);
}
/* Queue functions */
template<class T>
void  QStack<T>::enqueue( T value ){//same as push
    push( value );
}
template<class T>
T  QStack<T>::dequeue(){//Return a value and delete bottom
    if(!sBot){ return NULL; }
	T ret = sBot->data;
	Node<T>* victim = sBot;
	sBot = victim->prev;
	victim->prev = NULL;
	delete victim;
	length--;
	if(!length){
	    sTop=NULL;
	}
	return ret;
}
template<class T>
T  QStack<T>::bottom(){//Return a value and keep bottom
    return (sBot)? sBot->data : NULL;
}
/* Iterative functions: iterator works from stack perspective: top to bottome */
template<class T>
void QStack<T>::reset(){
    curr=sTop;
}
template<class T>
int QStack<T>::itrDone(){//increments on next() so len-1 is done
    return ( curr==NULL || curr->next==NULL );
}
template<class T>
int QStack<T>::next( T &returnMe ){//O(1) because it grabs next
    if( ( curr=curr->next )!=NULL ){
        returnMe=curr->data;
        return 1;
    }
    return 0;
}
template<class T>
int QStack<T>::at( int index, T &returnMe ){//O(n) because it traverses
    int ci=0;
	for (Node<T>* i=sTop; i!=NULL; i=i->next ){
	    if( index == ci++ ){
	        returnMe=i->data;
	        return 1;
	    }
	}
	return 0;
}
/* Misc functions */
template<class T>
void QStack<T>::disp(string label){
	cout << endl << label << endl;
	for (Node<T>* i=sTop; i!=NULL; i=i->next){
		cout << " (" << i->data << ") ";
	}
	cout << endl;
}
template<class T>
void QStack<T>::flipCopy(QStack &nu){//copies or replaces in reverse order
	while(!nu.empty())
	{
		nu.pop();
	}
	for (Node<T>* i=sTop; i!=NULL; i=i->next){
		nu.push(i->data);
	}
}

/* Test functions in qStack.cpp */
extern void test_qstack_stack();
extern void test_qstack_itr();
extern void test_qstack_at();
extern void test_qstack_queue();
