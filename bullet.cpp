#include "bullet.hpp"
#include "Sergei.hpp"
#include "utils.hpp"
#include <iostream>

std::unique_ptr<Bullet> Bullet::create(Sergei &sergei, Structure::Type type, std::size_t targetIndex) {
    if (type == Structure::Type::CANNON) return std::make_unique<BulletSingle>(sergei, type, targetIndex, 4.5f, 20.f, sf::Color(90, 90, 90));
    if (type == Structure::Type::ARCHER_TOWER) return std::make_unique<BulletSingle>(sergei, type, targetIndex, 4.5f, 12.5f, sf::Color(205, 0, 77));
    if (type == Structure::Type::MORTAR) return std::make_unique<BulletSplash>(sergei, type, targetIndex, 2.f, 25.f, sf::Color(60, 60, 60), 2.f);
    if (type == Structure::Type::AIR_DEFENSE) return std::make_unique<BulletSingle>(sergei, type, targetIndex, 3.f, 110.f, sf::Color(255, 215, 0));
    return nullptr;
}

Bullet::Bullet(Sergei &sergei, Structure::Type type, float speed, float damage, sf::Color color) : sergei(sergei), speed(speed), type(type), damage(damage) {
    shape = std::make_unique<sf::CircleShape>();
    shape->setFillColor(color);
}

void Bullet::initDraw(float radius, sf::Vector2f position) {
    shape->setRadius(radius);
    shape->setPosition(position);
    shape->setOrigin(shape->getGeometricCenter());
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*shape, states);
}

void BulletSplash::initDraw(float radius, sf::Vector2f position) {
    Bullet::initDraw(radius, position);
    splashRadius = radius * rangeMultiplier;
}

BulletSingle::BulletSingle(Sergei &sergei, Structure::Type type, std::size_t targetIndex, float speed, float damage, sf::Color color) : Bullet(sergei, type, speed, damage, color), targetIndex(targetIndex) {
}

BulletSplash::BulletSplash(Sergei &sergei, Structure::Type type, std::size_t targetIndex, float speed, float damage, sf::Color color, float rangeMultiplier) : Bullet(sergei, type, speed, damage, color), rangeMultiplier(rangeMultiplier) {
    targetPosition = sergei.getUnitGrid().getUnitsVec()[targetIndex]->getPosition();
}

void BulletSingle::update(sf::Time deltaTime) {
    auto &target = sergei.getUnitGrid().getUnitsVec()[targetIndex];
    if (target->isDead()) {
        toDelete = true;
        return;
    }
    sf::Vector2f path = target->getPosition() - getPosition();
    float pathLength = length(path);
    if (pathLength <= speed * CELL_SIZE * deltaTime.asSeconds()) {
        shape->setPosition(target->getPosition());
        target->takeDamage(damage);
        toDelete = true;
        return;
    }
    shape->setPosition(getPosition() + path / pathLength * speed * CELL_SIZE * deltaTime.asSeconds());
}

void BulletSplash::update(sf::Time deltaTime) {
    sf::Vector2f path = targetPosition - getPosition();
    float pathLength = length(path);
    if (pathLength <= speed * CELL_SIZE * deltaTime.asSeconds()) {
        shape->setPosition(targetPosition);
        for (auto &unit : sergei.getUnitGrid().getUnitsVec()) {
            if (distanceL2(unit->getPosition(), getPosition()) < splashRadius) {
                unit->takeDamage(damage);
            }
        }
        toDelete = true;
        return;
    }
    shape->setPosition(getPosition() + path / pathLength * speed * CELL_SIZE * deltaTime.asSeconds());
}
