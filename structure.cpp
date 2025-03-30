#include "structure.hpp"
#include "image_shape.hpp"

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
    if (type == STORAGE_GOLD) return {3, 3};
    if (type == STORAGE_ELIXIR) return {3, 3};
    if (type == COLLECTOR_GOLD) return {3, 3};
    if (type == COLLECTOR_ELIXIR) return {3, 3};
    if (type == ARMY_CAMP) return {4, 4};
    if (type == BARRACK) return {3, 3};
    if (type == LABORATORY) return {3, 3};
    if (type == BUILDERS_HUT) return {2, 2};
    if (type == BOMB) return {1, 1};
    if (type == SPRING_TRAP) return {1, 1};
    return {0, 0};
}

float Structure::getHealth(Structure::Type type) {
    if (type == WALL) return 900;
    if (type == CANNON) return 620;
    if (type == ARCHER_TOWER) return 500;
    if (type == MORTAR) return 450;
    if (type == AIR_DEFENCE) return 850;
    if (type == TOWN_HALL) return 2100;
    if (type == CLAN_CASTLE) return 1400;
    if (type == STORAGE_GOLD) return 1700;
    if (type == STORAGE_ELIXIR) return 1700;
    if (type == COLLECTOR_GOLD) return 680;
    if (type == COLLECTOR_ELIXIR) return 680;
    if (type == ARMY_CAMP) return 310;
    if (type == BARRACK) return 470;
    if (type == LABORATORY) return 550;
    if (type == BUILDERS_HUT) return 250;
    if (type == BOMB) return 1;
    if (type == SPRING_TRAP) return 1;
    return 0;
}

