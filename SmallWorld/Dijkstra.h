#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include"Graph.h"
#include<unordered_map>
#include<ctime>
#include"Heap.h"
#include"BinaryHeap.h"
#include"BinomialHeap.h"

Heap* createHeap() {
	return new BinaryHeap();
	//return new FibonacciHeap();
}


double dist(Graph& graph, int start, int end,bool draw) {

	clock_t startTime = clock();
	Heap* heap = createHeap();
	Vertex& startV = graph.vertexs[start];
	unordered_map<int, Node*> vertexNodeMap;
	
	// add nodes into the heap 
	for (auto vertex = graph.vertexs.begin(); vertex != graph.vertexs.end(); vertex++) {
		Node* node = heap->insert(vertex->first);
		vertexNodeMap[vertex->first] = node;
		if (vertex->first == start) {
			heap->decreaseKey(node, -1, 0.0);
		}
	}
	heap->print();
	//keep extracting min until the heap is empty
	Node* extractedNode;
	while (!heap->isEmpty())
	{
		extractedNode = heap->extractMin();
		cout << "extracted " << extractedNode->dist <<" " << extractedNode->vertex << endl;
		Vertex& vertex = graph.vertexs[extractedNode->vertex];
		for (auto edgeID = vertex.edges.begin(); edgeID != vertex.edges.end(); edgeID++) {
			Edge& edge = graph.edges[*edgeID];
			int otherVertexID;
			if (edge.vertex1 != vertex.id) otherVertexID = edge.vertex1;
			else otherVertexID = edge.vertex2;
			double dist = edge.length + extractedNode->dist;
			//cout << "other vertex is " << otherVertexID << endl;
			Node* otherVertexNode = vertexNodeMap[otherVertexID];
			if (otherVertexNode->dist > dist) {
				heap->decreaseKey(otherVertexNode, vertex.id, dist);
			}
		}
	}
	clock_t endTime = clock();

	cout << "took " << endTime - startTime << "ms" <<endl;

	if (draw) {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glLineWidth(1.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		for (auto entry = vertexNodeMap.begin(); entry != vertexNodeMap.end(); entry++) {
			int a = entry->second->parentVertex;
			int b = entry->second->vertex;
			if (a != -1 && b != -1) {
				graph.glPointLocation(a);
				graph.glPointLocation(b);
			}
		}
		glEnd();
	}
	return vertexNodeMap[end]->dist;
}

#endif