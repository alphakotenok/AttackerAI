#pragma once

#include "structure.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <list>

const float GRID_LINE_SIZE = 2.f;
const sf::Color GRASS_COLOR(0, 255, 0);
const sf::Color GRID_LINE_COLOR(20, 235, 20);

class Sergei;

class Background : public sf::Drawable {
private:
    sf::Vector2f center;
    sf::Vector2i gridSize;
    sf::RectangleShape grass;
    std::vector<sf::RectangleShape> gridLines;
    class WallConnection {
    public:
        sf::Vector2i first;
        sf::Vector2i second;
        sf::RectangleShape shape;
    };
    std::list<std::unique_ptr<WallConnection>> wallConnections;
    Sergei &sergei;

public:
    Background(Sergei &sergei, sf::Vector2i gridSize, sf::Vector2f center);
    void initWallConnections();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time deltaTime);
    inline sf::Vector2i getGridSize() { return gridSize; }
    inline sf::Vector2f getCenter() { return center; }
    inline sf::Vector2f getStructureDrawPosition(sf::Vector2i topLeft, sf::Vector2i gridSize) {
        return center + (sf::Vector2f)(2 * topLeft - this->gridSize + gridSize) * (CELL_SIZE / 2);
    }
    inline sf::Vector2f getStructureDrawSize(sf::Vector2i gridSize) {
        return (sf::Vector2f)gridSize * CELL_SIZE;
    }
};
