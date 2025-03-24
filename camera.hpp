#pragma once

#include <SFML/Graphics.hpp>

const float ZOOM_FACTOR = 0.03f;

class Camera {
private:
    sf::View view;
    float totalZoom;
    bool isDragging;
    sf::Vector2f windowSize;
    sf::Vector2i currentMousePos;
    sf::Vector2i lastMousePos;

public:
    Camera(sf::Vector2f center, sf::Vector2f size, sf::Vector2i mousePos);
    void handleEvents(const std::optional<sf::Event> &event);
    void setView(sf::RenderWindow &window);
};
