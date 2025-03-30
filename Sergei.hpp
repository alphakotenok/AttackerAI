#pragma once

#include "background.hpp"
#include "bullet_manager.hpp"
#include "structure_grid.hpp"
#include "unit_grid.hpp"

class Sergei : public sf::Drawable {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<StructureGrid> sg;
    std::unique_ptr<UnitGrid> ug;
    std::unique_ptr<BulletManager> bm;

public:
    Sergei(sf::Vector2i gridSize, sf::Vector2f center);
    Background &getBackground();
    StructureGrid &getStructureGrid();
    UnitGrid &getUnitGrid();
    BulletManager &getBulletManager();

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
