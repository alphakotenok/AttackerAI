#include "structure.hpp"
#include "structures/archer_tower.hpp"
#include "structures/cannon.hpp"
#include "structures/mortar.hpp"
#include "structures/wall.hpp"
#include <memory>

Structure::Structure(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : type(type), topLeft(topLeft), drawPosition(drawPosition), drawSize(drawSize) {}

sf::Vector2i Structure::getGridSize(Structure::Type type) {
    if (type == WALL) return {1, 1};
    if (type == CANNON) return {3, 3};
    if (type == ARCHER_TOWER) return {3, 3};
    if (type == MORTAR) return {3, 3};
    return {1, 1};
}

std::unique_ptr<Structure> Structure::create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) {
    if (type == WALL) return std::make_unique<Wall>(type, topLeft, drawPosition, drawSize);
    if (type == CANNON) return std::make_unique<Cannon>(type, topLeft, drawPosition, drawSize);
    if (type == ARCHER_TOWER) return std::make_unique<ArcherTower>(type, topLeft, drawPosition, drawSize);
    if (type == MORTAR) return std::make_unique<Mortar>(type, topLeft, drawPosition, drawSize);
    return nullptr;
}
