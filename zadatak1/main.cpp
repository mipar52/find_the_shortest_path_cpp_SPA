#include <iostream>
#include "Graph.h"

int main() {
    int startX, startY, endX, endY;
    std::cout << "Unesite redak i stupac poèetne toèke A (odvojeno razmakom): ";
    std::cin >> startX >> startY;
    std::cout << "Unesite redak i stupac krajnje toèke B (odvojeno razmakom): ";
    std::cin >> endX >> endY;

    Node start = { startX - 1, startY - 1, 0 };
    Node end = { endX - 1, endY - 1, 0 };

    Graph graph(20, 40);
    graph.dijkstra(start, end);
    graph.printPath();

    return 0;
}
