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

//operators

//Returns a copy of the current graph.
Graph Graph::operator+() const {
    return *this;
}

//Adds the adjacency matrices of two graphs if they are the same size
Graph Graph::operator+(const Graph &graph) const {
    if (!(this->isTheSameSize(graph))) {
        throw invalid_argument("Graphs are not the same size.");
    }
    Graph g(adjacencyMatrix, isDirected, hasNegWeight, isWeighted, vertexNum, edgesNum);
    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + graph.adjacencyMatrix[i][j];
        }
    }
    return g;
}

//Adds another graph’s adjacency matrix to the current graph’s matrix in-place.
Graph &Graph::operator+=(const Graph &graph) {
    if (!(this->isTheSameSize(graph))) {
        throw invalid_argument("Graphs are not the same size.");
    }

    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + graph.adjacencyMatrix[i][j];
        }
    }
    return *this;
}

//Negates all edge weights in the graph
Graph Graph::operator-() const {
    Graph g(adjacencyMatrix, isDirected, hasNegWeight, isWeighted, vertexNum, edgesNum);
    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g.adjacencyMatrix[i][j] = (-1) * adjacencyMatrix[i][j];
        }
    }
    return g;
}

//Subtracts the adjacency matrix of another graph from the current graph
Graph Graph::operator-(const Graph &graph) const {
    if (!(this->isTheSameSize(graph))) {
        throw invalid_argument("Graphs are not the same size.");
    }
    Graph g(adjacencyMatrix, isDirected, hasNegWeight, isWeighted, vertexNum, edgesNum);
    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - graph.adjacencyMatrix[i][j];
        }
    }
    return g;
}

//Subtracts another graph’s adjacency matrix from the current graph’s matrix in-place.
Graph &Graph::operator-=(const Graph &graph) {
    if (!(this->isTheSameSize(graph))) {
        throw invalid_argument("Graphs are not the same size.");
    }

    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - graph.adjacencyMatrix[i][j];
        }
    }
    return *this;
}

//compare operators

//Determines if the current graph is "greater" than another graph. It checks if the current graph contains the other graph as a subgraph.
bool Graph::operator>(const Graph &graph) {
    int largeMatrix = adjacencyMatrix.size();
    int smallMatrix = graph.adjacencyMatrix.size();

    if (largeMatrix < smallMatrix) {
        return false;
    }

    for (int i = 0; i < largeMatrix - smallMatrix + 1; ++i) {
        for (int j = 0; j < largeMatrix - smallMatrix + 1; ++j) {
            bool isSubMatrix = true;

            for (int k = 0; k < smallMatrix; ++k) {
                for (int l = 0; l < smallMatrix; ++l) {
                    if (
                            i + k >= largeMatrix ||
                            j + l >= largeMatrix ||
                            (graph.adjacencyMatrix[k][l] != 0 &&
                            graph.adjacencyMatrix[k][l] != adjacencyMatrix[k + i][l + j])){
                        isSubMatrix = false;
                        break;
                    }
                }
                if (!isSubMatrix) {
                    break;
                }
            }
            if (isSubMatrix) {
                return true;
            }
        }
    }

    if(vertexNum > graph.vertexNum){
        return true;
    }

    if (vertexNum < graph.vertexNum){
        return false;
    }

    if(adjacencyMatrix.size() > graph.adjacencyMatrix.size()){
        return true;
    }

    if(adjacencyMatrix.size() < graph.adjacencyMatrix.size()){
        return false;
    }
    
    return false;
}

//Checks if the current graph is greater than or equal to another graph.
bool Graph::operator>=(const Graph &graph) {
    return *this == graph || *this > graph;
}

////----------------------------------------------------------------------------------------------------------
////----------------------------------------------------------------------------------------------------------
//
//
//// Helper function to check if a submatrix matches the graph
//bool Graph:: isSubMatrixMatch(const std::vector<std::vector<int>>& largerGraph, const std::vector<std::vector<int>>& subGraph, int startRow, int startCol) const {
//    size_t subRows = subGraph.size();
//    size_t subCols = subGraph[0].size();
//
//    for (size_t i = 0; i < subRows; ++i) {
//        for (size_t j = 0; j < subCols; ++j) {
//            if (largerGraph[startRow + i][startCol + j] != subGraph[i][j]) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//// Function to check if the current graph is contained in another graph
//bool Graph::isContainedInGraph(const Graph& other) const {
//    if (vertexNum > other.vertexNum) {
//        return false;
//    }
//    int a = 0;
//    if (vertexNum == other.vertexNum){
//        for (int i = 0; i < vertexNum; ++i) {
//            for (int j = 0; j < vertexNum; ++j) {
//                if (adjacencyMatrix[i][j]!=other.adjacencyMatrix[i][j]){
//                    ++a;
//                }
//            }
//        }
//        if (a == 0) return false;
//    }
//
//    int subRows = vertexNum;
//    int subCols = vertexNum;
//    const auto& otherGraph = other.getAdjacencyMatrix();
//
//    for (int i = 0; i <= other.vertexNum - subRows; ++i) {
//        for (int j = 0; j <= other.vertexNum - subCols; ++j) {
//            if (isSubMatrixMatch(otherGraph, adjacencyMatrix, i, j)) {
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//
////bool Graph::operator<(const Graph& other) const {
////    if (isContainedInGraph(other)) {
////        return true;
////    }
////    if (other.isContainedInGraph(*this)) {
////        return false;
////    }
////    if (this->getEdgesNum() < other.getEdgesNum()) {
////        return true;
////    } else if (this->getEdgesNum() == other.getEdgesNum() && vertexNum < other.vertexNum) {
////        return true;
////    }
////    return false;
////}

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------

