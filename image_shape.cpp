#include "image_shape.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

ImageShape::PieceShape::PieceShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift) : getOriginShift(getOriginShift) {
}

void ImageShape::PieceShape::setOutline(std::function<float(sf::Vector2f)> getOutlineThickness, sf::Color color) {
    shape->setOutlineColor(color);
    this->getOutlineThickness = getOutlineThickness;
}

void ImageShape::PieceShape::setExtraRotation(sf::Angle angle) {
    shape->setRotation(angle);
    extraRotation = angle;
}

void ImageShape::PieceShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*shape, states);
}

ImageShape::RectanglePiece::RectanglePiece(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<sf::Vector2f(sf::Vector2f)> getDrawSize, sf::Color color) : PieceShape(getOriginShift), getDrawSize(getDrawSize) {
    shape.reset(new sf::RectangleShape());
    shape->setFillColor(color);
}

void ImageShape::RectanglePiece::init(sf::Vector2f drawSize, sf::Vector2f position) {
    sf::RectangleShape *rectangle = dynamic_cast<sf::RectangleShape *>(shape.get());
    rectangle->setSize(getDrawSize(drawSize));
    rectangle->setOrigin(getDrawSize(drawSize) / 2.f + getOriginShift(drawSize));
    rectangle->setPosition(position);
    if (getOutlineThickness) rectangle->setOutlineThickness(getOutlineThickness.value()(drawSize));
}

ImageShape::CirclePiece::CirclePiece(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<float(sf::Vector2f)> getRadius, sf::Color color, std::size_t pointNum) : PieceShape(getOriginShift), getRadius(getRadius) {
    shape.reset(new sf::CircleShape(0, pointNum));
    shape->setFillColor(color);
}

void ImageShape::CirclePiece::init(sf::Vector2f drawSize, sf::Vector2f position) {
    sf::CircleShape *circle = dynamic_cast<sf::CircleShape *>(shape.get());
    circle->setRadius(getRadius(drawSize));
    circle->setOrigin(sf::Vector2f{getRadius(drawSize), getRadius(drawSize)} + getOriginShift(drawSize));
    circle->setPosition(position);
    if (getOutlineThickness) circle->setOutlineThickness(getOutlineThickness.value()(drawSize));
}

ImageShape::ImageShape() : isInitted(false) {
}

void ImageShape::init(sf::Vector2f drawSize, sf::Vector2f position) {
    for (auto &shape : shapes) {
        shape->init(drawSize, position);
    }
    isInitted = true;
}

void ImageShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    assert(isInitted);
    for (auto &shape : shapes) {
        shape->draw(target, states);
    }
}

void ImageShape::setOutline(std::size_t index, std::function<float(sf::Vector2f)> getOutlineThickness, sf::Color color) {
    assert(index < shapes.size());
    shapes[index]->setOutline(getOutlineThickness, color);
}

void ImageShape::setExtraRotation(std::size_t index, sf::Angle angle) {
    assert(index < shapes.size());
    shapes[index]->setExtraRotation(angle);
}

void ImageShape::addRectangleShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<sf::Vector2f(sf::Vector2f)> getDrawSize, sf::Color color) {
    shapes.push_back(std::make_unique<ImageShape::RectanglePiece>(getOriginShift, getDrawSize, color));
}

void ImageShape::addCircleShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<float(sf::Vector2f)> getRadius, sf::Color color, std::size_t pointNum) {
    shapes.push_back(std::make_unique<ImageShape::CirclePiece>(getOriginShift, getRadius, color, pointNum));
}

void ImageShape::setRotation(sf::Angle angle) {
    for (auto &shape : shapes) {
        shape->setRotation(angle);
    }
}
