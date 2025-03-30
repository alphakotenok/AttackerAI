#pragma once

#include "image_shape.hpp"
#include "structure.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "structure_grid.hpp"

class Unit : public sf::Drawable {
public:
    enum class Type {
        BARBARIAN
    };

    static std::unique_ptr<Unit> create(sf::Vector2f position);
    Unit(sf::Vector2f position);
    virtual ~Unit() = default;

    void setTarget(sf::Vector2f target);
    void update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>>& structures);
    void initDraw(sf::Vector2f drawSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void attack(Structure* structure);
    bool isDead() const { return health <= 0; }
    float getHealth() const { return health; }
    sf::Vector2f getPosition() const { return position; }
    sf::CircleShape* getShape() const { return shape.get(); }

private:
    float distanceTo(sf::Vector2f point) const {
        sf::Vector2f diff = point - position;
        return std::sqrt(diff.x * diff.x + diff.y * diff.y);
    }

    void findNearestStructure(const std::list<std::unique_ptr<Structure>>& structures);
    bool isInRange(sf::Vector2f target) const { return distanceTo(target) <= attackRange; }

    sf::Vector2f position;
    sf::Vector2f drawSize;
    Type type;
    float speed;
    float health;
    float damage;
    float attackRange;
    float attackSpeed;
    float lastAttackTime;
    bool isAttacking;
    Structure* currentTarget;
    std::unique_ptr<sf::CircleShape> shape;
};
