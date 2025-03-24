#include "camera.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "AttackerAI");
    window.setFramerateLimit(60);
    Camera camera({0, 0}, {800, 600}, sf::Mouse::getPosition(window));

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({-50.f, -50.f});

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time delta = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            camera.handleEvents(event);
        }

        window.clear(sf::Color::White);
        camera.setView(window);

        window.draw(circle);

        // Update the window
        window.display();
    }
    return 0;
}
