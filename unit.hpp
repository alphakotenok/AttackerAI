#pragma once

#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class Structure;

class Unit : public sf::Drawable {
public:
    enum class Type {
        BARBARIAN,
        BALLOON
    };

    static std::unique_ptr<Unit> create(sf::Vector2f position);
    Unit(sf::Vector2f position);
    virtual ~Unit() = default;

    void setTarget(sf::Vector2f target);
    void update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>> &structures);
    void initDraw(sf::Vector2f drawSize);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void attack(Structure *structure);
    void takeDamage(float damage) { health -= damage; }
    bool isDead() const { return health < EPS; }
    float getHealth() const { return health; }
    sf::Vector2f getPosition() const { return position; }
    sf::CircleShape *getShape() const { return shape.get(); }
    inline Unit::Type getType() { return type; }

private:
    void findNearestStructure(const std::list<std::unique_ptr<Structure>> &structures);
    bool isInRange(sf::Vector2f target) const { return distanceL2(target, position) <= attackRange; }

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
    Structure *currentTarget;
    std::unique_ptr<sf::CircleShape> shape;
};