//Checks if the current graph is "less" than another graph, meaning it could be contained within the other graph.
bool Graph::operator<(const Graph &graph) {
    int smallMatrix = adjacencyMatrix.size();
    int largeMatrix = graph.adjacencyMatrix.size();

    if (largeMatrix < smallMatrix) {
        return false;
    }

    for (int i = 0; i < largeMatrix - smallMatrix + 1; ++i) {
        for (int j = 0; j < largeMatrix - smallMatrix + 1; ++j) {
            bool isSubMatrix = true;

            for (int k = 0; k < smallMatrix; ++k) {
                for (int l = 0; l < smallMatrix; ++l) {
                    if (
                            i + k >= largeMatrix ||
                            j + l >= largeMatrix ||
                            (adjacencyMatrix[k][l] != 0 &&
                            adjacencyMatrix[k][l] != graph.adjacencyMatrix[k + i][l + j])){
                        isSubMatrix = false;
                        break;
                    }
                }
                if (!isSubMatrix) {
                    break;
                }
            }
            if (isSubMatrix) {
                return true;
            }
        }
    }


    if(vertexNum < graph.vertexNum){
        return true;
    }

    if (vertexNum > graph.vertexNum){
        return false;
    }

    if(adjacencyMatrix.size() < graph.adjacencyMatrix.size()){
        return true;
    }

    if(adjacencyMatrix.size() > graph.adjacencyMatrix.size()){
        return false;
    }

    return false;
}

//Checks if the current graph is less than or equal to another graph.
bool Graph::operator<=(const Graph &graph) {
    return *this == graph || *this < graph;
}

//Checks if two graphs are identical by comparing their adjacency matrices.
bool Graph::operator==(const Graph &graph) {
    auto n = adjacencyMatrix.size();

    if (n != graph.adjacencyMatrix.size()) {
        return false;
    }

    for (int i = 0; i < (int)n; ++i) {
        for (int j = 0; j < (int)n; ++j) {
            if (adjacencyMatrix[i][j] != graph.adjacencyMatrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//Checks if two graphs are not equal.
bool Graph::operator!=(const Graph &graph) {
    return (!(*this == graph));
}

//increase operators
//Increments each non-zero edge weight by 1.
Graph &Graph::operator++() {
    if (this->adjacencyMatrix.size() == 0) {
        return *this;
    }

    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + 1;
            }
        }
    }
    return *this;
}

//Decrements each non-zero edge weight by 1.
Graph &Graph::operator--() {
    if (this->adjacencyMatrix.size() == 0) {
        return *this;
    }

    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - 1;
            }
        }
    }
    return *this;
}

//Multiplies each edge weight in the graph by a scalar value num.
Graph &Graph::operator*(int num) {
    if (this->adjacencyMatrix.size() == 0) {
        return *this;
    }

    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adjacencyMatrix[i][j] = adjacencyMatrix[i][j] * num;
        }
    }
    return *this;
}

//Performs matrix multiplication of two graphs' adjacency matrices.
Graph Graph::operator*(const Graph &graph) const {
    if (this->adjacencyMatrix.size() == 0 && graph.adjacencyMatrix.size() == 0) {
        return *this;
    }
    if (this->adjacencyMatrix.size() != graph.adjacencyMatrix.size()) {
        throw invalid_argument("The Graphs are not same size");
    }

    int n = adjacencyMatrix.size();
    Graph g(adjacencyMatrix, isDirected, hasNegWeight, isWeighted, vertexNum, edgesNum);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g.adjacencyMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g.adjacencyMatrix[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                g.adjacencyMatrix[i][j] += (adjacencyMatrix[i][k] * graph.adjacencyMatrix[k][j]);
            }
        }
    }
    return g;
}

//Outputs the adjacency matrix of the graph to an output stream.
std::ostream &operator<<(std::ostream &output, const Graph &g) {
    int n = g.adjacencyMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            output << g.adjacencyMatrix[i][j];
            if (j < n - 1) {
                output << ", ";
            }
        }
        output << std::endl;
    }
    return output;
}
