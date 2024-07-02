#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Graph constructor and properties") {
    SUBCASE("directed graph") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
        };
        Graph g(matrix, false, false, false, 3, 3);
        CHECK(g.isDirectedGraph() == false);
        CHECK(g.getVertexNum() == 3);
        CHECK(g.getEdgesNum() == 3);
        CHECK(g.isSquare(matrix) == true);
        CHECK(g.hasNegativeWeights() == false);
        CHECK(g.isDirectedGraph() == false);
    }

    SUBCASE("undirected graph") {
        std::vector<std::vector<int>> directedMatrix = {
                {0, 1, 0},
                {0, 0, 1},
                {1, 0, 0}
        };
        Graph g2(directedMatrix, true, false, false, 3, 3);
        CHECK(g2.isDirectedGraph() == true);
        CHECK(g2.getVertexNum() == 3);
        CHECK(g2.getEdgesNum() == 3);
        CHECK(g2.isSquare(directedMatrix) == true);
        CHECK(g2.hasNegativeWeights() == false);
        CHECK(g2.isDirectedGraph() == true);
    }
}

// Test loadGraph method
TEST_CASE("Graph loadGraph method") {
    SUBCASE("directed graph") {
        Graph g;
        vector<std::vector<int>> matrix = {
                {0, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {0, 0, 1, 0}
        };
        g.loadGraph(matrix);
        CHECK(g.getVertexNum() == 4);
        CHECK(g.getEdgesNum() == 3);
        CHECK(g.isDirectedGraph() == false);
        CHECK(g.isSquare(matrix) == true);
        CHECK(g.getIsWeighted() == false);
        CHECK(g.hasNegativeWeights() == false);
    }

    SUBCASE("undirected graph"){
        Graph g3;
        std::vector<std::vector<int>> largeMatrix = {
                {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                {1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                {1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
                {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}
        };

        g3.loadGraph(largeMatrix);
        CHECK(g3.isDirectedGraph() == false);
        CHECK(g3.isSquare(largeMatrix) == true);
        CHECK(g3.getEdgesNum() == 13);
        CHECK(g3.hasNegativeWeights() == false);

    }
}

// Test the printGraph method
TEST_CASE("Graph printGraph method") {
    std::vector<std::vector<int>> matrix = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    Graph g(matrix, false, false, false, 3, 3);
    g.printGraph();
    // Manual verification required for print output
}

// Test the isConnected method
TEST_CASE("isConnected method") {
    std::vector<std::vector<int>> matrix = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    Graph g(matrix, false, false, false, 3, 3);
    CHECK(Algorithms::isConnected(g) == 1);

    std::vector<std::vector<int>> matrix2 = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}
    };
    Graph g2(matrix2, false, false, false, 3, 2);
    CHECK(Algorithms::isConnected(g2) == 0);

    // Test 1: Empty graph
    vector<vector<int>> emptyGraph = {};
    g.loadGraph(emptyGraph);
}


// Test the shortestPath method
TEST_CASE("shortestPath method") {
    SUBCASE("directed graph") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0, 0, 0},
                {1, 0, 1, 0, 0, 0},
                {0, 1, 0, 1, 0, 0},
                {0, 0, 1, 0, 1, 0},
                {0, 0, 0, 1, 0, 1},
                {0, 0, 0, 0, 1, 0}
        };
        Graph g(matrix, false, false, false, 6, 5);
        CHECK(Algorithms::shortestPath(g, 0, 5) == "0->1->2->3->4->5");
    }

    SUBCASE("unweighted undirected graph") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                {1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                {1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
                {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}
        };
        Graph g(matrix, false, false, false, 10, 14);
        CHECK(Algorithms::shortestPath(g, 0, 9) == "0->1->2->3->9");
    }

    SUBCASE("weighted undirected graph") {
        std::vector<std::vector<int>> matrix = {
                {0, 2, 0, 0, 0, 0, 1, 0, 0, 0},
                {2, 0, 3, 0, 0, 0, 0, 1, 0, 0},
                {0, 3, 0, 1, 0, 0, 0, 0, 2, 0},
                {0, 0, 1, 0, 4, 0, 0, 0, 0, 1},
                {0, 0, 0, 4, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 2, 0, 0, 0},
                {1, 0, 0, 0, 0, 2, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 0, 1, 0, 3, 0},
                {0, 0, 2, 0, 0, 0, 0, 3, 0, 1},
                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}
        };
        Graph g(matrix, false, false, true, 10, 14);
        CHECK(Algorithms::shortestPath(g, 0, 9) == "0->6->7->8->9");
    }
}


