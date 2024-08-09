//mail: guyes134@gmail.com

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
    Graph g;
    SUBCASE("Empty graph") {
        vector<vector<int>> emptyGraph = {};
        g.loadGraph(emptyGraph);
        CHECK(Algorithms::isConnected(g) == 0);
    }
    SUBCASE("Single vertex graph") {
        vector<vector<int>> singleVertexGraph = {{0}};
        g.loadGraph(singleVertexGraph);
        CHECK(Algorithms::isConnected(g) == 1);
    }
    SUBCASE("Disconnected graph") {
        vector<vector<int>> disconnectedGraph = {
                {0, 1, 0, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 1},
                {0, 0, 1, 0}
        };
        g.loadGraph(disconnectedGraph);
        CHECK(Algorithms::isConnected(g) == 0);
    }
    SUBCASE("directed graph") {
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

        g.loadGraph(largeMatrix);
        CHECK(g.isDirectedGraph() == false);
        CHECK(g.isSquare(largeMatrix) == true);
        CHECK(g.getEdgesNum() == 13);
        CHECK(g.hasNegativeWeights() == false);

    }
}

// Test the printGraph method
TEST_CASE("Graph printGraph method") {
    vector<vector<int>> matrix = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    Graph g(matrix, false, false, false, 3, 3);
    g.printGraph();
}

// Test the shortestPath method
TEST_CASE("shortestPath method") {
    Graph g;
    SUBCASE("directed graph") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0, 0, 0},
                {1, 0, 1, 0, 0, 0},
                {0, 1, 0, 1, 0, 0},
                {0, 0, 1, 0, 1, 0},
                {0, 0, 0, 1, 0, 1},
                {0, 0, 0, 0, 1, 0}
        };
        g.loadGraph(matrix);
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
        g.loadGraph(matrix);
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
        g.loadGraph(matrix);
        CHECK(Algorithms::shortestPath(g, 0, 9) == "0->6->7->8->9");
    }
    SUBCASE("Directed graph with no path") {
        vector<vector<int>> directedGraphNoPath = {
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        };
        g.loadGraph(directedGraphNoPath);
        CHECK(Algorithms::shortestPath(g, 0, 3) == "-1");
    }
    SUBCASE("Single node graph") {
        vector<vector<int>> singleNodeGraph = {
                {0}
        };
        g.loadGraph(singleNodeGraph);
        CHECK(Algorithms::shortestPath(g, 0, 0) == "0");
    }
    SUBCASE("Graph with multiple shortest paths") {
        vector<vector<int>> multiplePathsGraph = {
                {0, 1, 1, 0},
                {1, 0, 0, 1},
                {1, 0, 0, 1},
                {0, 1, 1, 0}
        };
        g.loadGraph(multiplePathsGraph);
        string result = Algorithms::shortestPath(g, 0, 3);
        bool ans = (result == "0->1->3" || "0->2->3");
        CHECK(ans);
    }
    SUBCASE("Very short path") {
        vector<vector<int>> largeGraph = {
                {0, 1, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 1, 0},
                {0, 1, 0, 1, 0, 0, 1, 0, 0},
                {0, 0, 1, 0, 1, 1, 0, 0, 0},
                {0, 0, 0, 1, 0, 1, 0, 0, 0},
                {0, 0, 0, 1, 1, 0, 1, 0, 0},
                {0, 0, 1, 0, 0, 1, 0, 1, 0},
                {0, 1, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 1, 0}
        };
        g.loadGraph(largeGraph);
        CHECK(Algorithms::shortestPath(g, 0, 8) == "0->8");
    }
}