std::unique_ptr<Structure> Structure::create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize) {
    std::unique_ptr<ImageShape> base = std::make_unique<ImageShape>();
    std::optional<std::unique_ptr<ImageShape>> tower;

    if (type == WALL) {
        base->addRectangleShape(proportional(0, 0), proportional(0.8, 0.8), sf::Color(90, 90, 90));
        base->addRectangleShape(proportional(0, 0), proportional(0.4, 0.4), sf::Color(120, 120, 120));
    }
    if (type == CANNON) {
        tower = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(150, 150, 150));
        base->addCircleShape(proportional(0, 0), proportionalX(0.36f), sf::Color(160, 82, 45));
        tower.value()->addCircleShape(proportional(0, 0), proportionalX(0.15f), sf::Color(90, 90, 90));
        tower.value()->addRectangleShape(proportional(0, 0.25f), proportional(0.3f, 0.5f), sf::Color(90, 90, 90));
        tower.value()->addRectangleShape(proportional(0, 0.5f - 1.f / 30.f), proportional(1.f / 3.f, 1.f / 15.f), sf::Color(110, 110, 110));
    }
    if (type == ARCHER_TOWER) {
        tower = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(0, 168, 0));
        base->addRectangleShape(proportional(0, 0), proportional(0.5f, 0.5f), sf::Color(139, 69, 19));
        base->setOutline(1, proportionalX(0.05f), sf::Color(140, 140, 140));
        tower.value()->addCircleShape(proportional(0, 0), proportionalX(0.25f), sf::Color(205, 0, 77), 3);
        tower.value()->addRectangleShape(proportional(0, 0.15f), proportional(0.12f, 0.4f), sf::Color(205, 0, 77));
    }
    if (type == MORTAR) {
        tower = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0.35f - 1.f / 30.f, 0), proportional(0.3f, 14.f / 15.f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(1.f / 30.f - 0.35f, 0), proportional(0.3f, 14.f / 15.f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(0, 0), proportional(0.7f, 0.7f), sf::Color(160, 82, 45));
        base->addCircleShape(proportional(0, 0), proportionalX(0.25f), sf::Color(90, 90, 90));
        tower.value()->addCircleShape(proportional(0, 0.1f), proportionalX(0.13f), sf::Color(30, 30, 30));
    }
    if (type == AIR_DEFENCE) {
        tower = std::make_unique<ImageShape>();
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(139, 69, 19));
        base->addCircleShape(proportional(0, 0), proportionalX(0.36f), sf::Color(140, 140, 140));
        tower.value()->addRectangleShape(proportional(0, -0.025f), proportional(0.35f, 0.25f), sf::Color(120, 0, 0));
        tower.value()->addCircleShape(proportional(0, 0), proportionalX(0.15f), sf::Color(180, 0, 0), 3);
        tower.value()->addRectangleShape(proportional(0, 0.2f), proportional(0.12f, 0.4f), sf::Color(180, 0, 0));
    }
    if (type == TOWN_HALL) {
        base->addRectangleShape(proportional(0, 0), proportional(0.95f, 0.95f), sf::Color(182, 133, 13));
        base->addRectangleShape(proportional(0, 0), proportional(0.80f, 0.55f), sf::Color(217, 164, 32));
        base->addRectangleShape(proportional(-0.3f, 0), proportional(0.025f, 0.60f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(0.3f, 0), proportional(0.025f, 0.60f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(-0.1f, 0.1f), proportional(0.12f, 0.12f), sf::Color(120, 120, 120));
        base->setOutline(4, proportionalX(0.04f), sf::Color(90, 90, 90));
    }
    if (type == CLAN_CASTLE) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(120, 120, 120));
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f - 0.4f, 14.f / 15.f - 0.4f), sf::Color(139, 69, 19));
        base->setOutline(1, proportionalX(0.05f), sf::Color(90, 90, 90));
    }
    if (type == STORAGE_GOLD) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f - 0.3f, 14.f / 15.f - 0.3f), sf::Color(255, 215, 0));
        base->setOutline(0, proportionalX(0.15f), sf::Color(150, 150, 150));
    }
    if (type == STORAGE_ELIXIR) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f - 0.3f, 14.f / 15.f - 0.3f), sf::Color(185, 9, 155));
        base->setOutline(0, proportionalX(0.15f), sf::Color(150, 150, 150));
    }
    if (type == COLLECTOR_GOLD) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(0, 168, 0));
        base->addCircleShape(proportional(0, 0), proportionalX(0.35f), sf::Color(90, 90, 90));
        base->setOutline(1, proportionalX(0.05f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(0, 0), proportional(0.3f, 0.3f), sf::Color(255, 215, 0));
    }
    if (type == COLLECTOR_ELIXIR) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(0, 168, 0));
        base->addCircleShape(proportional(0, 0), proportionalX(0.35f), sf::Color(90, 90, 90));
        base->setOutline(1, proportionalX(0.05f), sf::Color(150, 150, 150));
        base->addRectangleShape(proportional(0, 0), proportional(0.3f, 0.3f), sf::Color(185, 9, 155));
    }
    if (type == ARMY_CAMP) {
        base->addRectangleShape(proportional(0, 0), proportional(0.95f, 0.95f), sf::Color(0, 168, 0));
        base->addCircleShape(proportional(0, 0), proportionalX(0.2f), sf::Color(170, 60, 0));
        base->setOutline(1, proportionalX(0.05f), sf::Color(139, 69, 19));
        base->addCircleShape(proportional(0, 0), proportionalX(0.1f), sf::Color(215, 53, 2));
    }
    if (type == BARRACK) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f - 0.1f, 14.f / 15.f - 0.1f), sf::Color(180, 0, 0));
        base->setOutline(0, proportionalX(0.05f), sf::Color(120, 0, 0));
        base->addRectangleShape(proportional(0, 0), proportional(0.07f, 0.6f), sf::Color(200, 200, 200));
        base->setExtraRotation(1, sf::degrees(-45));
        base->addRectangleShape(proportional(0, -0.2f), proportional(0.2f, 0.07f), sf::Color(139, 69, 19));
        base->setExtraRotation(2, sf::degrees(-45));
        base->addRectangleShape(proportional(0, -0.27f), proportional(0.07f, 0.1f), sf::Color(139, 69, 19));
        base->setExtraRotation(3, sf::degrees(-45));
        base->addRectangleShape(proportional(0, 0), proportional(0.07f, 0.6f), sf::Color(200, 200, 200));
        base->setExtraRotation(4, sf::degrees(45));
        base->addRectangleShape(proportional(0, -0.2f), proportional(0.2f, 0.07f), sf::Color(139, 69, 19));
        base->setExtraRotation(5, sf::degrees(45));
        base->addRectangleShape(proportional(0, -0.27f), proportional(0.07f, 0.1f), sf::Color(139, 69, 19));
        base->setExtraRotation(6, sf::degrees(45));
    }
    if (type == LABORATORY) {
        base->addRectangleShape(proportional(0, 0), proportional(14.f / 15.f, 14.f / 15.f), sf::Color(0, 168, 0));
        base->addCircleShape(proportional(0, 0), proportionalX(0.35f), sf::Color(200, 200, 200), 8);
        base->setOutline(1, proportionalX(0.1f), sf::Color(139, 69, 19));
        base->setExtraRotation(1, sf::degrees(360.f / 16.f));
        base->addCircleShape(proportional(0, 0), proportionalX(0.15f), sf::Color(30, 30, 30), 8);
    }
    if (type == BUILDERS_HUT) {
        base->addRectangleShape(proportional(0, 0), proportional(0.8f, 0.8f), sf::Color(30, 30, 30));
        base->setOutline(0, proportionalX(0.05f), sf::Color(200, 200, 200));
        base->addRectangleShape(proportional(0, 0), proportional(0.1f, 0.5f), sf::Color(200, 200, 200));
        base->setExtraRotation(1, sf::degrees(-45));
        base->addRectangleShape(proportional(0, 0), proportional(0.05f, 0.5f), sf::Color(139, 69, 19));
        base->setExtraRotation(2, sf::degrees(45));
        base->addRectangleShape(proportional(0, 0.25f), proportional(0.2f, 0.15f), sf::Color(200, 200, 200));
        base->setExtraRotation(3, sf::degrees(45));
    }
    if (type == BOMB) {
        base->addCircleShape(proportional(0, 0), proportionalX(0.35f), sf::Color(30, 30, 30));
        base->setOutline(0, proportionalX(0.05f), sf::Color(90, 90, 90));
        base->addCircleShape(proportional(0, 0.2f), proportionalX(0.1f), sf::Color(182, 34, 3));
        base->setExtraRotation(1, sf::degrees(45));
    }
    if (type == SPRING_TRAP) {
        base->addRectangleShape(proportional(0, 0), proportional(0.60f, 0.60f), sf::Color(211, 160, 59));
        base->setOutline(0, proportionalX(0.1f), sf::Color(160, 82, 45));
    }
    auto structure = std::make_unique<Structure>(type, topLeft, std::move(base));
    if (tower) {
        tower.value()->setRotation(sf::degrees(rand()));
        structure->addTower(std::move(tower.value()));
    }
    return structure;
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