// Test the isContainsCycle method
TEST_CASE("isContainsCycle method") {
    SUBCASE("matrix without cycle") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {0, 0, 1, 0}
        };
        Graph g(matrix, false, false, false, 4, 4);
        CHECK(Algorithms::isContainsCycle(g) == "0");

        std::vector<std::vector<int>> largeMatrix = {
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
        };
        Graph g3(largeMatrix, false, false, false, 10, 9);
        CHECK(Algorithms::isContainsCycle(g3) == "0");
    }

    SUBCASE("matrix with cycle") {
        std::vector<std::vector<int>> matrix2 = {
                {0, 1, 0, 1},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {1, 0, 1, 0}
        };
        Graph g2(matrix2, false, false, false, 4, 5);
        CHECK(Algorithms::isContainsCycle(g2) == "The cycle is: 3->0->1->2->3");

        std::vector<std::vector<int>> largeMatrixWithCycle = {
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
        };
        Graph g4(largeMatrixWithCycle, false, false, false, 10, 10);
        CHECK(Algorithms::isContainsCycle(g4) != "0");
    }
}



// Test the isBipartite method
TEST_CASE("isBipartite method") {
    SUBCASE("is bipartite") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {0, 0, 1, 0}
        };
        Graph g(matrix, false, false, false, 4, 4);
        CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
    }

    SUBCASE("is'nt bipartite") {
        std::vector<std::vector<int>> matrix2 = {
                {0, 1, 1, 0},
                {1, 0, 1, 0},
                {1, 1, 0, 1},
                {0, 0, 1, 0}
        };
        Graph g2(matrix2, false, false, false, 4, 5);
        CHECK(Algorithms::isBipartite(g2) == "0");

        std::vector<std::vector<int>> largeMatrix = {
                {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                {1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
                {1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
                {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}
        };
        Graph g3(largeMatrix, false, false, false, 10, 14);
        CHECK(Algorithms::isBipartite(g3) == "0");
    }
}

// Test the negativeCycle method
TEST_CASE("negativeCycle method") {
    SUBCASE("graph without negative cycle") {
        std::vector<std::vector<int>> matrix = {
                {0,  -1, 0,  0},
                {-1, 0,  -1, 0},
                {0,  -1, 0,  -1},
                {0,  0,  -1, 0}
        };
        Graph g(matrix, true, true, true, 4, 4);
        CHECK(Algorithms::negativeCycle(g) == "0");

        std::vector<std::vector<int>> matrix2 = {
                {0, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {0, 0, 1, 0}
        };
        g.loadGraph(matrix2);
        CHECK(Algorithms::negativeCycle(g) == "0");

        vector<vector<int>> matrix3 = {
                {0,    -1,   1000},
                {-1,   0,    1000},
                {1000, 1000, 0}
        };
        g.loadGraph(matrix3);
        CHECK(Algorithms::negativeCycle(g) == "0");

        vector<vector<int>> matrix4 = {
                {0, 1, 0,  8},
                {1, 0, 8,  8},
                {8, 3, 0,  -1},
                {0, 8, -1, 0}
        };
        g.loadGraph(matrix4);
        CHECK(Algorithms::negativeCycle(g) == "0");
    }

    SUBCASE("graph with negative cycle") {
        Graph g;
        vector<vector<int>> matrix1 = {
                {0,  -1, 7,  8},
                {10, 0,  -1, 6},
                {9,  9,  0,  -1},
                {-1, 7,  8,  0}
        };
        g.loadGraph(matrix1);
        CHECK(Algorithms::negativeCycle(g) == "The negative weight cycle is: 1->2->3->0->1");
    }
}