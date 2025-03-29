#include "tower.hpp"

Tower::Tower(std::unique_ptr<ImageShape> image) {
    this->image = std::move(image);
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*image, states);
}

void Tower::initDraw(sf::Vector2f drawSize, sf::Vector2f position) {
    image->init(drawSize, position);
}
