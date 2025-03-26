#include "wall.hpp"

Wall::Wall(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : Structure(type, topLeft, drawPosition, drawSize) {
    health = 900;
    outer.setSize(drawSize * 0.8f);
    outer.setOrigin(0.4f * drawSize);
    outer.setPosition(drawPosition);
    outer.setFillColor(sf::Color(60, 60, 60));

    inner.setSize(drawSize * 0.4f);
    inner.setOrigin(0.2f * drawSize);
    inner.setPosition(drawPosition);
    inner.setFillColor(sf::Color(100, 100, 100));
}

void Wall::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(outer, states);
    target.draw(inner, states);
}
