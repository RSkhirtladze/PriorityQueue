/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	currSize = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {}

int HeapPriorityQueue::size() {
	return currSize;
}

bool HeapPriorityQueue::isEmpty() {
	if(currSize == 0) return true;	
	return false;
}

void HeapPriorityQueue::enqueue(string value) {
	tree.add(value);
	currSize++;
	int currIndex = currSize;

	while (currIndex != 1 && tree[currIndex/2-1] > tree[currIndex-1]){
		string temp = tree[currIndex/2-1];
		tree[currIndex/2-1] = tree[currIndex-1];
		tree[currIndex-1] = temp;
		currIndex = currIndex/2;
	}
}

string HeapPriorityQueue::peek() {	
	if (currSize == 0) error("index out of bounds");
	return tree[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (currSize == 0) error("index out of bounds");

	string answer = tree[0];
	tree[0] = tree[--currSize];
	tree.remove(currSize);

	int currIndex = 1;
	while (currIndex * 2 + 1 <= currSize){
		int toSwap;
		if (tree[currIndex * 2] > tree[currIndex * 2 - 1]) toSwap = currIndex * 2 - 1;
		else toSwap = currIndex * 2;
		
		if (tree[currIndex - 1] < tree[toSwap])break;

		string temp = tree[toSwap];
		tree[toSwap] = tree[currIndex - 1];
		tree[currIndex - 1] = temp;

		currIndex = toSwap + 1;
	}

	if (currIndex * 2 == currSize && tree[currIndex - 1] > tree[currIndex * 2 - 1]){
		string temp = tree[currIndex * 2 - 1];
		tree[currIndex * 2 - 1] = tree[currIndex - 1];
		tree[currIndex - 1] = temp;
	}
	return answer;
}

