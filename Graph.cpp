//mail: guyes134@gmail.com

#include "Graph.hpp"
#include <functional>

using namespace std;

//constructor
Graph::Graph(std::vector<std::vector<int>> matrix, bool direction, bool negWeight, bool weight, int verNum,
             int edgNum) {
    this->adjacencyMatrix = matrix;
    this->isDirected = direction;
    this->isWeighted = weight;
    this->vertexNum = verNum;
    this->edgesNum = edgNum;
    this->hasNegWeight = negWeight;
}

Graph::Graph() : vertexNum(0), edgesNum(0), isDirected(false), isWeighted(false), hasNegWeight(0) {}

Graph::~Graph() {}

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

void Graph::printGraph() {
    for (int i = 0; i < this->vertexNum; ++i) {
        for (int j = 0; j < this->vertexNum; ++j) {
            cout << this->adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool Graph::isSquare(const vector<vector<int>> &matrix) const {
    auto numRows = matrix.size();
    for (const auto &row: matrix) {
        if (row.size() != numRows) {
            return false;
        }
    }
    return true;
}

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

bool Graph::isTheSameSize(const Graph &graph) const {
    return getAdjacencyMatrix().size() == graph.getAdjacencyMatrix().size();
}
