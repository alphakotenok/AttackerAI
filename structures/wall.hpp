#pragma once

#include "../structure.hpp"

class Wall : public Structure {
private:
    sf::RectangleShape rectangle;
    sf::CircleShape circle;

public:
    Wall(sf::Vector2i topLeft, sf::Vector2f drawCenter, sf::Vector2f drawOrigin, sf::Vector2f drawSize);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
