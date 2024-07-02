//guyes134@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

int Algorithms::isConnected(const Graph &g) {
   if (g.getVertexNum() == 0){
       return 0;
   }
   std::vector<bool> visited(g.getVertexNum(), false);
   Algorithms::DFS(g, 0, visited);
   for (bool v : visited){
       if (!v){
           return 0;
       }
   }
   return 1;
}

void Algorithms::DFS(Graph g, int v, std::vector<bool> &visited) {
    visited[v] = true;
    for (int i = 0; i < g.getVertexNum(); ++i) {
        if (g.getAdjacencyMatrix()[v][i] != 0 && !visited[i]) {
            Algorithms::DFS(g, i, visited);
        }
    }
}


std::string BFSShortestPath(const Graph &g, int start, int end) {
    std::stringstream ss;
    if (start == end) {
        ss << start; // Same vertex, just print the vertex
        return ss.str();
    }

    int vertexNum = g.getVertexNum();
    if (vertexNum == 0) {
        return "-1";
    }

    std::vector<bool> visited(vertexNum, false);
    std::vector<int> parent(vertexNum, -1); // Parent of each vertex in the shortest path
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    bool found = false;
    while (!q.empty() && !found) {
        int currVertex = q.front();
        q.pop();

        // Visit neighbors
        for (int i = 0; i < vertexNum; ++i) {
            if (g.getAdjacencyMatrix()[currVertex][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                parent[i] = currVertex; // Set parent of i to currVertex
                if (i == end) {
                    found = true; // Found the end vertex
                    break;
                }
            }
        }
    }

    if (!found) {
        return "-1";
    }

    // Reconstruct and print the path
    std::stack<int> path;
    int currVertex = end;
    while (currVertex != -1) {
        path.push(currVertex);
        currVertex = parent[currVertex];
    }

    // Print the path
    while (!path.empty()) {
        ss << path.top();
        path.pop();
        if (!path.empty()) {
            ss << "->";
        }
    }
    return ss.str();
}

std::string DijkstraShortestPath(const Graph &g, int start, int end) {
    std::stringstream ss;
    if (start == end) {
        ss << start; // Same vertex, just print the vertex
        return ss.str();
    }

    int vertexNum = g.getVertexNum();
    if (vertexNum == 0) {
        return "-1";
    }

    std::vector<int> dist(vertexNum, std::numeric_limits<int>::max());
    std::vector<int> parent(vertexNum, -1); // Parent of each vertex in the shortest path
    dist[start] = 0;

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int currVertex = pq.top().second;
        pq.pop();

        if (currDist > dist[currVertex]) continue;

        for (int i = 0; i < vertexNum; ++i) {
            if (g.getAdjacencyMatrix()[currVertex][i] != 0) {
                int weight = g.getAdjacencyMatrix()[currVertex][i];
                if (dist[currVertex] + weight < dist[i]) {
                    dist[i] = dist[currVertex] + weight;
                    pq.push({dist[i], i});
                    parent[i] = currVertex;
                }
            }
        }
    }

    if (dist[end] == std::numeric_limits<int>::max()) {
        return "-1";
    }

    // Reconstruct and print the path
    std::stack<int> path;
    int currVertex = end;
    while (currVertex != -1) {
        path.push(currVertex);
        currVertex = parent[currVertex];
    }

    // Print the path
    while (!path.empty()) {
        ss << path.top();
        path.pop();
        if (!path.empty()) {
            ss << "->";
        }
    }
    return ss.str();
}

std::string Algorithms::shortestPath(const Graph &g, int start, int end) {
    if (g.getIsWeighted()) {
        return DijkstraShortestPath(g, start, end);
    } else {
        return BFSShortestPath(g, start, end);
    }
}

bool DFSUtil(const Graph &g, int v, std::vector<bool> &visited, std::vector<int> &parent, int &cycleStart, int &cycleEnd) {
    visited[v] = true;

    for (int i = 0; i < g.getVertexNum(); ++i) {
        if (g.getAdjacencyMatrix()[v][i] != 0) { // Check for an edge
            if (!visited[i]) {
                parent[i] = v;
                if (DFSUtil(g, i, visited, parent, cycleStart, cycleEnd))
                    return true;
            } else if (i != parent[v]) { // A back edge found (and not the parent)
                cycleStart = i;
                cycleEnd = v;
                return true;
            }
        }
    }
    return false;
}

