#include "structure.hpp"
#include "structures/wall.hpp"
#include <memory>

Structure::Structure(sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawOrigin, sf::Vector2f drawSize) : topLeft(topLeft), drawPosition(drawPosition), drawOrigin(drawOrigin), drawSize(drawSize) {}

sf::Vector2i Structure::getGridSize(Structure::Type type) {
    if (type == WALL) return {1, 1};
    if (type == CANNON) return {3, 3};
    return {1, 1};
}

std::unique_ptr<Structure> Structure::create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawOrigin, sf::Vector2f drawSize) {
    if (type == WALL) return std::make_unique<Wall>(topLeft, drawPosition, drawOrigin, drawSize);
    return nullptr;
}
