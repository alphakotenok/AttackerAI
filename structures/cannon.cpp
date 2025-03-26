#include "cannon.hpp"

Cannon::Cannon(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : Structure(type, topLeft, drawPosition, drawSize) {
    health = 620;
    outer.setSize(drawSize * 0.933f);
    outer.setOrigin(drawSize * 0.4665f);
    outer.setPosition(drawPosition);
    outer.setFillColor(sf::Color(150, 150, 150));

    base.setRadius(drawSize.x * 0.36f);
    base.setOrigin(drawSize * 0.36f);
    base.setPosition(drawPosition);
    base.setFillColor(sf::Color(160, 82, 45));

    backCircle.setRadius(drawSize.x * 0.15f);
    backCircle.setOrigin(drawSize * 0.15f);
    backCircle.setPosition(drawPosition);
    backCircle.setFillColor(sf::Color(90, 90, 90));

    cannon.setSize({drawSize.x * 0.5f, drawSize.y * 0.3f});
    cannon.setOrigin(sf::Vector2f{0, drawSize.y * 0.15f});
    cannon.setPosition(drawPosition);
    cannon.setFillColor(sf::Color(90, 90, 90));

    muzzle.setSize({drawSize.x * (1.f / 15.f), drawSize.y * (1.f / 3.f)});
    muzzle.setOrigin(sf::Vector2f{drawSize.x * (1.f / 30.f), drawSize.y * (1.f / 6.f)} - sf::Vector2f{drawSize.x * (0.5f - 1.f / 30.f), 0});
    muzzle.setPosition(drawPosition);
    muzzle.setFillColor(sf::Color(110, 110, 110));
}

void Cannon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(outer, states);
    target.draw(base, states);
    target.draw(backCircle, states);
    target.draw(cannon, states);
    target.draw(muzzle, states);
}

void Cannon::rotate(sf::Angle angle) {
    backCircle.rotate(angle);
    cannon.rotate(angle);
    muzzle.rotate(angle);
}
