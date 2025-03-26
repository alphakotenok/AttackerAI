#pragma once

#include <SFML/Graphics.hpp>

class Structure : public sf::Drawable {
public:
    enum Type {
        WALL,
        CANNON,
        ARCHER_TOWER,
        MORTAR,
        AIR_DEFENCE,
        TOWN_HALL,

    };

protected:
    sf::Vector2i topLeft;
    Structure::Type type;
    float health;

    sf::Vector2f drawPosition;
    sf::Vector2f drawSize;

public:
    static sf::Vector2i getGridSize(Structure::Type type);
    static std::unique_ptr<Structure> create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);

    Structure(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);
    inline sf::Vector2i getTopLeft() { return topLeft; }
    inline sf::Vector2i getGridSize() { return Structure::getGridSize(type); }
    inline float getHealth() { return health; }
    virtual void update(sf::Time delta) = 0;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {};
};
