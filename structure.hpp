#pragma once

#include <SFML/Graphics.hpp>

class Structure : public sf::Drawable {
protected:
    sf::Vector2i topLeft;
    sf::Vector2i gridSize;
    float health;

    sf::Vector2f drawPosition;
    sf::Vector2f drawOrigin;
    sf::Vector2f drawSize;

public:
    Structure(sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawOrigin, sf::Vector2f drawSize);
    inline sf::Vector2i getTopLeft() { return topLeft; }
    inline sf::Vector2i getGridSize() { return gridSize; }
    inline float getHealth() { return health; }
    void update(sf::Time delta) {};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {};
    enum Type {
        WALL,
        CANNON
    };
    static sf::Vector2i getGridSize(Structure::Type type);
    static std::unique_ptr<Structure> create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawRelativePosition, sf::Vector2f drawSize);
};
