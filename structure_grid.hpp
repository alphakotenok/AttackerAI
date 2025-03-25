#pragma once

#include "background.hpp"
#include "structure.hpp"
#include <SFML/Graphics.hpp>
#include <list>

class StuctureGrid : public sf::Drawable {
private:
    sf::Vector2i size;
    std::list<std::unique_ptr<Structure>> structures;
    std::vector<std::vector<std::optional<std::list<std::unique_ptr<Structure>>::iterator>>> cellStructure;
    Background &bg;

public:
    StuctureGrid(Background &bg);
    bool place(Structure::Type type, sf::Vector2i topLeft); // returns false if couldn't place
    void remove(std::list<std::unique_ptr<Structure>>::iterator &structure);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time deltaTime);
};
