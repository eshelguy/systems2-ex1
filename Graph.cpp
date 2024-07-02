#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace std;

//constructor
Graph::Graph(std::vector<std::vector<int>> matrix, bool direction, bool negWeight, bool weight, int verNum, int edgNum) {
    this->adjacencyMatrix = matrix;
    this->isDirected = direction;
    this->isWeighted = weight;
    this->vertexNum = verNum;
    this->edgesNum = edgNum;
    this->hasNegWeight = negWeight;
}

Graph::Graph() : edgesNum(0), vertexNum(0), hasNegWeight(0), isDirected(false), isWeighted(false) {}

//Graph::~Graph(){
//    delete(this);
//}

void Graph::loadGraph(const vector<vector<int>>& matrix) {
    this->adjacencyMatrix.clear();
    this->vertexNum = 0;
    this->edgesNum = 0;

    if (!isSquare(matrix)){
        throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    this->adjacencyMatrix = matrix;
    this->vertexNum = matrix.size();
    int countEdges = 0;

    if (isDirectedGraph()){
        isDirected = true;
    }

    if (hasNegativeWeights()){
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

void Graph::printGraph() {
    for (int i = 0; i < this->vertexNum; ++i) {
        for (int j = 0; j < this->vertexNum; ++j) {
            cout << this->adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool Graph::isSquare(const vector<vector<int>> &matrix) const {
    int numRows = matrix.size();
    for (const auto& row : matrix) {
        if (row.size() != numRows) {
            return false;
        }
    }
    return true;
}
bool Graph::hasNegativeWeights() const {
    for (size_t i = 0; i < getAdjacencyMatrix().size(); ++i) {
        for (size_t j = 0; j < getAdjacencyMatrix().size(); ++j) {
            if (adjacencyMatrix[i][j] < 0) {
                return true; // Found a negative weight
            }
        }
    }
    return false; // No negative weights found
}

bool Graph::isDirectedGraph() const {
    // Check if the adjacency matrix is symmetric
    for (size_t i = 0; i < getAdjacencyMatrix().size(); ++i) {
        for (size_t j = i + 1; j < getAdjacencyMatrix().size(); ++j) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
                return true; // Graph is directed
            }
        }
    }
    return false; // Graph is undirected
}