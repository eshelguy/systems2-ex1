//mail: guyes134@gmail.com

#pragma once

#include <vector>
#include <iostream>


class Graph{
private:
    int vertexNum;
    int edgesNum;
    bool isDirected;
    bool isWeighted;
    bool hasNegWeight;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    //methods
    void loadGraph(const std::vector<std::vector<int>>& matrix);
    void printGraph();
    bool isSquare(const std::vector<std::vector<int>> &matrix) const;
    bool hasNegativeWeights() const;
    bool isDirectedGraph() const;


    //constructors
    Graph();
    Graph(std::vector<std::vector<int>> matrix, bool direction, bool negWeight, bool weight, int veNum, int edgNum);

    ~Graph();

    int getVertexNum() const{
        return this->vertexNum;
    }

    int getEdgesNum() const{
        return edgesNum;
    }
    std::vector<std::vector<int>> getAdjacencyMatrix() const{
        return this->adjacencyMatrix;
    }

    bool getIsDirected() const{
        return isDirected;
    }

    bool getIsWeighted() const{
        return isWeighted;
    }

    bool getHasNegEdges() const{
        return hasNegWeight;
    }

    bool isTheSameSize(const Graph& graph) const;

    bool isWeightedGraph() const;
