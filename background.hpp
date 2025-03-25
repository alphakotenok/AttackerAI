#pragma once

#include <SFML/Graphics.hpp>

const float CELL_SIZE = 50.f;
const float GRID_LINE_SIZE = 2.f;
const sf::Color GRASS_COLOR(0, 255, 0);
const sf::Color GRID_LINE_COLOR(20, 235, 20);

class Background : public sf::Drawable, public sf::Transformable {
private:
    sf::Vector2f center;
    sf::Vector2i gridSize;
    sf::RectangleShape grass;
    std::vector<sf::RectangleShape> gridLines;

public:
    Background(sf::Vector2i gridSize, sf::Vector2f center);
    inline sf::Vector2i getGridSize() { return gridSize; }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    inline sf::Vector2f getCenter() {
        return center;
    }
    inline sf::Vector2f getStructureOrigin(sf::Vector2i topLeft, sf::Vector2i size) { // grid params -> draw params
        return (sf::Vector2f)(gridSize - 2 * topLeft) * (CELL_SIZE / 2);
    }
    sf::Vector2f getStructureSize(sf::Vector2i size) { // grid params -> draw params
        return (sf::Vector2f)size * CELL_SIZE;
    }
};
