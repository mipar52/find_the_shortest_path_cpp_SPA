#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <thread>
#include <chrono>

// Definicija strukture èvora
struct Node {
    int x, y;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Definicija klase grafa
class Graph {
public:
    Graph(int rows, int cols);
    void dijkstra(Node start, Node end);
    void printPath();
private:
    int rows, cols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<Node>> previous;
    std::vector<Node> path;
    void initializeGrid();
    bool isValid(int x, int y);
    void reconstructPath(Node end);
};

#endif