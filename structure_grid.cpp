#include "structure_grid.hpp"
#include "Sergei.hpp"
#include "structure.hpp"
#include <optional>

StructureGrid::StructureGrid(Sergei &sergei) : sergei(sergei) {
    size = sergei.getBackground().getGridSize();
    cellStructure = std::vector<std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>>(
        size.x,
        std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>(size.y));
}

bool StructureGrid::place(Structure::Type type, sf::Vector2i topLeft) {
    auto structureGridSize = Structure::getGridSize(type);
    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            if (topLeft.y + y < 0 || topLeft.y + y >= size.y ||
                topLeft.x + x < 0 || topLeft.x + x >= size.x ||
                cellStructure[topLeft.x + x][topLeft.y + y].has_value()) {
                return false;
            }
        }
    }
    auto structure = Structure::create(type, sergei, topLeft);
    structure->initDraw(sergei.getBackground().getStructureDrawSize(structureGridSize), sergei.getBackground().getStructureDrawPosition(topLeft, structureGridSize));
    structures.push_back(std::move(structure));

    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            cellStructure[topLeft.x + x][topLeft.y + y] = --structures.end();
        }
    }

    return true;
}

void StructureGrid::remove(std::list<std::unique_ptr<Structure>>::iterator &structure) {
    auto structureTopLeft = structure->get()->getTopLeft();
    auto structureGridSize = structure->get()->getGridSize();
    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            cellStructure[structureTopLeft.x + x][structureTopLeft.y + y] = std::nullopt;
        }
    }
    structure = structures.erase(structure);
}

void StructureGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &structure : structures) {
        target.draw(*structure.get(), states);
    }
}

void StructureGrid::update(sf::Time deltaTime) {
    auto structure = structures.begin();
    while (structure != structures.end()) {
        structure->get()->update(deltaTime);
        if (structure->get()->getToDelete()) {
            sergei.getUnitGrid().setUpdateTargets();
            remove(structure);
        } else {
            ++structure;
        }
    }
}

const std::list<std::unique_ptr<Structure>> &StructureGrid::getStructures() const {
    return structures;
}

std::optional<Structure *> StructureGrid::getStructureAtPosition(sf::Vector2i position) {
    if (!cellStructure[position.x][position.y]) return std::nullopt;
    return cellStructure[position.x][position.y].value()->get();
}
