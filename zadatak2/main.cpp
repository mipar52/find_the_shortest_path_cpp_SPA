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

    int wallX, wallY;
    char moreWalls;
    do {
        std::cout << "Unesite redak i stupac zida (odvojeno razmakom): ";
        std::cin >> wallX >> wallY;
        graph.addWall(wallX - 1, wallY - 1);

        std::cout << "Želite li dodati još zidova? (d/n): ";
        std::cin >> moreWalls;
    } while (moreWalls == 'd' || moreWalls == 'D');

    graph.dijkstra(start, end);
    graph.printPath();

    return 0;
}
