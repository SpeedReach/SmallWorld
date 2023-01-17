#include <GLFW/glfw3.h>
#include <climits>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include"Dijkstra.h"
#include "Graph.h"

#define vertexAmount 1000
#define radius 0.5
int x = 1000;
double y = 100;
int z = 100;

double ys[] = { 5,10,50,100,200,400 };
int xs[] = {10,50,100,1000,10000,100000};

float vertexDistances[vertexAmount][vertexAmount] = {0};



void test(int edges) {
    srand(time(0));
    for (int i = 0; i < 6; i++) {
        Graph graph;
        //Generating Cycle
        {
            for (int i = 0; i < vertexAmount; i++) {
                graph.addVertex();
            }
            for (int i = 0; i < vertexAmount - 1; i++) {
                graph.addEdge(i, i + 1, 1.0);
            }
            graph.addEdge(0, vertexAmount - 1, 1.0);
        }
        for (int j = 0; j < edges; j++) {
            graph.addEdge(rand() % vertexAmount, rand() % vertexAmount, ys[i]);
        }
        double totalDistance = 0;
        for (int j = 0; j < z; j++) {
            totalDistance +=dist(graph, rand() % vertexAmount, rand() % vertexAmount, false);
        }
        totalDistance /= z;
        cout << totalDistance << endl;
    }
}

int main(int argc, const char* argv[]) {
    test(10000);
    return 0;

    bool draw = false;
    srand(time(0));
    glfwInit();
    GLFWwindow* const window = glfwCreateWindow(1000, 1000, "GLFW test", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    Graph graph;
    //Generating Cycle
    {
        for (int i = 0; i < vertexAmount; i++) {
            graph.addVertex();
        }
        for (int i = 0; i < vertexAmount-1; i++) {
            graph.addEdge(i, i + 1, 1.0);
        }
        graph.addEdge(0, vertexAmount-1, 1.0);
    }

    // adding random edges
    for (int i = 0; i < x; i++) {
        graph.addEdge(rand() % vertexAmount, rand() % vertexAmount, y);
    }
    Graph& g = graph;
    if (draw) {
        graph.draw();
        dist(g, 3, vertexAmount - 1, false);
        glfwSwapBuffers(window);
        glfwWaitEvents();
        while (true)
        {

        }
    }
    else {
        cout << "x=" << x << endl;
        cout << "y=" << y << endl;
        cout << "z=" << z << endl;
        vector<double> distances;
        double totalDist = 0;
        for (int i = 0; i < z; i++) {
            double d = dist(graph, rand() % 1000, rand() % 1000, false);
            distances.push_back(d);
            totalDist += d;
        }
        double averageD = totalDist / z;
        cout << "average: " << averageD << endl;
        double varience = 0;
        for (auto it = distances.begin(); it != distances.end(); it++) {
            varience += pow((*it) - averageD, 2);
        }
        varience /= z;
        double devieation = sqrt(varience);
        cout << "devieation: " << devieation << endl;
        double margin = (1.654 * devieation / sqrt(z));
        cout << "margin: " << margin <<endl;
        cout << margin / averageD * 100 << "%" << endl;
    }
    
    
    
    return 0;
}