// Test the isContainsCycle method
TEST_CASE("isContainsCycle method") {
    Graph g;
    SUBCASE("Empty graph") {
        vector<vector<int>> emptyGraph = {};
        g.loadGraph(emptyGraph);
        CHECK(Algorithms::isContainsCycle(g) == "0");
    }
    SUBCASE("Single vertex graph"){
        vector<vector<int>> singleVertexGraph = {{0}};
        g.loadGraph(singleVertexGraph);
        CHECK(Algorithms::isContainsCycle(g) == "0");
    }
    SUBCASE("matrix without cycle") {
        std::vector<std::vector<int>> matrix = {
                {0, 1, 0, 0},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {0, 0, 1, 0}
        };
        g.loadGraph(matrix);
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
        g.loadGraph(largeMatrix);
        CHECK(Algorithms::isContainsCycle(g) == "0");
    }

    SUBCASE("matrix with cycle") {
        std::vector<std::vector<int>> matrix2 = {
                {0, 1, 0, 1},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {1, 0, 1, 0}
        };
        g.loadGraph(matrix2);
        CHECK(Algorithms::isContainsCycle(g) == "The cycle is: 3->0->1->2->3");

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
        vector<vector<int>> matrix = {
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

TEST_CASE("Arithmetic operators"){
    Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    Graph g3 = g1 + g2;
    Graph g4 = g3.operator+();
    Graph g5;
    g5.loadGraph(g1.getAdjacencyMatrix());
    g5 += g2;
    vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}
    };

    Graph g6 = g3 - g2;
    Graph g7;
    g7.loadGraph(g5.getAdjacencyMatrix());
    g7 -= g1;
    Graph g8 = g3.operator-();

    vector<vector<int>> expectedMinusGraph{
            {0, -2, -1},
            {-2, 0, -3},
            {-1, -3, 0}
    };

    CHECK(g3.getAdjacencyMatrix() == expectedGraph);
    CHECK(g4.getAdjacencyMatrix() == expectedGraph);
    CHECK(g5.getAdjacencyMatrix() == expectedGraph);
    CHECK(g6.getAdjacencyMatrix() == g1.getAdjacencyMatrix());
    CHECK(g7.getAdjacencyMatrix() == g2.getAdjacencyMatrix());
    CHECK(g8.getAdjacencyMatrix() == expectedMinusGraph);
}

TEST_CASE("Compare operators"){
    Graph g1, g1_2, g2, g3, g4, g5, g6, g7;
    vector<vector<int>> graph1 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}
    };
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g2.loadGraph(graph2);

    vector<vector<int>> graph1_2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}
    };
    g1_2.loadGraph(graph1_2);

    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 2},
            {1, 0, 0, 1, 0}
    };
    g3.loadGraph(graph3);

    vector<vector<int>> graph4 = {
            {0, 1, 0},
            {1, 0, 2},
            {0, 1, 0}
    };
    g4.loadGraph(graph4);

    vector<vector<int>> graph5 = {
            {-1, -8, 0, -3, 0},
            {0, 2, 3, 4, 5},
            {1, -10, 4, 2, 1},
            {1, 1, 1, 1, 1},
            {-8, -1, -2, -3, -4}
    };

    vector<vector<int>> graph6 = {
            {-1, -8, 0, 0},
            {0, 2, 3, 5},
            {1, -10, 4, 1},
            {-8, -1, -2, -4}
    };

    vector<vector<int>> graph7 = {
            {-1, 0, 0},
            {1, 4, 1},
            {-8, -2, -4}
    };

    g5.loadGraph(graph5);
    g6.loadGraph(graph6);
    g7.loadGraph(graph7);

    CHECK((g1 > g2) == true);
    CHECK((g1 < g2) == false);
    CHECK((g1 == g1_2) == true);
    CHECK((g1 != g3) == true);
    CHECK((g1 == g3) == false);
    CHECK((g1 <= g1_2) == true);
    CHECK((g1 >= g1_2) == true);
    CHECK((g1 > g4) == true);
    CHECK((g4 < g3) == true);
    CHECK((g5 < g6) == false);
    CHECK((g5 > g6) == true);
    CHECK((g5 > g7) == true);
    CHECK((g6 > g7) == true);
}

