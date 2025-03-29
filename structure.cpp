#include "structure.hpp"
#include "image_shape.hpp"
#include "structures/archer_tower.hpp"
#include "structures/mortar.hpp"

Structure::Structure(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) : type(type), topLeft(topLeft), drawPosition(drawPosition), drawSize(drawSize) {}

Structure::Structure(Structure::Type type, sf::Vector2i topLeft, std::unique_ptr<ImageShape> baseImage) : type(type), topLeft(topLeft), baseImage(std::move(baseImage)) {
    health = getHealth(type);
}

sf::Vector2i Structure::getGridSize(Structure::Type type) {
    if (type == WALL) return {1, 1};
    if (type == CANNON) return {3, 3};
    if (type == ARCHER_TOWER) return {3, 3};
    if (type == MORTAR) return {3, 3};
    if (type == AIR_DEFENCE) return {3, 3};
    if (type == TOWN_HALL) return {4, 4};
    if (type == CLAN_CASTLE) return {3, 3};
    if (type == STORAGE) return {3, 3};
    if (type == COLLECTOR) return {3, 3};
    if (type == ARMY_CAMP) return {4, 4};
    if (type == LABORATORY) return {3, 3};
    if (type == BOMB) return {1, 1};
    if (type == SPRING_TRAP) return {1, 1};
    return {0, 0};
}

float Structure::getHealth(Structure::Type type) {
    if (type == WALL) return 900;
    if (type == CANNON) return 620;
    return 1;
}

std::unique_ptr<Structure> Structure::create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) {
    if (type == WALL) {
        std::unique_ptr<ImageShape> base = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0, 0), proportional(0.8, 0.8), sf::Color(60, 60, 60));
        base->addRectangleShape(proportional(0, 0), proportional(0.4, 0.4), sf::Color(100, 100, 100));
        return std::make_unique<Structure>(type, topLeft, std::move(base));
    }
    if (type == CANNON) {

        std::unique_ptr<ImageShape> base = std::make_unique<ImageShape>();
        std::unique_ptr<ImageShape> tower = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0, 0), proportional(13.f / 15.f, 13.f / 15.f), sf::Color(150, 150, 150));
        base->addCircleShape(proportional(0, 0), proportionalX(0.36f), sf::Color(160, 82, 45));
        tower->addCircleShape(proportional(0, 0), proportionalX(0.15f), sf::Color(90, 90, 90));
        tower->addRectangleShape(proportional(0, 0.25f), proportional(0.3f, 0.5f), sf::Color(90, 90, 90));
        tower->addRectangleShape(proportional(0, 0.5f - 1.f / 30.f), proportional(1.f / 3.f, 1.f / 15.f), sf::Color(110, 110, 110));
        auto structure = std::make_unique<Structure>(type, topLeft, std::move(base));
        structure->addTower(std::move(tower));
        return structure;
    }
    if (type == ARCHER_TOWER) return std::make_unique<ArcherTower>(type, topLeft, drawPosition, drawSize);
    if (type == MORTAR) return std::make_unique<Mortar>(type, topLeft, drawPosition, drawSize);

    return nullptr;
}

void Structure::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw(*baseImage, states);
    if (tower) {
        target.draw(*tower.value(), states);
    }
}

void Structure::update(sf::Time deltaTime) {
    if (health < EPS) {
        toDelete = true;
    }
    if (tower) {
        tower.value()->update(deltaTime);
    }
}

void Structure::initDraw(sf::Vector2f drawSize, sf::Vector2f position) {
    baseImage->init(drawSize, position);
    if (tower) {
        tower.value()->initDraw(drawSize, position);
    }
}

void Structure::addTower(std::unique_ptr<ImageShape> image) {
    tower = std::make_unique<Tower>(std::move(image));
}
