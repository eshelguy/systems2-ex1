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

// Operator Overloads

/**
 * @brief Returns a copy of the current graph.
 *
 * @return Graph A new Graph object that is a copy of the current graph.
 */
Graph Graph::operator+() const {
    return *this;
}

/**
 * @brief Adds the adjacency matrices of two graphs if they are the same size.
 *
 * @param graph The graph to be added.
 * @return Graph A new Graph object that is the sum of the two graphs.
 * @throws std::invalid_argument if the graphs are not the same size.
 */
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

/**
 * @brief Adds another graph’s adjacency matrix to the current graph’s matrix in-place.
 *
 * @param graph The graph to be added.
 * @return Graph& A reference to the current graph after addition.
 * @throws std::invalid_argument if the graphs are not the same size.
 */
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

/**
 * @brief Negates all edge weights in the graph.
 *
 * @return Graph A new Graph object with all edge weights negated.
 */
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

/**
 * @brief Subtracts the adjacency matrix of another graph from the current graph.
 *
 * @param graph The graph to be subtracted.
 * @return Graph A new Graph object that is the difference of the two graphs.
 * @throws std::invalid_argument if the graphs are not the same size.
 */
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

/**
 * @brief Subtracts another graph’s adjacency matrix from the current graph’s matrix in-place.
 *
 * @param graph The graph to be subtracted.
 * @return Graph& A reference to the current graph after subtraction.
 * @throws std::invalid_argument if the graphs are not the same size.
 */
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

// Comparison Operators

/**
 * @brief Determines if the current graph is "greater" than another graph.
 *
 * Checks if the current graph contains the other graph as a subgraph.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the current graph is greater, false otherwise.
 */
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
                    if (i + k >= largeMatrix ||
                        j + l >= largeMatrix ||
                        (graph.adjacencyMatrix[k][l] != 0 &&
                         graph.adjacencyMatrix[k][l] != adjacencyMatrix[k + i][l + j])) {
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

    if(edgesNum > graph.edgesNum){
        return true;
    }

    if (edgesNum < graph.edgesNum){
        return false;
    }

    if(adjacencyMatrix.size() > graph.adjacencyMatrix.size()){
        return true;
    }

    return false;
}

/**
 * @brief Checks if the current graph is greater than or equal to another graph.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the current graph is greater than or equal, false otherwise.
 */
bool Graph::operator>=(const Graph &graph) {
    return *this == graph || *this > graph;
}

/**
 * @brief Determines if the current graph is "less" than another graph.
 *
 * Checks if the current graph could be contained within the other graph.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the current graph is less, false otherwise.
 */
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
                    if (i + k >= largeMatrix ||
                        j + l >= largeMatrix ||
                        (adjacencyMatrix[k][l] != 0 &&
                         adjacencyMatrix[k][l] != graph.adjacencyMatrix[k + i][l + j])) {
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

    if(edgesNum < graph.edgesNum){
        return true;
    }

    if (edgesNum > graph.edgesNum){
        return false;
    }

    if(adjacencyMatrix.size() < graph.adjacencyMatrix.size()){
        return true;
    }

    return false;
}

/**
 * @brief Checks if the current graph is less than or equal to another graph.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the current graph is less than or equal, false otherwise.
 */
bool Graph::operator<=(const Graph &graph) {
    return *this == graph || *this < graph;
}

/**
 * @brief Checks if two graphs are identical by comparing their adjacency matrices.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the graphs are identical, false otherwise.
 */
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

/**
 * @brief Checks if two graphs are not equal.
 *
 * @param graph The graph to compare with.
 * @return bool Returns true if the graphs are not equal, false otherwise.
 */
bool Graph::operator!=(const Graph &graph) {
    return (!(*this == graph));
}

// Increment and Decrement Operators

/**
 * @brief Increments each non-zero edge weight by 1 (prefix increment).
 *
 * @return Graph& A reference to the incremented graph.
 */
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

/**
 * @brief Increments each non-zero edge weight by 1 (postfix increment).
 *
 * @return Graph A copy of the original graph before incrementing.
 */
Graph Graph::operator++(int) {
    Graph temp = *this; // Store the current state
    ++(*this);          // Use the prefix increment to update the current object
    return temp;        // Return the original state
}

/**
 * @brief Decrements each non-zero edge weight by 1 (prefix decrement).
 *
 * @return Graph& A reference to the decremented graph.
 */
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

/**
 * @brief Decrements each non-zero edge weight by 1 (postfix decrement).
 *
 * @return Graph A copy of the original graph before decrementing.
 */
Graph Graph::operator--(int) {
    Graph temp = *this; // Store the current state
    --(*this);          // Use the prefix decrement to update the current object
    return temp;        // Return the original state
}

// Multiplication Operators

/**
 * @brief Multiplies each edge weight in the graph by a scalar value num.
 *
 * @param num The scalar value to multiply the edge weights by.
 * @return Graph& A reference to the graph after multiplication.
 */
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

/**
 * @brief Performs matrix multiplication of two graphs' adjacency matrices.
 *
 * @param graph The graph to be multiplied with.
 * @return Graph The result of matrix multiplication of the two graphs.
 * @throws std::invalid_argument if the graphs are not the same size.
 */
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

/**
 * @brief Outputs the adjacency matrix of the graph to an output stream.
 *
 * @param output The output stream to write the matrix to.
 * @param g The graph whose adjacency matrix is to be printed.
 * @return std::ostream& The output stream after writing.
 */
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
