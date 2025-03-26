#pragma once

#include "../structure.hpp"

class Mortar : public Structure {
private:
    sf::RectangleShape leg1, leg2;
    sf::RectangleShape body;
    sf::CircleShape base;
    sf::CircleShape muzzle;

public:
    Mortar(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time delta) override {
        rotate(sf::degrees(360.f * delta.asSeconds()));
    };
    void rotate(sf::Angle angle);
};
