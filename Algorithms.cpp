//mail: guyes134@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

/**
 * @brief Checks if the graph is connected using Depth-First Search (DFS).
 *
 * This function performs a DFS starting from the first vertex and marks all reachable vertices.
 * If all vertices are visited, the graph is considered connected.
 *
 * @param g The graph to be checked.
 * @return int Returns 1 if the graph is connected, 0 otherwise.
 */
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

/**
 * @brief Function to relax all edges |V|-1 times in a graph.
 *
 * This function updates the distance and parent vectors by relaxing all the edges in the graph.
 * It is used in the Bellman-Ford and other shortest path algorithms.
 *
 * @param g The graph containing the edges.
 * @param dist The distance vector that will be updated.
 * @param parent The parent vector that will be updated to reconstruct paths.
 */
void Algorithms::relaxEdges(const Graph &g, std::vector<int> &dist, std::vector<int> &parent) {
    int V = g.getVertexNum();
    std::vector<std::vector<int>> matrix = g.getAdjacencyMatrix();
    const int INF = std::numeric_limits<int>::max();

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
}

/**
 * @brief Helper function for Depth-First Search (DFS) to mark visited vertices.
 *
 * This function performs a DFS from a given vertex, marking all reachable vertices as visited.
 *
 * @param g The graph to be searched.
 * @param v The current vertex in the DFS.
 * @param visited A vector tracking which vertices have been visited.
 */
void Algorithms::DFS(Graph g, int v, std::vector<bool> &visited) {
    visited[v] = true;
    for (int i = 0; i < g.getVertexNum(); ++i) {
        if (g.getAdjacencyMatrix()[v][i] != 0 && !visited[i]) {
            Algorithms::DFS(g, i, visited);
        }
    }
}

/**
 * @brief Finds the shortest path using Breadth-First Search (BFS) from start to end.
 *
 * This function finds the shortest path in an unweighted graph by exploring all nodes at the current depth level before moving on to nodes at the next depth level.
 *
 * @param g The graph in which the path is to be found.
 * @param start The starting vertex.
 * @param end The ending vertex.
 * @return std::string The shortest path from start to end as a string in the format "0->1->2". Returns "-1" if no path exists.
 */
