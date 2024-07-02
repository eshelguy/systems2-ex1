#include <string>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);

    g.printGraph();
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 2) << endl;
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::isBipartite(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    cout << "" << endl;

    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};

    g.loadGraph(graph2);

    g.printGraph();
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 4) << endl;
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::isBipartite(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    cout << "" << endl;

    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);

    g.printGraph();
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 4) << endl;
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::isBipartite(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    cout << "" << endl;

    std::vector<std::vector<int>> graph5 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}
    };

    g.loadGraph(graph5);

    std::cout << "Graph 5:" << std::endl;
    g.printGraph();
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    std::vector<std::vector<int>> graph6 = {
            {0, 1, 0, 0, 0},
            {1, 0, -3, 0, 0},
            {0, -3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}
    };

    g.loadGraph(graph6);

    std::cout << "Graph 6:" << std::endl;
    g.printGraph();
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    std::vector<std::vector<int>> graph7 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, -5},
            {0, 0, 0, -5, 0}
    };

    g.loadGraph(graph7);

    std::cout << "Graph 7:" << std::endl;
    g.printGraph();
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    vector<vector<int>> graph4 = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4);
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl;
    }


    std::vector<std::vector<int>> graphWithNegativeCycle = {
            {0, 1, 0, 0, 0},
            {0, 0, -1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1},
            {0, 0, 0, -5, 0}
    };

    g.loadGraph(graphWithNegativeCycle);

    g.printGraph();
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 4) << endl;
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::isBipartite(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0},
            {0, 0, -2, 0},
            {0, 0, 0, -2},
            {1, 0, 0, 0}
    };
    g.loadGraph(adjacencyMatrix);

    g.printGraph();
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 3) << endl;
    cout << Algorithms::isContainsCycle(g) << endl;
    cout << Algorithms::isBipartite(g) << endl;
    cout << Algorithms::negativeCycle(g) << endl;

    vector<vector<int>> matrix1 = {
            {0,  -1, 7,  8},
            {10, 0,  -1, 6},
            {9,  9,  0,  -1},
            {-1, 7,  8,  0}
    };

    g.loadGraph(matrix1);
    cout << Algorithms::negativeCycle(g) << endl;

    return 0;
}