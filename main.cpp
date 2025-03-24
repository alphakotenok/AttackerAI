#include "background.hpp"
#include "camera.hpp"

int main() {

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "AttackerAI", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Camera camera({0, 0}, {800, 600}, sf::Mouse::getPosition(window));

    Background bg({45, 45}, {0, 0});

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time delta = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            camera.handleEvents(event);
        }

        window.clear(sf::Color::White);

        camera.setViewOn(window);
        bg.drawOn(window);

        // Update the window
        window.display();
    }
    return 0;
}
