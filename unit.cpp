#include "unit.hpp"
#include "structure.hpp"
#include "utils.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

std::unique_ptr<Unit> Unit::create(sf::Vector2f position) {
    return std::make_unique<Unit>(position);
}

Unit::Unit(sf::Vector2f position)
    : position(position), isAttacking(false), type(Type::BARBARIAN), currentTarget(nullptr) {
    
    if (type == Type::BARBARIAN) {
        speed = 100;
        health = 100;
        damage = 200;
        attackRange = 2;
        attackSpeed = 1;
        lastAttackTime = 0;

        shape = std::make_unique<sf::CircleShape>();
        shape->setFillColor(sf::Color::Red);
    } else {
        throw std::invalid_argument("Not yet implemented lmao we only got stupid barbarians rn");
    }
}

void Unit::update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>>& structures) {
    if (!currentTarget || currentTarget->isDead()) {
        findNearestStructure(structures);
    }

    if (currentTarget) {
        sf::Vector2f targetPos = currentTarget->getDrawPosition();
        float distToTarget = distanceTo(targetPos);
        
        if (distToTarget <= attackRange) {
            if (!isAttacking) {
                currentTarget->takeDamage(damage);
                isAttacking = true;
                lastAttackTime = 0.0f;
                shape->setFillColor(sf::Color::Yellow);
            }
        } else {
            sf::Vector2f direction = targetPos - position;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) {
                direction = direction / length;
                position += direction * speed * deltaTime.asSeconds();
                shape->setPosition(position);
                shape->setFillColor(sf::Color::Red);
            }
        }
    }

    if (isAttacking) {
        lastAttackTime += deltaTime.asSeconds();
        if (lastAttackTime >= 1.0f / attackSpeed) {
            isAttacking = false;
            lastAttackTime = 0;
        }
    }
    shape->setPosition(position);
}

void Unit::findNearestStructure(const std::list<std::unique_ptr<Structure>>& structures) {
    float minDist = std::numeric_limits<float>::max();
    Structure* nearest = nullptr;

    for (const auto& structure : structures) {
        if (!structure || structure->isDead()) continue;
        
        float dist = distanceTo(structure->getDrawPosition());
        if (dist < minDist) {
            minDist = dist;
            nearest = structure.get();
        }
    }

    currentTarget = nearest;
}

void Unit::initDraw(sf::Vector2f drawSize) {
    this->drawSize = drawSize;
    shape->setRadius(drawSize.x * 0.5f);
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (shape) {
        target.draw(*shape, states);
    }
}

void Unit::attack(Structure* structure) {
    if (!structure || structure->isDead()) return;

    sf::Vector2f structurePos = structure->getDrawPosition();
    float distToTarget = distanceTo(structurePos);
    
    if (distToTarget <= attackRange) {
        if (!isAttacking) {
            structure->takeDamage(damage);
            isAttacking = true;
            lastAttackTime = 0.0f;
            shape->setFillColor(sf::Color::Yellow);
        }
    } else {
        sf::Vector2f direction = structurePos - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction = direction / length;
            position += direction * speed / 60.0f; 
            shape->setPosition(position);
            shape->setFillColor(sf::Color::Red);
        }
    }
}

void Unit::takeDamage(float damage) {
    health -= damage;
    if (health <= EPS) {
        isDead = true;
    }
}