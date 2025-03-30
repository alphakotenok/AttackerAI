#pragma once

#include "SFML/Graphics/Shape.hpp"
#include <functional>

class ImageShape : public sf::Drawable {
private:
    class PieceShape : public sf::Drawable {
    protected:
        std::unique_ptr<sf::Shape> shape;
        std::function<sf::Vector2f(sf::Vector2f)> getOriginShift;
        std::optional<std::function<float(sf::Vector2f)>> getOutlineThickness;
        sf::Angle extraRotation;

    public:
        PieceShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift);
        virtual void init(sf::Vector2f drawSize, sf::Vector2f position) = 0;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setOutline(std::function<float(sf::Vector2f)> getOutlineThickness, sf::Color color);
        inline void setRotation(sf::Angle angle) { shape->setRotation(angle + extraRotation); }
        void setExtraRotation(sf::Angle angle);
    };

    class RectanglePiece : public PieceShape {
    private:
        std::function<sf::Vector2f(sf::Vector2f)> getDrawSize;
        void init(sf::Vector2f drawSize, sf::Vector2f position) override;

    public:
        RectanglePiece(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<sf::Vector2f(sf::Vector2f)> getDrawSize, sf::Color color);
    };
    class CirclePiece : public PieceShape {
    private:
        std::function<float(sf::Vector2f)> getRadius;
        void init(sf::Vector2f drawSize, sf::Vector2f position) override;

    public:
        CirclePiece(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<float(sf::Vector2f)> getRadius, sf::Color color, std::size_t pointNum = 30);
    };

    std::vector<std::unique_ptr<PieceShape>> shapes;
    bool isInitted = false;

public:
    ImageShape();

    void init(sf::Vector2f drawSize, sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void addRectangleShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<sf::Vector2f(sf::Vector2f)> getDrawSize, sf::Color color);
    void addCircleShape(std::function<sf::Vector2f(sf::Vector2f)> getOriginShift, std::function<float(sf::Vector2f)> getRadius, sf::Color color, std::size_t pointNum = 30);

    void setOutline(std::size_t index, std::function<float(sf::Vector2f)> getOutlineThickness, sf::Color color);
    void setExtraRotation(std::size_t index, sf::Angle angle);
    void setRotation(sf::Angle angle);
};
