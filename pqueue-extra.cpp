/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"


/*
 * This is implementation of binomial heap.
 * A binomial heap is a specific implementation of the heap data structure.
 * Binomial heaps are collections of binomial trees that are linked together where each tree is an ordered heap.
 * In a binomial heap, there are either one or zero binomial trees of order k, where k helps describe the number 
 * of element a given tree can have: 2^k. Each k (or as I represent it in my code - "degree")  also represents
 * how many children each node has.
 */
ExtraPriorityQueue::ExtraPriorityQueue() {
	/*
	 *	Constructor creates first Node, which will always exist (upon calling destructor).
	 *	I will be using head Node as "start Node", and will only call its immediate right sibling.
	 */
	currSize = 0;
	head = new Node;
	head->immedRightSibling = NULL;
	head->leftMostChild = NULL;
	head->parent = NULL;
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	deleteNode(head);
}

void ExtraPriorityQueue::deleteNode(Node* &currNode){
	// To delete Node means, we got to delete its child and its sibling recursively
	if (currNode == NULL) return;

	deleteNode(currNode->immedRightSibling);
	deleteNode(currNode->leftMostChild);
	delete currNode;
	
}

int ExtraPriorityQueue::size() {	
	return currSize;
}

bool ExtraPriorityQueue::isEmpty() {
	if (currSize == 0) return true;
	return false;
}

void ExtraPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->degree = 0;
	newNode->str = value;
	newNode->immedRightSibling = NULL;
	newNode->leftMostChild = NULL;
	newNode->parent = NULL;

	// Enqueueing new element means we need to create new Node with degree(k) = 0.
	//	Therefore, we need to merge newNode with immediate right sibling of head

	merge(newNode, head->immedRightSibling);
	currSize++;
}


void ExtraPriorityQueue::merge(Node*& newNode, Node*& toMerge){
	// We need to make sure that newNode does not have any siblings so it wont mess up chain.
	newNode->immedRightSibling = NULL;

	// We will need this temporary node to iterate over trees several times
	Node* tmp;

	/* 
	 * There are 2 cases: 1) we came here by adding new element in empty queue, which means there are no more
	 * elements, so we push it right next to head Node. 2) we came here by merging and creating Node with 
	 * highest degree(k) value. Therefore if there doesnt exist Node with greater degree, we just put given 
	 * newNode to the end of the chain.
	 */
	if (toMerge == NULL){
		for (tmp = head; tmp->immedRightSibling!=NULL; tmp = tmp->immedRightSibling){}
		tmp->immedRightSibling = newNode;
		return;
	}

	/* 
	 * If toMerge degree is bigger we freely can put newNode before toMerge Node.
	 */
	if (toMerge->degree > newNode->degree){
		newNode->immedRightSibling = toMerge;
		tmp = head;
		while (tmp->immedRightSibling != toMerge){
			tmp = tmp->immedRightSibling;
		}
		tmp->immedRightSibling = newNode;

		return;
	}

	/* 
	 * If toMerge degree is lower than newNode's one, we should find higher degree Node if it exists.
	 */
	if (toMerge->degree < newNode->degree){
		merge(newNode, toMerge->immedRightSibling);
		return;
	}
	/* 
	 * If there exist Node with same degree count than we should merge them.
	 * To merge two trees we need to take the one with less str value as root/as parent,
	 * and make the other one its child. Also we need to set childs->sibling to parent's->child.
	 * Finally we got n+1 degree Node;

head-->	 b -->a	--> NULL	|	head-->	  a --> NULL
       	 |    |				|			 /| 
		 c	  d				|			b d
							|			|
							|			c
	
	 */

	Node* parentNode = toMerge; 
	Node* childNode = newNode;
	if (newNode->str < toMerge->str){
		parentNode = newNode;
		childNode = toMerge;
	}

	tmp = head;
	while (tmp->immedRightSibling != toMerge){
			tmp = tmp->immedRightSibling;
	}
	tmp->immedRightSibling = toMerge->immedRightSibling;


	childNode->parent = parentNode;
	childNode->immedRightSibling = parentNode->leftMostChild;

	parentNode->leftMostChild = childNode;
	parentNode->degree++;
	parentNode->immedRightSibling = NULL;
	
	/*
	 * As we got new, one n+1 degree binomial tree from two n degree ones,
	 * there might be n+1 degree binomial tree, so we should merge current 
	 * tree with the one right next to it.
	 */
	
	merge(parentNode, tmp->immedRightSibling);
	
}

string ExtraPriorityQueue::peek() {
	if (currSize == 0) error("index out of bounds");
	
	// Find minimal string value through all tree roots.

	Node* tmp = head->immedRightSibling;
	string minStr = tmp->str;
	while (tmp->immedRightSibling != NULL){
		if (minStr > tmp->immedRightSibling->str) minStr = tmp->immedRightSibling->str;
		tmp = tmp->immedRightSibling;
	}
	return minStr;
}

string ExtraPriorityQueue::dequeueMin() {
	if (currSize == 0) error("index out of bounds");
	// Find minimal string value Node

	Node* tmp = head->immedRightSibling;
	Node* toDelete = tmp;
	string minStr = tmp->str;
	while (tmp->immedRightSibling != NULL){
		if (minStr > tmp->immedRightSibling->str) {
			minStr = tmp->immedRightSibling->str;
			toDelete = tmp->immedRightSibling;
		}
		tmp = tmp->immedRightSibling;
	}
	
	tmp = head;
	while (tmp ->immedRightSibling != toDelete) tmp = tmp->immedRightSibling;

	tmp->immedRightSibling = toDelete ->immedRightSibling;
	
	// Merge all subTrees of min value root Node
	tmp = toDelete->leftMostChild;
	Node* tmp2;
	for (int i =0; i < toDelete->degree; i++){
		tmp2 = tmp->immedRightSibling;
		merge(tmp, head->immedRightSibling);
		tmp = tmp2;
	}	
	delete toDelete;
	currSize--;

	return minStr;
}

