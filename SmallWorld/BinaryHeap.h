#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H

#include<iostream>
#include<climits>
#include"Heap.h"
using namespace std;



class BinaryHeapNode :public Node {
public:
	int position;

	BinaryHeapNode(int vertex, int position) {
		this->vertex = vertex;
		this->position = position;
	}

};
void swap(BinaryHeapNode** node1,BinaryHeapNode** node2);
class BinaryHeap : public Heap {
public:
	vector<BinaryHeapNode*> heap;

	int size = 0;

	virtual Node* extractMin();
	virtual Node* insert(int vertex);
	virtual void decreaseKey(Node* node, int newParent, double dist);
	
	virtual bool isEmpty() {
		return size == 0;
	}

	void heapify(int position);

	int parent(int i) { return (i - 1) / 2; }

	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }

	void print() {
		for (auto it = heap.begin(); it != heap.end(); it++) {
			cout << (*it)->dist <<","<<(*it)->position << " ";
		}
		cout << endl;
	}
};

Node* BinaryHeap::extractMin() {
	if (isEmpty()) return nullptr;

	Node* root = heap[0];
	if (size == 1)
	{
		size--;
		return root;
	}
	heap[0] = heap[size - 1];
	size--;
	heapify(0);
	return root;
}

Node* BinaryHeap::insert(int vertex)
{
	
	int i =size;
	size++;
	heap.push_back(new BinaryHeapNode(vertex, i));

	// Fix the min heap property if it is violated
	while (i != 0 && heap[parent(i)]->dist > heap[i]->dist)
	{
		swap(&heap[i], &heap[parent(i)]);
		i = parent(i);
	}
	return heap[i];
}

void BinaryHeap::decreaseKey(Node* node, int newParent, double dist)
{
	BinaryHeapNode* binaryNode = dynamic_cast<BinaryHeapNode*>(node);
	if (binaryNode == nullptr) return;
	binaryNode->dist = dist;
	binaryNode->parentVertex = newParent;
	int i = binaryNode->position;
	(*heap[i]).dist = dist;
	while (i != 0 && (*heap[parent(i)]).dist > (*heap[i]).dist)
	{
		swap(&heap[i], &heap[parent(i)]);
		i = parent(i);
	}
}

void BinaryHeap::heapify(int i ) {
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < size && heap[l]->dist < heap[i]->dist)
		smallest = l;
	if (r < size && heap[r]->dist < heap[smallest]->dist)
		smallest = r;
	if (smallest != i)
	{
		swap(&heap[i], &heap[smallest]);
		heapify(smallest);
	}
}

void swap(BinaryHeapNode** node1, BinaryHeapNode** node2) {
	BinaryHeapNode* tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;
	int tmpIndex = (*node1)->position;
	(*node1)->position = (*node2)->position;
	(*node2)->position = tmpIndex;
}

#endif