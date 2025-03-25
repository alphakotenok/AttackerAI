#include "background.hpp"
#include "camera.hpp"
#include "grid.hpp"

int main() {

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "AttackerAI", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Camera camera({0, 0}, {800, 600}, sf::Mouse::getPosition(window));

    Background bg({45, 45}, {0, 0});

    Grid grid(bg);

    grid.place(Structure::WALL, {27, 27});
    grid.place(Structure::WALL, {27, 26});
    grid.place(Structure::WALL, {27, 25});
    grid.place(Structure::WALL, {26, 27});
    grid.place(Structure::WALL, {28, 27});

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            camera.handleEvent(event);
        }

        grid.update(deltaTime);

        window.clear(sf::Color::White);

        window.draw(bg);
        window.draw(grid);

        camera.setViewOn(window);

        // Update the window
        window.display();
    }
    return 0;
}
