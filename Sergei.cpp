#include "Sergei.hpp"
#include "unit_grid.hpp"

Sergei::Sergei(sf::Vector2i gridSize, sf::Vector2f center) {
    bg = std::make_unique<Background>(gridSize, center);
    sg = std::make_unique<StructureGrid>(*this);
    ug = std::make_unique<UnitGrid>();
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
