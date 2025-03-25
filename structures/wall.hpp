#pragma once

#include "../structure.hpp"

class Wall : public Structure {
private:
    sf::RectangleShape rectangle;
    sf::CircleShape circle;

public:
    Wall(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time delta) override {};
};
