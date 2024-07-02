//guyes134@gmail.com

## README

# Graph Algorithms Implementation

This project provides an implementation of various fundamental graph algorithms using an adjacency matrix representation
for the graph. The algorithms include connectivity check, shortest path finding (both unweighted and weighted),
cycle detection, bipartiteness check, and negative cycle detection. The implementation is written in C++.

## Introduction

This project provides a set of functions to perform common graph operations using a class-based approach. The `Graph` class encapsulates the graph representation, while the `Algorithms` namespace contains various functions to operate on graphs.

## Features

- **Graph Representation**: Adjacency matrix representation of graphs.
- **Connectivity Check**: Determines if a graph is connected.
- **Shortest Path Finding**: Implements both BFS for unweighted graphs and Dijkstra's algorithm for weighted graphs.
- **Cycle Detection**: Identifies cycles in the graph.
- **Bipartiteness Check**: Determines if the graph is bipartite.
- **Negative Cycle Detection**: Detects the presence of negative weight cycles.


## Usage

### Graph Class

The `Graph` class represents a graph using an adjacency matrix. It provides methods to load and print the graph, as well as to check properties like whether the graph is directed or has negative weights.

### Algorithms Class

The `Algorithms` namespace contains various graph algorithms. It provides methods to check connectivity, find the shortest path, detect cycles, check bipartiteness, and detect negative weight cycles.

## Graph Class

The `Graph` class is designed to represent a graph using an adjacency matrix. It includes several methods and attributes that facilitate the manipulation and examination of graph properties.

### Graph Class Methods

- **Constructor**: Initializes the graph with the given parameters.
- **loadGraph**: Loads a graph from an adjacency matrix.
- **printGraph**: Prints the adjacency matrix of the graph.
- **isSquare**: Checks if the provided matrix is square.
- **hasNegativeWeights**: Checks if the graph has negative weights.
- **isDirectedGraph**: Checks if the graph is directed.

### Graph Class Attributes

- **vertexNum**: Number of vertices.
- **edgesNum**: Number of edges.
- **isDirected**: Boolean indicating if the graph is directed.
- **isWeighted**: Boolean indicating if the graph is weighted.
- **hasNegWeight**: Boolean indicating if the graph has negative weights.
- **adjacencyMatrix**: Adjacency matrix representation of the graph.

## Algorithms Class

The `Algorithms` namespace contains various functions that operate on `Graph` objects to perform common graph operations.

### Algorithms Functions

- **isConnected**: Checks if the graph is connected.
- **shortestPath**: Finds the shortest path between two vertices using BFS or Dijkstra's algorithm.
- **isContainsCycle**: Detects if the graph contains any cycle.
- **isBipartite**: Checks if the graph is bipartite.
- **negativeCycle**: Detects if the graph contains a negative weight cycle.
- **DFS**: Depth-First Search helper function.


## Testing

The project includes unit tests using the Doctest framework.


