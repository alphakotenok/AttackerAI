#include "archer_tower.hpp"

ArcherTower::ArcherTower(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : Structure(type, topLeft, drawPosition, drawSize) {
    health = 500;
    outer.setSize(drawSize * 0.933f);
    outer.setOrigin(drawSize * 0.4665f);
    outer.setPosition(drawPosition);
    outer.setFillColor(sf::Color(0, 168, 0));

    inner.setSize(drawSize * 0.5f);
    inner.setOrigin(drawSize * 0.25f);
    inner.setPosition(drawPosition);
    inner.setOutlineThickness(drawSize.x * 0.05f);
    inner.setOutlineColor(sf::Color(140, 140, 140));
    inner.setFillColor(sf::Color(139, 69, 19));

    archer.setPointCount(3);
    archer.setRadius(drawSize.x * 0.25f);
    archer.setOrigin(drawSize * 0.25f);
    archer.setPosition(drawPosition);
    archer.setFillColor(sf::Color(205, 0, 77));

    muzzle.setSize({drawSize.x * 0.12f, drawSize.y * 0.4f});
    muzzle.setOrigin({drawSize.x * 0.06f, drawSize.y * (0.2f + 0.15f)});
    muzzle.setPosition(drawPosition);
    muzzle.setFillColor(sf::Color(205, 0, 77));

    archer.rotate(sf::degrees(90));
    muzzle.rotate(sf::degrees(90));
}

void ArcherTower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(outer, states);
    target.draw(inner, states);
    target.draw(archer, states);
    target.draw(muzzle, states);
}

void ArcherTower::rotate(sf::Angle angle) {
    archer.rotate(angle);
    muzzle.rotate(angle);
}
