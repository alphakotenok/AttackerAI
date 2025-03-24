#include "camera.hpp"

Camera::Camera(sf::Vector2f center, sf::Vector2f windowSize, sf::Vector2i mousePos) : totalZoom(1.f), isDragging(false), currentMousePos(mousePos), windowSize(windowSize) {
    view.setSize(windowSize);
    view.setCenter(center);
}

void Camera::handleEvents(const std::optional<sf::Event> &event) {
    if (const auto mouse = event->getIf<sf::Event::MouseMoved>()) {
        currentMousePos = mouse->position;
        if (isDragging) {
            view.move({(lastMousePos.x - currentMousePos.x) * totalZoom, (lastMousePos.y - currentMousePos.y) * totalZoom});
            lastMousePos = mouse->position;
        }
    }
    if (const auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button == sf::Mouse::Button::Left) {
            lastMousePos = mouse->position;
            isDragging = true;
        }
    }
    if (const auto mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (mouse->button == sf::Mouse::Button::Left) {
            isDragging = false;
        }
    }
    if (const auto wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
        float zoom = std::exp(wheel->delta * ZOOM_FACTOR);
        view.move({(windowSize.x / 2 - currentMousePos.x) * (zoom - 1) * totalZoom, (windowSize.y / 2 - currentMousePos.y) * (zoom - 1) * totalZoom});

        view.zoom(zoom);
        totalZoom *= zoom;
    }
    if (const auto resized = event->getIf<sf::Event::Resized>()) {
        windowSize = {(float)resized->size.x, (float)resized->size.y};
        view.setSize(windowSize);
        view.zoom(totalZoom);
    }
}

void Camera::setViewOn(sf::RenderWindow &window) {
    window.setView(view);
}
