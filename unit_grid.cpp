#include "unit_grid.hpp"
#include "Sergei.hpp"
#include "structure.hpp"
#include "unit.hpp"

UnitGrid::UnitGrid(Sergei &sergei) : sergei(sergei) {}

void UnitGrid::addUnit(std::unique_ptr<Unit> unit) {
    unitsVec.push_back(std::move(unit));
}

void UnitGrid::update(sf::Time deltaTime) {
    const std::list<std::unique_ptr<Structure>> &structures = sergei.getStructureGrid().getStructures();
    for (auto &unit : unitsVec) {
        if (!unit->isDead()) unit->update(deltaTime, structures);
    }
}

void UnitGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &unit : unitsVec) {
        if (!unit->isDead()) target.draw(*unit, states);
    }
}

const std::list<std::unique_ptr<Unit>> &UnitGrid::getUnits() const {
    return units;
}

std::vector<std::unique_ptr<Unit>> &UnitGrid::getUnitsVec() {
    return unitsVec;
}
