#pragma once

#include "structure.hpp"
#include "tower.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include <vector>

class Sergei;

class StructureGrid : public sf::Drawable {
private:
    sf::Vector2i size;
    std::list<std::unique_ptr<Structure>> structures;
    std::vector<std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>> cellStructure;
    Sergei &sergei;

public:
    StructureGrid(Sergei &sergei);
    bool place(Structure::Type type, sf::Vector2i topLeft); // returns false if couldn't place
    void remove(std::list<std::unique_ptr<Structure>>::iterator &structure);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time deltaTime);
    const std::list<std::unique_ptr<Structure>> &getStructures() const;
};
