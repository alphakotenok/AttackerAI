#pragma once

#include "unit.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class UnitGrid : public sf::Drawable {
public:
    void addUnit(std::unique_ptr<Unit> unit);
    void update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>>& structures);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const std::list<std::unique_ptr<Unit>>& getUnits() const;

private:
    std::list<std::unique_ptr<Unit>> units;
};