std::string Algorithms::BFSShortestPath(const Graph &g, int start, int end) {
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

/**
 * @brief Finds the shortest path using Dijkstra's algorithm from start to end.
 *
 * This function finds the shortest path in a weighted graph with non-negative weights using Dijkstra's algorithm.
 *
 * @param g The graph in which the path is to be found.
 * @param start The starting vertex.
 * @param end The ending vertex.
 * @return std::string The shortest path from start to end as a string in the format "0->1->2". Returns "-1" if no path exists.
 */
std::string Algorithms::DijkstraShortestPath(const Graph &g, int start, int end) {
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

/**
 * @brief Finds the shortest path using the Bellman-Ford algorithm from start to end.
 *
 * This function finds the shortest path in a graph that may have negative weights using the Bellman-Ford algorithm.
 * It also detects negative weight cycles.
 *
 * @param g The graph in which the path is to be found.
 * @param start The starting vertex.
 * @param end The ending vertex.
 * @return std::string The shortest path from start to end as a string in the format "0->1->2". Returns "-1" if no path exists or "Negative cycle detected" if a negative cycle is found.
 */
std::string Algorithms::BellmanFordShortestPath(const Graph &g, int start, int end) {
    std::stringstream ss;
    int vertexNum = g.getVertexNum();
    const int INF = std::numeric_limits<int>::max();

    if (vertexNum == 0 || start >= vertexNum || end >= vertexNum) {
        return "-1";
    }

    std::vector<int> dist(vertexNum, INF);
    std::vector<int> parent(vertexNum, -1);
    dist[start] = 0;

    // Relax all edges
    relaxEdges(g, dist, parent);

    // Check for negative weight cycles
    for (int u = 0; u < vertexNum; ++u) {
        for (int v = 0; v < vertexNum; ++v) {
            int weight = g.getAdjacencyMatrix()[u][v];
            if (weight != 0 && dist[u] != INF && dist[u] + weight < dist[v]) {
                // Negative weight cycle found
                return "Negative cycle detected";
            }
        }
    }

    if (dist[end] == INF) {
        return "-1"; // No path found
    }

    // Reconstruct the path
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

/**
 * @brief Determines the shortest path from start to end using the appropriate algorithm
 * based on the presence of negative weights and whether the graph is weighted.
 *
 * This function selects the appropriate shortest path algorithm based on the properties of the graph:
 * - Uses Bellman-Ford if the graph has negative weights.
 * - Uses Dijkstra if the graph is weighted but has no negative weights.
 * - Uses BFS if the graph is unweighted.
 *
 * @param g The graph in which the path is to be found.
 * @param start The starting vertex.
 * @param end The ending vertex.
 * @return std::string The shortest path from start to end as a string in the format "0->1->2". Returns "-1" if no path exists.
 */
std::string Algorithms::shortestPath(const Graph &g, int start, int end) {
    if(start >= g.getVertexNum() || end >= g.getVertexNum()){
        return "-1";
    }
    else if (g.getHasNegEdges()) {
        return BellmanFordShortestPath(g, start, end);
    }
    else if (g.getIsWeighted()) {
        return DijkstraShortestPath(g, start, end);
    }
    else {
        return BFSShortestPath(g, start, end);
    }
}

/**
 * @brief Utility function for Depth-First Search (DFS) to detect cycles in a graph.
 *
 * This function helps detect cycles by recursively visiting nodes and tracking their parents.
 * If a back edge (an edge that points to one of the node's ancestors in the DFS tree) is found,
 * a cycle exists in the graph.
 *
 * @param g The graph to be checked.
 * @param v The current vertex being visited.
 * @param visited A vector tracking which vertices have been visited.
 * @param parent A vector tracking the parent of each vertex.
 * @param cycleStart Reference to the starting vertex of the detected cycle.
 * @param cycleEnd Reference to the ending vertex of the detected cycle.
 * @return bool Returns true if a cycle is found, false otherwise.
 */
bool Algorithms::DFSUtil(const Graph &g, int v, std::vector<bool> &visited, std::vector<int> &parent, int &cycleStart, int &cycleEnd) {
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

/**
 * @brief Checks if the graph contains a cycle using Depth-First Search (DFS).
 *
 * This function detects cycles in a graph and returns the cycle as a string.
 * If no cycle is found, it returns "0".
 *
 * @param g The graph to be checked.
 * @return std::string The cycle in the graph as a string in the format "0->1->2". Returns "0" if no cycle is found.
 */
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

/**
 * @brief Utility function for Breadth-First Search (BFS) to check if the graph is bipartite.
 *
 * This function checks if a graph can be colored with two colors such that no two adjacent vertices
 * share the same color, indicating that the graph is bipartite.
 *
 * @param g The graph to be checked.
 * @param src The source vertex from which BFS starts.
 * @param colors A vector tracking the color assigned to each vertex.
 * @param setA A vector tracking the vertices in set A of the bipartite graph.
 * @param setB A vector tracking the vertices in set B of the bipartite graph.
 * @return bool Returns true if the graph is bipartite, false otherwise.
 */
bool Algorithms::BFSUtil(const Graph &g, int src, std::vector<int> &colors, std::vector<int> &setA, std::vector<int> &setB) {
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

/**
 * @brief Checks if the graph is bipartite using Breadth-First Search (BFS).
 *
 * This function determines if a graph is bipartite by trying to color it with two colors.
 * It returns the sets A and B of the bipartite graph if it is bipartite, or "0" if it is not.
 *
 * @param g The graph to be checked.
 * @return std::string A string representation of the bipartite sets A and B. Returns "0" if the graph is not bipartite.
 */
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

/**
 * @brief Checks for the presence of negative weight cycles using the Bellman-Ford algorithm.
 *
 * This function detects negative weight cycles in a graph. If such a cycle is found, it returns the cycle as a string.
 * If no cycle is found, it returns "0".
 *
 * @param g The graph to be checked.
 * @return std::string The negative weight cycle in the graph as a string in the format "0->1->2". Returns "0" if no cycle is found.
 */
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

    // Relax all edges
    relaxEdges(g, dist, parent);

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
