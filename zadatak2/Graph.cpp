#include "Graph.h"

// Konstruktor grafa
Graph::Graph(int rows, int cols) : rows(rows), cols(cols) {
    initializeGrid();
}

// Inicijalizacija mreže
void Graph::initializeGrid() {
    grid.resize(rows, std::vector<int>(cols, 1));
    distances.resize(rows, std::vector<int>(cols, INT_MAX));
    previous.resize(rows, std::vector<Node>(cols, { -1, -1, -1 }));
}

// Provjera je li pozicija unutar granica mreže
bool Graph::isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

// Dodavanje zida na mrežu
void Graph::addWall(int x, int y) {
    if (isValid(x, y)) {
        grid[x][y] = INT_MAX; // Zid
    }
}

// Implementacija Dijkstra algoritma
void Graph::dijkstra(Node start, Node end) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({ start.x, start.y, 0 });
    distances[start.x][start.y] = 0;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.x == end.x && current.y == end.y) {
            reconstructPath(end);
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY) && grid[newX][newY] != INT_MAX && distances[newX][newY] > current.distance + grid[newX][newY]) {
                distances[newX][newY] = current.distance + grid[newX][newY];
                pq.push({ newX, newY, distances[newX][newY] });
                previous[newX][newY] = current;
            }
        }
    }
}

// Rekonstrukcija puta nakon što je Dijkstra algoritam pronašao najkraæi put
void Graph::reconstructPath(Node end) {
    Node current = end;
    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        current = previous[current.x][current.y];
    }
    std::reverse(path.begin(), path.end());
}

// Iscrtavanje puta na mreži
void Graph::printPath() {
    for (const auto& node : path) {
        system("clear");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == node.x && j == node.y)
                    std::cout << "X ";
                else if (grid[i][j] == INT_MAX)
                    std::cout << "# "; // Zid
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
