#pragma once

#include "utils.hpp"
#include <SFML/Graphics.hpp>

const float GRID_LINE_SIZE = 2.f;
const sf::Color GRASS_COLOR(0, 255, 0);
const sf::Color GRID_LINE_COLOR(20, 235, 20);

class Background : public sf::Drawable {
private:
    sf::Vector2f center;
    sf::Vector2i gridSize;
    sf::RectangleShape grass;
    std::vector<sf::RectangleShape> gridLines;

public:
    Background(sf::Vector2i gridSize, sf::Vector2f center);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    inline sf::Vector2i getGridSize() { return gridSize; }
    inline sf::Vector2f getCenter() { return center; }
    inline sf::Vector2f getStructureDrawPosition(sf::Vector2i topLeft, sf::Vector2i gridSize) {
        return center + (sf::Vector2f)(2 * topLeft - this->gridSize + gridSize) * (CELL_SIZE / 2);
    }
    inline sf::Vector2f getStructureDrawSize(sf::Vector2i gridSize) {
        return (sf::Vector2f)gridSize * CELL_SIZE;
    }
};
