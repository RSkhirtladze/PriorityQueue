/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	currSize = 0;

	head = new Node;
	tail = new Node;

	head -> next = tail;
	tail -> next = NULL;

}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node* ptr = head;
	while (ptr != NULL) {
		Node* tmp = ptr;
		ptr = ptr -> next;
		delete tmp;
	}
	
}

int LinkedListPriorityQueue::size() {
	return currSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	if (currSize == 0) return true;
	return false;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* tmp = head;
	while(tmp->next != tail){

		if (value < tmp->next->str) break;
		tmp = tmp->next;

	}

	Node* newNode = new Node;
	newNode->str = value;
	newNode->next = tmp->next;
	tmp->next = newNode;

	currSize++;
}

string LinkedListPriorityQueue::peek() {
	if (currSize == 0) error("index out of bounds");
	return head -> next -> str;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (currSize == 0) error("index out of bounds");

	string answer = head -> next -> str;
	
	Node* tmp = head -> next;
	head->next = head->next->next;
	delete tmp;
	currSize--;

	return answer;
}

