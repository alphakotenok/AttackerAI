#include "structure_grid.hpp"
#include "structure.hpp"
#include <optional>

const float EPS = 1e-4;

Grid::Grid(Background &bg) : bg(bg) {
    size = bg.getGridSize();
    cellStructure = std::vector<std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>>(
        size.y,
        std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>(size.x));
}

bool Grid::place(Structure::Type type, sf::Vector2i topLeft) {
    auto structureGridSize = Structure::getGridSize(type);
    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            if (topLeft.y + y < 0 || topLeft.y + y >= size.y ||
                topLeft.x + x < 0 || topLeft.x + x >= size.x ||
                cellStructure[topLeft.y + y][topLeft.x + x].has_value()) {
                return false;
            }
        }
    }
    auto structure = Structure::create(type, topLeft, bg.getCenter(), bg.getStructureOrigin(topLeft, structureGridSize), bg.getStructureSize(structureGridSize));
    structures.push_back(std::move(structure));

    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            cellStructure[topLeft.y + y][topLeft.x + x] = --structures.end();
        }
    }

    return true;
}

void Grid::remove(std::list<std::unique_ptr<Structure>>::iterator &structure) {
    auto structureTopLeft = structure->get()->getTopLeft();
    auto structureGridSize = structure->get()->getGridSize();
    for (int y = 0; y < structureGridSize.y; ++y) {
        for (int x = 0; x < structureGridSize.x; ++x) {
            cellStructure[structureTopLeft.y + y][structureTopLeft.x + x] = std::nullopt;
        }
    }
    structure = structures.erase(structure);
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = bg.getTransform();
    for (auto &structure : structures) {
        target.draw(*structure.get(), states);
    }
}

void Grid::update(sf::Time deltaTime) {
    auto structure = structures.begin();
    while (structure != structures.end()) {
        structure->get()->update(deltaTime);
        if (structure->get()->getHealth() < EPS) {
            remove(structure);
        } else {
            ++structure;
        }
    }
}
