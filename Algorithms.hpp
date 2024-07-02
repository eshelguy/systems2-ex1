//guyes134@gmail.com


#pragma once
#include "Graph.hpp"
#include <string>

namespace Algorithms{
    int isConnected(const Graph &g);
    std::string shortestPath(const Graph &g, int start, int end);
    std::string isContainsCycle(const Graph &g);
    std::string isBipartite(const Graph &g);
    std::string negativeCycle(const Graph &g);
    void DFS(Graph g, int v, std::vector<bool> &visited);
}
