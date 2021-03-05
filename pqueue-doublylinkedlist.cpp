/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	currSize = 0;
	head = new Node;
	tail = new Node;
	
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = tail;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* ptr = head;
	while (ptr != NULL) {
		Node* tmp = ptr;
		ptr = ptr -> next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {	
	return currSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {	
	if (currSize == 0) return true;
	return false;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->str = value;

	newNode->prev = head;
	newNode->next = head->next;
	newNode->next->prev = newNode;
	head->next = newNode;


	currSize++;
}

string DoublyLinkedListPriorityQueue::peek() {
	Node* temp = new Node;
	findMinStrNode(temp);
	return temp->str;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	Node* temp = new Node;
	findMinStrNode(temp);
	string answer = temp->str;
	
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	delete temp;
	currSize--;

	return answer;
}

void DoublyLinkedListPriorityQueue::findMinStrNode(Node* &minStrNode){
	if (currSize == 0) error("index out of bounds");

	minStrNode = head ->next;
	Node* temp = head ->next;
	while (temp != tail){
		if (minStrNode->str > temp->str) minStrNode = temp;
		temp = temp -> next;
	}
}