std::string Algorithms::isContainsCycle(const Graph &g) {
    std::vector<bool> visited(g.getVertexNum(), false);
    std::vector<int> parent(g.getVertexNum(), -1);
    int cycleStart = -1, cycleEnd = -1;

    for (int i = 0; i < g.getVertexNum(); i++) {
        if (!visited[i] && DFSUtil(g, i, visited, parent, cycleStart, cycleEnd))
            break;
    }

    if (cycleStart == -1) {
        return "0";
    } else {
        std::vector<int> cycle;
        for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycleStart);
        cycle.push_back(cycleEnd);  // Add the starting point to complete the cycle

        // Reverse the cycle
        std::reverse(cycle.begin(), cycle.end());

        // Print the reversed cycle
        std::ostringstream cycleStream;
        cycleStream << "The cycle is: ";
        for (size_t i = 0; i < cycle.size(); ++i) {
            cycleStream << cycle[i];
            if (i < cycle.size() - 1) {
                cycleStream << "->";
            }
        }

        return cycleStream.str();
    }
}



bool BFSUtil(const Graph &g, int src, std::vector<int> &colors, std::vector<int> &setA, std::vector<int> &setB) {
    std::queue<int> q;
    q.push(src);
    colors[src] = 1; // Start coloring the source vertex with color 1
    setA.push_back(src); // Add to set A

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < g.getVertexNum(); ++v) {
            if (g.getAdjacencyMatrix()[u][v] != 0) { // There is an edge from u to v
                if (colors[v] == -1) { // If vertex v is not colored
                    colors[v] = 1 - colors[u]; // Assign an alternate color to v
                    q.push(v);
                    if (colors[v] == 1) {
                        setA.push_back(v);
                    } else {
                        setB.push_back(v);
                    }
                } else if (colors[v] == colors[u]) { // If vertex u and v have the same color
                    return false;
                }
            }
        }
    }
    return true;
}

std::string Algorithms::isBipartite(const Graph &g) {
    std::vector<int> colors(g.getVertexNum(), -1); // Initialize all vertices as not colored
    std::vector<int> setA, setB;

    for (int i = 0; i < g.getVertexNum(); ++i) {
        if (colors[i] == -1) { // If the vertex is not colored
            if (!BFSUtil(g, i, colors, setA, setB)) {
                return "0";
            }
        }
    }

    std::ostringstream result;
    result << "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        result << setA[i];
        if (i < setA.size() - 1) {
            result << ", ";
        }
    }
    result << "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        result << setB[i];
        if (i < setB.size() - 1) {
            result << ", ";
        }
    }
    result << "}";

    return result.str();
}


std::string Algorithms::negativeCycle(const Graph &g) {
    std::stringstream ss;
    int V = g.getVertexNum();
    const int INF = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> matrix = g.getAdjacencyMatrix();
    std::vector<int> dist(V, INF);
    std::vector<int> parent(V, -1);

    dist[0] = 0;

    if (isContainsCycle(g) == "0") {
        return "0";
    }

    // Relax all edges |V|-1 times
    for (int i = 1; i <= V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                std::vector<int> cycle;
                std::vector<bool> visited(V, false);

                // To find the cycle, we follow the parent links until we find a cycle
                int cycleVertex = v;
                while (!visited[cycleVertex]) {
                    visited[cycleVertex] = true;
                    cycleVertex = parent[cycleVertex];
                }

                int startVertex = cycleVertex;
                cycle.push_back(startVertex);
                for (int cur = parent[startVertex]; cur != startVertex; cur = parent[cur]) {
                    cycle.push_back(cur);
                }
                cycle.push_back(startVertex);

                std::reverse(cycle.begin(), cycle.end());

                // Check the cycle size for undirected graphs
                if (cycle.size() < 4) {
                    ss << "0";
                    return ss.str();
                }

                ss << "The negative weight cycle is: ";
                for (size_t i = 0; i < cycle.size(); ++i) {
                    ss << cycle[i];
                    if (i < cycle.size() - 1) {
                        ss << "->";
                    }
                }
                return ss.str();
            }
        }
    }

    ss << "0";
    return ss.str();
}
