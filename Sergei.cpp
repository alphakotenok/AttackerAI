#include "Sergei.hpp"
#include "bullet.hpp"
#include "unit_grid.hpp"

Sergei::Sergei(sf::Vector2i gridSize, sf::Vector2f center) {
    bg = std::make_unique<Background>(gridSize, center);
    sg = std::make_unique<StructureGrid>(*this);
    ug = std::make_unique<UnitGrid>(*this);
    bm = std::make_unique<BulletManager>();
}

Background &Sergei::getBackground() {
    assert(bg);
    return *bg;
}
StructureGrid &Sergei::getStructureGrid() {
    assert(sg);
    return *sg;
}
UnitGrid &Sergei::getUnitGrid() {
    assert(ug);
    return *ug;
}

BulletManager &Sergei::getBulletManager() {
    assert(bm);
    return *bm;
}

void Sergei::update(sf::Time deltaTime) {
    sg->update(deltaTime);
    ug->update(deltaTime);
}

void Sergei::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*bg, states);
    target.draw(*sg, states);
    target.draw(*ug, states);
    target.draw(*bm, states);
}
