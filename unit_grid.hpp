#pragma once

#include "unit.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class Sergei;

class UnitGrid : public sf::Drawable {
public:
    UnitGrid(Sergei &sergei);
    void addUnit(std::unique_ptr<Unit> unit);
    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    const std::list<std::unique_ptr<Unit>> &getUnits() const;
    std::vector<std::unique_ptr<Unit>> &getUnitsVec();
    void setUpdateTargets() { updateTargets = true; };

private:
    std::list<std::unique_ptr<Unit>> units;
    std::vector<std::unique_ptr<Unit>> unitsVec;
    Sergei &sergei;
    bool updateTargets;
};
