/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	currSize = 0;
}

VectorPriorityQueue::~VectorPriorityQueue() {}

int VectorPriorityQueue::size() {	
	return currSize;
}

bool VectorPriorityQueue::isEmpty() {
	if (currSize == 0) return true;
	return false;
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
	currSize++;
}

string VectorPriorityQueue::peek() {	
	return vec[minIndex()];
}

string VectorPriorityQueue::dequeueMin() {
	int temp = minIndex();
	string answer = vec[temp];
	vec.remove(temp);
	currSize--;

	return answer;
}

int VectorPriorityQueue::minIndex(){
	if (currSize == 0) error("index out of bounds");

	string minString = vec[0];
	int answer = 0;
	for(int i = 0; i < currSize; i++){
		if (vec[i] < minString){
			minString = vec[i];
			answer = i;
		}	
	}
	

	return answer;
}
