#include "unit_grid.hpp"
#include "unit.hpp"
#include <algorithm>

void UnitGrid::addUnit(std::unique_ptr<Unit> unit) {
    units.push_back(std::move(unit));
}

void UnitGrid::update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>>& structures) {
    
    for (auto& unit : units) {
        unit->update(deltaTime, structures);
    }

    units.erase(
        std::remove_if(units.begin(), units.end(),
            [](const std::unique_ptr<Unit>& unit) { return unit->isDead(); }),
        units.end());
}

void UnitGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& unit : units) {
        target.draw(*unit, states);
    }
}

const std::list<std::unique_ptr<Unit>>& UnitGrid::getUnits() const {
    return units;
}
