#pragma once

#include "image_shape.hpp"
#include "structure_grid.hpp"
#include "unit.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Tower : public sf::Drawable {
private:
    Structure::Type type;
    std::unique_ptr<ImageShape> image;
    Sergei &sergei;
    std::optional<std::size_t> targetIndex;
    sf::Vector2f position;
    float innerRadius;
    float outerRadius;

    sf::Angle getAngleToTarget(sf::Vector2f point) {
        float len = distanceL2(point, {0, 0});
        return sf::radians(-std::atan2(point.x, point.y) + std::acos(-1));
    }

    bool isInRadius(sf::Vector2f position) {
        float distance = distanceL2(this->position, position) / CELL_SIZE;
        return distance > innerRadius - EPS && distance < outerRadius + EPS;
    }

public:
    Tower(std::unique_ptr<ImageShape> image, Sergei &sergei, float innerRadius, float outerRadius, Structure::Type type);
    void update(sf::Time deltaTime);
    void initDraw(sf::Vector2f drawSize, sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
