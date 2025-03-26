#include "mortar.hpp"

Mortar::Mortar(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : Structure(type, topLeft, drawPosition, drawSize) {
    health = 450;

    leg1.setSize({drawSize.x * 0.3f, drawSize.y * 0.933f});
    leg1.setOrigin({drawSize.x * (0.5f - 1.f / 30.f), drawSize.y * 0.466f});
    leg1.setPosition(drawPosition);
    leg1.setFillColor(sf::Color(150, 150, 150));

    leg2.setSize({drawSize.x * 0.3f, drawSize.y * 0.933f});
    leg2.setOrigin({drawSize.x * (1.f / 30.f - 0.2f), drawSize.y * 0.466f});
    leg2.setPosition(drawPosition);
    leg2.setFillColor(sf::Color(150, 150, 150));

    body.setSize({drawSize * 0.7f});
    body.setOrigin(drawSize * 0.35f);
    body.setPosition(drawPosition);
    body.setFillColor(sf::Color(160, 82, 45));

    base.setRadius(drawSize.x * 0.25f);
    base.setOrigin(drawSize * 0.25f);
    base.setPosition(drawPosition);
    base.setFillColor(sf::Color(90, 90, 90));

    muzzle.setRadius(drawSize.x * 0.13f);
    muzzle.setOrigin(drawSize * 0.13f - sf::Vector2f{drawSize.x * 0.1f, 0.f});
    muzzle.setPosition(drawPosition);
    muzzle.setFillColor(sf::Color(30, 30, 30));
}

void Mortar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(leg1, states);
    target.draw(leg2, states);
    target.draw(body, states);
    target.draw(base, states);
    target.draw(muzzle, states);
}

void Mortar::rotate(sf::Angle angle) {
    muzzle.rotate(angle);
}
