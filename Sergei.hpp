#pragma once

#include "background.hpp"
#include "structure_grid.hpp"
#include "unit_grid.hpp"

class Sergei {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<StructureGrid> sg;
    std::unique_ptr<UnitGrid> ug;

public:
    Sergei(sf::Vector2i gridSize, sf::Vector2f center);
    Background &getBackground();
    StructureGrid &getStructureGrid();
    UnitGrid &getUnitGrid();
};
