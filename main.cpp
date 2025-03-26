#include "background.hpp"
#include "camera.hpp"
#include "structure_grid.hpp"

int main() {

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "AttackerAI", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Camera camera({0, 0}, {800, 600}, sf::Mouse::getPosition(window));

    Background bg({45, 45}, {0, 0});

    StuctureGrid structureGrid(bg);

    structureGrid.place(Structure::WALL, {27, 27});
    structureGrid.place(Structure::WALL, {27, 26});
    structureGrid.place(Structure::WALL, {27, 25});
    structureGrid.place(Structure::WALL, {26, 27});
    structureGrid.place(Structure::WALL, {28, 27});

    structureGrid.place(Structure::CANNON, {28, 24});
    structureGrid.place(Structure::CANNON, {31, 24});
    structureGrid.place(Structure::CANNON, {34, 24});
    structureGrid.place(Structure::CANNON, {31, 21});
    structureGrid.place(Structure::CANNON, {31, 18});

    structureGrid.place(Structure::ARCHER_TOWER, {24, 24});
    structureGrid.place(Structure::ARCHER_TOWER, {21, 24});
    structureGrid.place(Structure::ARCHER_TOWER, {18, 24});
    structureGrid.place(Structure::ARCHER_TOWER, {21, 21});
    structureGrid.place(Structure::ARCHER_TOWER, {21, 18});

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            camera.handleEvent(event);
        }

        structureGrid.update(deltaTime);

        window.clear(sf::Color::White);

        window.draw(bg);
        window.draw(structureGrid);

        camera.setViewOn(window);

        // Update the window
        window.display();
    }
    return 0;
}
