#include <GLFW/glfw3.h>
#include <climits>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include"Dijkstra.h"
#include "Graph.h"

#define vertexAmount 1000
#define radius 0.5
int x = 100;
double y = 5;
int z = 10;

float vertexDistances[vertexAmount][vertexAmount] = {0};

int main(int argc, const char* argv[]) {
    bool draw = true;
    srand(time(0));
    
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
        glfwInit();
        GLFWwindow* const window = glfwCreateWindow(1000, 1000, "GLFW test", NULL, NULL);
        glfwMakeContextCurrent(window);
        graph.draw();
        dist(g, 3, vertexAmount - 1, false);
        glfwSwapBuffers(window);
        glfwWaitEvents();
        while (true)
        {

        }
    }
    else {
        int z = 10;
        double totalDistance = 0;
        for (int i = 0; i < z; i++) {
            totalDistance += dist(g, rand() % vertexAmount, rand() % vertexAmount, false);
        }

        cout << z * 1.0 / totalDistance << endl;
    }
    
    
    
    return 0;
}