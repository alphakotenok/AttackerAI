#pragma once

#include <SFML/Graphics.hpp>

const float CELL_SIZE = 50.f;
const float GRID_LINE_SIZE = 2.f;
const sf::Color GRASS_COLOR(0, 255, 0);
const sf::Color GRID_LINE_COLOR(50, 205, 50);

class Background {
private:
    sf::Vector2f center;
    sf::Vector2i gridSize;
    sf::RectangleShape grass;
    std::vector<sf::RectangleShape> gridLines;

public:
    Background(sf::Vector2i gridSize, sf::Vector2f center);
    void drawOn(sf::RenderWindow &window);
};
