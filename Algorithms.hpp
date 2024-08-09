//mail: guyes134@gmail.com

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
    std::string BFSShortestPath(const Graph &g, int start, int end);
    std::string DijkstraShortestPath(const Graph &g, int start, int end);
    std::string BellmanFordShortestPath(const Graph &g, int start, int end);
    bool BFSUtil(const Graph &g, int src, std::vector<int> &colors, std::vector<int> &setA, std::vector<int> &setB);
    bool DFSUtil(const Graph &g, int v, std::vector<bool> &visited, std::vector<int> &parent, int &cycleStart, int &cycleEnd);
    void relaxEdges(const Graph &g, std::vector<int> &dist, std::vector<int> &parent);
}
