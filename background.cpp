#include "background.hpp"
#include "Sergei.hpp"
#include "structure_grid.hpp"
#include "unit.hpp"
#include "utils.hpp"
#include <iostream>
#include <optional>

Background::Background(Sergei &sergei, sf::Vector2i gridSize, sf::Vector2f center) : sergei(sergei), gridSize(gridSize), center(center) {

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
    target.draw(grass, states);
    for (auto &line : gridLines) {
        target.draw(line, states);
    }
    for (auto &connection : wallConnections) {
        target.draw(connection->shape, states);
    }
}

void Background::initWallConnections() {
    StructureGrid &sg = sergei.getStructureGrid();
    for (int i = 0; i < gridSize.x - 1; ++i) {
        for (int j = 0; j < gridSize.y; ++j) {
            std::optional<Structure *> str1 = sg.getStructureAtPosition({i, j});
            std::optional<Structure *> str2 = sg.getStructureAtPosition({i + 1, j});
            if (str1.has_value() && str2.has_value() && str1.value()->getType() == Structure::Type::WALL && str2.value()->getType() == Structure::Type::WALL) {
                auto connection = std::make_unique<WallConnection>();
                connection->first = {i, j};
                connection->second = {i + 1, j};
                connection->shape.setSize({CELL_SIZE * 0.2f, CELL_SIZE * 0.6f});
                connection->shape.setFillColor(sf::Color(90, 90, 90));
                connection->shape.setOrigin(connection->shape.getGeometricCenter());
                connection->shape.setPosition(getStructureDrawPosition({i, j}, {2, 1}));
                wallConnections.push_back(std::move(connection));
            }
        }
    }

    for (int i = 0; i < gridSize.x; ++i) {
        for (int j = 0; j < gridSize.y - 1; ++j) {
            std::optional<Structure *> str1 = sg.getStructureAtPosition({i, j});
            std::optional<Structure *> str2 = sg.getStructureAtPosition({i, j + 1});
            if (str1.has_value() && str2.has_value() && str1.value()->getType() == Structure::Type::WALL && str2.value()->getType() == Structure::Type::WALL) {
                auto connection = std::make_unique<WallConnection>();
                connection->first = {i, j};
                connection->second = {i, j + 1};
                connection->shape.setSize({CELL_SIZE * 0.6f, CELL_SIZE * 0.2f});
                connection->shape.setFillColor(sf::Color(90, 90, 90));
                connection->shape.setOrigin(connection->shape.getGeometricCenter());
                connection->shape.setPosition(getStructureDrawPosition({i, j}, {1, 2}));
                wallConnections.push_back(std::move(connection));
            }
        }
    }
}

void Background::update(sf::Time deltaTime) {
    StructureGrid &sg = sergei.getStructureGrid();
    auto wallConnection = wallConnections.begin();
    while (wallConnection != wallConnections.end()) {
        if (sg.getStructureAtPosition(wallConnection->get()->first).has_value() &&
            sg.getStructureAtPosition(wallConnection->get()->second).has_value() &&
            sg.getStructureAtPosition(wallConnection->get()->first).value()->getType() == Structure::Type::WALL &&
            sg.getStructureAtPosition(wallConnection->get()->second).value()->getType() == Structure::Type::WALL) {
            ++wallConnection;
        } else {
            wallConnection = wallConnections.erase(wallConnection);
        }
    }
}
