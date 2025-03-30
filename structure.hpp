#pragma once

#include "image_shape.hpp"
#include "unit.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Tower;

class Sergei;

class Structure : public sf::Drawable {
public:
    enum Type {
        WALL,
        CANNON,
        ARCHER_TOWER,
        MORTAR,
        AIR_DEFENSE,
        TOWN_HALL,
        CLAN_CASTLE,
        STORAGE_GOLD,
        STORAGE_ELIXIR,
        COLLECTOR_GOLD,
        COLLECTOR_ELIXIR,
        ARMY_CAMP,
        BARRACK,
        LABORATORY,
        BUILDERS_HUT,
        BOMB,
        SPRING_TRAP
    };

protected:
    sf::Vector2i topLeft;
    Structure::Type type;
    float health;

    sf::Vector2f drawPosition;
    sf::Vector2f drawSize;

    Sergei &sergei;

    std::unique_ptr<ImageShape> baseImage;
    std::optional<std::unique_ptr<Tower>> tower;

    bool toDelete = false;

public:
    static sf::Vector2i getGridSize(Structure::Type type);
    static float getHealth(Structure::Type type);
    static sf::Vector2f getTowerRange(Structure::Type type);
    static float getDamage(Structure::Type type);
    static sf::Time getReloadTime(Structure::Type type);
    static std::function<sf::Vector2f(sf::Vector2f)> getMuzzleLengthAndBulletRadiusFunctor(Structure::Type type);
    static std::unique_ptr<Structure> create(Structure::Type type, Sergei &sergei, sf::Vector2i topLeft);
    static bool canAttack(Structure::Type strType, Unit::Type unitType);

    Structure(Structure::Type type, Sergei &sergei, sf::Vector2i topLeft, std::unique_ptr<ImageShape> baseImage);
    inline sf::Vector2i getTopLeft() { return topLeft; }
    inline sf::Vector2i getGridSize() { return Structure::getGridSize(type); }
    inline sf::Vector2f getDrawPosition() { return drawPosition; }
    inline float getHealth() { return health; }
    inline bool getToDelete() { return toDelete; }
    inline Structure::Type getType() { return type; }
    void takeDamage(float damage);
    virtual void update(sf::Time deltaTime);
    void initDraw(sf::Vector2f drawSize, sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void addTower(std::unique_ptr<ImageShape> image, Type type);
    bool isDead() const { return health < EPS; }
};