TEST_CASE("Increment and Decrement Operators"){
    Graph g;
    SUBCASE("Prefix Increment (normal case)") {
        vector<vector<int>> matrix = {
                {0, 1, 2},
                {1, 0, 3},
                {2, 3, 0}
        };
        g.loadGraph(matrix);

        ++g;

        vector<vector<int>> expectedMatrix = {
                {0, 2, 3},
                {2, 0, 4},
                {3, 4, 0}
        };

        CHECK(g.getAdjacencyMatrix() == expectedMatrix);
    }

    SUBCASE("Postfix Increment (normal case)") {
        vector<vector<int>> matrix = {
                {0, 1, 2},
                {1, 0, 3},
                {2, 3, 0}
        };
        g.loadGraph(matrix);
        Graph originalGraph = g++;

        vector<vector<int>> expectedMatrix = {
                {0, 2, 3},
                {2, 0, 4},
                {3, 4, 0}
        };

        // Check if the graph has been incremented
        CHECK(g.getAdjacencyMatrix() == expectedMatrix);

        // Check if the originalGraph is unchanged
        CHECK(originalGraph.getAdjacencyMatrix() == matrix);
    }

    SUBCASE("Postfix Decrement (normal case)") {
        std::vector<std::vector<int>> matrix = {
                {0, 2, 3},
                {2, 0, 4},
                {3, 4, 0}
        };
        g.loadGraph(matrix);

        Graph originalGraph = g--;  // Perform postfix decrement

        std::vector<std::vector<int>> expectedMatrix = {
                {0, 1, 2},
                {1, 0, 3},
                {2, 3, 0}
        };

        // Check if the graph has been decremented
        CHECK(g.getAdjacencyMatrix() == expectedMatrix);

        // Check if the originalGraph is unchanged
        CHECK(originalGraph.getAdjacencyMatrix() == matrix);
    }

    SUBCASE("Increment an empty graph (edge case)") {
        Graph g1;
        ++g1;
        CHECK(g.getAdjacencyMatrix().empty());

        g1++;
        CHECK(g.getAdjacencyMatrix().empty());
    }

    SUBCASE("Decrement an empty graph (edge case)") {
        Graph g1;

        --g1;
        CHECK(g.getAdjacencyMatrix().empty());

        g1--;
        CHECK(g.getAdjacencyMatrix().empty());
    }

    SUBCASE("Increment a graph with zero weights (edge case)") {
        vector<vector<int>> matrix = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };
        g.loadGraph(matrix);

        ++g;

        CHECK(g.getAdjacencyMatrix() == matrix);  // Should be unchanged

        Graph originalGraph = g++;

        CHECK(g.getAdjacencyMatrix() == matrix);  // Should still be unchanged
        CHECK(originalGraph.getAdjacencyMatrix() == matrix);  // Original should also be unchanged
    }

    SUBCASE("Decrement a graph with minimum non-zero weights (edge case)") {
        vector<vector<int>> matrix = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}
        };
        g.loadGraph(matrix);

        --g;

        vector<vector<int>> expectedMatrix = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };

        CHECK(g.getAdjacencyMatrix() == expectedMatrix);

        Graph originalGraph = g--;

        CHECK(g.getAdjacencyMatrix() == expectedMatrix);  // Should stay at zero
        CHECK(originalGraph.getAdjacencyMatrix() == expectedMatrix);  // Should also be zeros
    }

    SUBCASE("Increment a graph with mixed weights (edge case)") {
        vector<vector<int>> matrix = {
                {0, 1, -2},
                {1, 0, 3},
                {-2, 3, 0}
        };
        g.loadGraph(matrix);

        ++g;

        vector<vector<int>> expectedMatrix = {
                {0, 2, -1},
                {2, 0, 4},
                {-1, 4, 0}
        };

        CHECK(g.getAdjacencyMatrix() == expectedMatrix);
    }

    SUBCASE("Decrement a graph with mixed weights (edge case)") {
        vector<vector<int>> matrix = {
                {0, 1, -2},
                {1, 0, 3},
                {-2, 3, 0}
        };
        g.loadGraph(matrix);

        --g;
        vector<vector<int>> expectedMatrix = {
                {0, 0, -3},
                {0, 0, 2},
                {-3, 2, 0}
        };

        CHECK(g.getAdjacencyMatrix() == expectedMatrix);
    }
}
TEST_CASE("Multiplication operators") {
    Graph g1, g2, g3, g3_1, g3_2, g4;
    vector<vector<int>> graph1 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}
    };
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
    };
    g2.loadGraph(graph2);

    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 2},
            {1, 0, 0, 1, 0}
    };
    g3.loadGraph(graph3);

    vector<vector<int>> graph3_1 = {
            {0, 2, 0, 0, 2},
            {2, 0, 2, 0, 0},
            {0, 2, 0, 2, 0},
            {0, 0, 2, 0, 2},
            {2, 0, 0, 2, 0}
    };
    g3_1.loadGraph(graph3_1);
    g1 * 2;

    vector<vector<int>> graph3_2 = {
            {4, 0, 2, 2, 0},
            {0, 4, 0, 2, 2},
            {2, 0, 4, 0, 2},
            {4, 2, 0, 6, 0},
            {0, 2, 2, 0, 4}
    };
    g3_2.loadGraph(graph3_2);
    g4 = g3 * g3_1;

    CHECK((g1 == g3_1) == true);
    CHECK((g4 == g3_2) == true);
    SUBCASE("output"){
        Graph g;
        vector<vector<int>> matrix = {
                {0, 1, 2},
                {1, 0, 3},
                {2, 3, 0}
        };
        g.loadGraph(matrix);

        ostringstream oss;
        oss << g;
        std::string expectedOutput =
                "0, 1, 2\n"
                "1, 0, 3\n"
                "2, 3, 0\n";
        CHECK(oss.str() == expectedOutput);
    }
}


