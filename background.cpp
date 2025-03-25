#include "background.hpp"

Background::Background(sf::Vector2i gridSize, sf::Vector2f center) : gridSize(gridSize), center(center) {

    grass.setSize((sf::Vector2f)gridSize * CELL_SIZE);
    grass.setFillColor(GRASS_COLOR);
    grass.setOrigin((sf::Vector2f)gridSize * (CELL_SIZE / 2));
    grass.setPosition(center);

    gridLines.resize((gridSize.x + 1) + (gridSize.y + 1));

    for (int i = 0; i <= gridSize.x; ++i) {
        gridLines[i].setSize({GRID_LINE_SIZE, gridSize.y * CELL_SIZE + GRID_LINE_SIZE});
        gridLines[i].setFillColor(GRID_LINE_COLOR);
        gridLines[i].setOrigin({(gridSize.x * CELL_SIZE + GRID_LINE_SIZE) / 2 - i * CELL_SIZE, (gridSize.y * CELL_SIZE + GRID_LINE_SIZE) / 2});
        gridLines[i].setPosition(center);
    }

    for (int j = 0; j <= gridSize.y; ++j) {
        gridLines[gridSize.x + 1 + j].setSize({gridSize.x * CELL_SIZE + GRID_LINE_SIZE, GRID_LINE_SIZE});
        gridLines[gridSize.x + 1 + j].setFillColor(GRID_LINE_COLOR);
        gridLines[gridSize.x + 1 + j].setOrigin({(gridSize.x * CELL_SIZE + GRID_LINE_SIZE) / 2, (gridSize.y * CELL_SIZE + GRID_LINE_SIZE) / 2 - j * CELL_SIZE});
        gridLines[gridSize.x + 1 + j].setPosition(center);
    }
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(grass, states);
    for (auto &line : gridLines) {
        target.draw(line, states);
    }
}
