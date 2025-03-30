#include "Sergei.hpp"
#include "background.hpp"
#include "bullet.hpp"
#include "camera.hpp"
#include "structure.hpp"
#include "structure_grid.hpp"
#include "tower.hpp"
#include "unit.hpp"
#include "unit_grid.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "AttackerAI", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Camera camera({0, 0}, {800, 600}, sf::Mouse::getPosition(window));

    Sergei sergei({45, 45}, {0, 0});

    Background &bg = sergei.getBackground();
    StructureGrid &structureGrid = sergei.getStructureGrid();
    UnitGrid &unitGrid = sergei.getUnitGrid();

    structureGrid.place(Structure::BUILDERS_HUT, {10, 10});
    structureGrid.place(Structure::BUILDERS_HUT, {9, 13});
    structureGrid.place(Structure::BUILDERS_HUT, {13, 9});

    structureGrid.place(Structure::COLLECTOR_GOLD, {12, 12});
    structureGrid.place(Structure::COLLECTOR_ELIXIR, {8, 16});
    structureGrid.place(Structure::COLLECTOR_ELIXIR, {16, 8});

    structureGrid.place(Structure::BARRACK, {8, 20});
    structureGrid.place(Structure::BARRACK, {20, 8});

    structureGrid.place(Structure::ARMY_CAMP, {11, 23});
    structureGrid.place(Structure::ARMY_CAMP, {23, 12});

    structureGrid.place(Structure::COLLECTOR_GOLD, {15, 28});
    structureGrid.place(Structure::COLLECTOR_GOLD, {27, 16});

    structureGrid.place(Structure::COLLECTOR_ELIXIR, {19, 28});
    structureGrid.place(Structure::BARRACK, {27, 20});

    structureGrid.place(Structure::LABORATORY, {23, 27});
    structureGrid.place(Structure::COLLECTOR_ELIXIR, {26, 24});
    structureGrid.place(Structure::COLLECTOR_GOLD, {23, 24});
    structureGrid.place(Structure::BUILDERS_HUT, {26, 27});

    structureGrid.place(Structure::STORAGE_GOLD, {12, 16});
    structureGrid.place(Structure::CANNON, {12, 19});
    structureGrid.place(Structure::ARCHER_TOWER, {16, 12});
    structureGrid.place(Structure::STORAGE_ELIXIR, {19, 12});

    structureGrid.place(Structure::CLAN_CASTLE, {16, 17});
    structureGrid.place(Structure::MORTAR, {16, 20});
    structureGrid.place(Structure::AIR_DEFENSE, {19, 16});
    structureGrid.place(Structure::TOWN_HALL, {19, 19});

    structureGrid.place(Structure::STORAGE_ELIXIR, {16, 24});
    structureGrid.place(Structure::ARCHER_TOWER, {19, 24});
    structureGrid.place(Structure::CANNON, {23, 17});
    structureGrid.place(Structure::STORAGE_GOLD, {23, 20});

    structureGrid.place(Structure::BOMB, {15, 16});
    structureGrid.place(Structure::BOMB, {15, 17});
    structureGrid.place(Structure::SPRING_TRAP, {19, 15});
    structureGrid.place(Structure::SPRING_TRAP, {17, 23});

    for (int i = 0; i < 8; ++i) structureGrid.place(Structure::WALL, {11 + i, 15});
    for (int i = 0; i < 7; ++i) structureGrid.place(Structure::WALL, {11, 16 + i});
    for (int i = 0; i < 3; ++i) structureGrid.place(Structure::WALL, {12 + i, 22});
    for (int i = 0; i < 10; ++i) structureGrid.place(Structure::WALL, {15, 18 + i});
    for (int i = 0; i < 7; ++i) structureGrid.place(Structure::WALL, {16 + i, 27});
    for (int i = 0; i < 3; ++i) structureGrid.place(Structure::WALL, {22, 26 - i});
    for (int i = 0; i < 9; ++i) structureGrid.place(Structure::WALL, {18 + i, 23});
    for (int i = 0; i < 7; ++i) structureGrid.place(Structure::WALL, {26, 22 - i});
    for (int i = 0; i < 3; ++i) structureGrid.place(Structure::WALL, {25 - i, 16});
    for (int i = 0; i < 8; ++i) structureGrid.place(Structure::WALL, {22, 18 - i});
    for (int i = 0; i < 7; ++i) structureGrid.place(Structure::WALL, {21 - i, 11});
    for (int i = 0; i < 3; ++i) structureGrid.place(Structure::WALL, {15, 12 + i});

    for (int i = 0; i < 80; ++i) {
        auto barbarian = Unit::create(sf::Vector2f(1000 * cos(sf::degrees(360.f / 80.f * i).asRadians()), 1000 * sin(sf::degrees(360.f / 80.f * i).asRadians())));
        barbarian->getShape()->setFillColor(sf::Color::Red);
        barbarian->initDraw(sf::Vector2f(30, 30));
        unitGrid.addUnit(std::move(barbarian));
    }

    sergei.getBackground().initWallConnections();

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            camera.handleEvent(event);
        }

        sergei.update(deltaTime);

        window.clear(sf::Color(0, 168, 0));

        window.draw(sergei);

        camera.setViewOn(window);

        window.display();
    }

    return 0;
}
