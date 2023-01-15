#ifndef _HEAP_H
#define _HEAP_H
#include"Graph.h"
#include<float.h>

class Node {
public:
	int vertex, parentVertex=-1;
	double dist = DBL_MAX;
	virtual ~Node() {

	}
};

class Heap {
public:
	virtual Node* extractMin() = 0;
	virtual Node* insert(int vertex) = 0;
	virtual void decreaseKey(Node* node, int newParent, double dist) = 0;
	virtual bool isEmpty() = 0;
	virtual void print()= 0;
	virtual ~Heap() {

	}
};
#endif