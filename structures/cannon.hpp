#pragma once

#include "../structure.hpp"

class Cannon : public Structure {
private:
    sf::RectangleShape outer;
    sf::CircleShape base;
    sf::CircleShape backCircle;
    sf::RectangleShape cannon;
    sf::RectangleShape muzzle;

public:
    Cannon(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time delta) override {
        rotate(sf::degrees(360.f * delta.asSeconds()));
    };
    void rotate(sf::Angle angle);
};
