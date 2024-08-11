//mail: guyes134@gmail.com

#include "Graph.hpp"
#include <functional>

using namespace std;

/**
 * @brief Constructor to initialize the Graph with a given adjacency matrix and properties.
 *
 * @param matrix The adjacency matrix representing the graph.
 * @param direction Specifies if the graph is directed (true) or undirected (false).
 * @param negWeight Specifies if the graph contains negative weights (true) or not (false).
 * @param weight Specifies if the graph is weighted (true) or unweighted (false).
 * @param verNum The number of vertices in the graph.
 * @param edgNum The number of edges in the graph.
 */
Graph::Graph(std::vector<std::vector<int>> matrix, bool direction, bool negWeight, bool weight, int verNum, int edgNum) {
    this->adjacencyMatrix = matrix;
    this->isDirected = direction;
    this->isWeighted = weight;
    this->vertexNum = verNum;
    this->edgesNum = edgNum;
    this->hasNegWeight = negWeight;
}

/**
 * @brief Default constructor for the Graph class.
 *
 * Initializes an empty graph with no vertices or edges, and sets default properties for direction,
 * weight, and negative weight.
 */
Graph::Graph() : vertexNum(0), edgesNum(0), isDirected(false), isWeighted(false), hasNegWeight(0) {}

/**
 * @brief Destructor for the Graph class.
 *
 * Clears the adjacency matrix to free memory.
 */
Graph::~Graph() {
    adjacencyMatrix.clear();
}

/**
 * @brief Loads a new graph from the given adjacency matrix.
 *
 * Updates the number of vertices and edges, and determines if the graph is directed,
 * weighted, or has negative weights.
 *
 * @param matrix The adjacency matrix representing the graph.
 */
void Graph::loadGraph(const vector<vector<int>> &matrix) {
    this->adjacencyMatrix.clear();
    this->vertexNum = 0;
    this->edgesNum = 0;

    if (!isSquare(matrix)) {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    this->adjacencyMatrix = matrix;
    this->vertexNum = matrix.size();
    int countEdges = 0;

    if (isDirectedGraph()) {
        isDirected = true;
    }

    if (isWeightedGraph()) {
        isWeighted = true;
    }

    if (hasNegativeWeights()) {
        hasNegWeight = true;
    }

    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                countEdges++;
            }
        }
    }
    this->edgesNum = isDirected ? countEdges : countEdges / 2;
}

/**
 * @brief Prints the adjacency matrix of the graph to the console.
 */
void Graph::printGraph() {
    for (int i = 0; i < this->vertexNum; ++i) {
        for (int j = 0; j < this->vertexNum; ++j) {
            cout << this->adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Checks if the given matrix is a square matrix (the number of rows equals the number of columns).
 *
 * @param matrix The matrix to be checked.
 * @return bool Returns true if the matrix is square, false otherwise.
 */
bool Graph::isSquare(const vector<vector<int>> &matrix) const {
    auto numRows = matrix.size();
    for (const auto &row: matrix) {
        if (row.size() != numRows) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Determines if the graph is weighted by checking if any edge weight is not 0 or 1.
 *
 * @return bool Returns true if the graph is weighted, false otherwise.
 */
bool Graph::isWeightedGraph() const {
    for (const auto& row : adjacencyMatrix) {
        for (int weight : row) {
            if (weight != 0 && weight != 1) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the graph has negative weights.
 *
 * @return bool Returns true if the graph has negative weights, false otherwise.
 */
bool Graph::hasNegativeWeights() const {
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] < 0) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Determines if the graph is directed by checking if the adjacency matrix is symmetric.
 *
 * @return bool Returns true if the graph is directed, false otherwise.
 */
bool Graph::isDirectedGraph() const {
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = i + 1; j < getAdjacencyMatrix().size(); ++j) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the current graph and the given graph have the same size adjacency matrix.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if both graphs have the same size adjacency matrix, false otherwise.
 */
bool Graph::isTheSameSize(const Graph &graph) const {
    return getAdjacencyMatrix().size() == graph.getAdjacencyMatrix().size();
}
