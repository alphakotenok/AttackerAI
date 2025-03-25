#include "wall.hpp"

Wall::Wall(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : Structure(type, topLeft, drawPosition, drawSize) {
    health = 100;
    rectangle.setSize(drawSize * 0.8f);
    rectangle.setOrigin(drawOrigin - 0.1f * drawSize);
    rectangle.setPosition(drawPosition);
    rectangle.setFillColor(sf::Color(80, 80, 80));

    circle.setRadius(drawSize.x * 0.20);
    circle.setOrigin(drawOrigin - 0.30f * drawSize);
    circle.setPosition(drawPosition);
    circle.setFillColor(sf::Color(120, 120, 120));
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rectangle, states);
    target.draw(circle, states);
}
