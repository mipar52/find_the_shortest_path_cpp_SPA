#include <SFML/Graphics.hpp>
#include "Graph.h"

const int CELL_SIZE = 20;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

void drawGrid(sf::RenderWindow& window, const Graph& graph, const Node& current, const Node& end) {
    window.clear(sf::Color::White);
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 40; ++j) {
            if (graph.isWall(i, j)) {
                cell.setFillColor(sf::Color::Black);
            }
            else {
                cell.setFillColor(sf::Color::White);
            }
            cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
            window.draw(cell);
        }
    }

    // Iscrtavanje krajnje tocke crvenom bojom
    cell.setFillColor(sf::Color::Red);
    cell.setPosition(end.y * CELL_SIZE, end.x * CELL_SIZE);
    window.draw(cell);

    // Iscrtavanje trenutne tocke zelenom bojom
    cell.setFillColor(sf::Color::Green);
    cell.setPosition(current.y * CELL_SIZE, current.x * CELL_SIZE);
    window.draw(cell);

    window.display();
}

int main() {
    int startX, startY, endX, endY;
    std::cout << "Unesite redak i stupac pocetne tocke A (odvojeno razmakom): ";
    std::cin >> startX >> startY;
    std::cout << "Unesite redak i stupac krajnje tocke B (odvojeno razmakom): ";
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

        std::cout << "Zelite li dodati jos zidova? (d/n): ";
        std::cin >> moreWalls;
    } while (moreWalls == 'd' || moreWalls == 'D');

    graph.dijkstra(start, end);
    auto path = graph.getPath();

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinding Visualization");

    for (const auto& node : path) {
        drawGrid(window, graph, node, end);
        sf::sleep(sf::milliseconds(100));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
