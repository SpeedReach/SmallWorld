#ifndef _GRAPH_H
#define _GRAPH_H


#include<unordered_map>
#include<vector>
#include <GLFW/glfw3.h>
#include<iostream>
#include<cmath>

using namespace std;

class Edge;
class Vertex;
class Graph;

class Vertex {
public:
	int id;
	vector<int> edges;
	Vertex() :id(-1) {}
	Vertex(int id):id(id) {
	}
};

class Edge {
public:
	int id;
	int vertex1, vertex2;
	double length;
	Edge():id(-1),vertex1(-1),vertex2(-1),length(0) {

	}
	Edge(int id, int vertex1, int vertex2,double length):id(id),vertex1(vertex1),vertex2(vertex2),length(length) {

	}
};

class Graph {
public:
	double radius = 0.8;
	unordered_map<int, Edge> edges;
	unordered_map<int, Vertex> vertexs;
	int maxEdgeID = -1;
	int maxVertexID = -1;

	void addVertex() {
		vertexs[++maxVertexID] = Vertex(maxVertexID);
	}

	void addEdge(int vertex1, int vertex2,double length) {
		if (vertex1 == vertex2) return;
		edges[++maxEdgeID] = Edge(maxEdgeID,vertex1,vertex2,length);
		Vertex& v1 = vertexs[vertex1];
		Vertex& v2 = vertexs[vertex2];
		v1.edges.push_back(maxEdgeID);
		v2.edges.push_back(maxEdgeID);
	}

	void draw() {
		
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(0.0f);
		glBegin(GL_POINTS);
		//glColor3f(0.0f, 0.0f, 0.0f);
		for (int i = 1; i <= maxVertexID; i++)
			glVertex2d(radius * cos(i * 6.28 / maxVertexID), radius * sin(i * 6.28 / maxVertexID));
		glEnd();

		glBegin(GL_LINES);

		for (auto it = edges.begin(); it != edges.end(); ++it) {
			Edge& e =  it->second;
			glPointLocation(e.vertex1);
			//glVertex2d(radius*cos(e.vertex1*6.28/maxVertexID),radius*sin(e.vertex1 * 6.28 / maxVertexID));
			glVertex2d(radius * cos(e.vertex2 * 6.28 / maxVertexID), radius * sin(e.vertex2 * 6.28 / maxVertexID));
		}
		glEnd();
	}

	void glPointLocation(int index) {
		glVertex2d(radius * cos(index * 6.28 / maxVertexID), radius * sin(index * 6.28 / maxVertexID));
	}
	
};

#endif