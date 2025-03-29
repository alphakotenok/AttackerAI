#pragma once

#include "image_shape.hpp"
#include <SFML/Graphics.hpp>

class Tower : public sf::Drawable {
private:
    std::unique_ptr<ImageShape> image;

public:
    Tower(std::unique_ptr<ImageShape> image);

    void update(sf::Time deltaTime) {}
    void initDraw(sf::Vector2f drawSize, sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
