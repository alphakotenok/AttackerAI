#pragma once

#include "image_shape.hpp"
#include "tower.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

const float EPS = 1e-4;

inline auto proportional(float a, float b) {
    return [a, b](sf::Vector2f pair) { return sf::Vector2f{pair.x * a, pair.y * b}; };
}

inline auto proportionalX(float a) {
    return [a](sf::Vector2f pair) { return pair.x * a; };
}

inline auto proportionalY(float a) {
    return [a](sf::Vector2f pair) { return pair.y * a; };
}

class Structure : public sf::Drawable {
public:
    enum Type {
        WALL,
        CANNON,
        ARCHER_TOWER,
        MORTAR,
        AIR_DEFENCE,
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

    std::unique_ptr<ImageShape> baseImage;
    std::optional<std::unique_ptr<Tower>> tower;

    bool toDelete = false;

public:
    static sf::Vector2i getGridSize(Structure::Type type);
    static float getHealth(Structure::Type type);
    static std::unique_ptr<Structure> create(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);

    Structure(Structure::Type type, sf::Vector2i topLeft, sf::Vector2f drawPosition, sf::Vector2f drawSize);
    Structure(Structure::Type type, sf::Vector2i topLeft, std::unique_ptr<ImageShape> baseImage);
    inline sf::Vector2i getTopLeft() { return topLeft; }
    inline sf::Vector2i getGridSize() { return Structure::getGridSize(type); }
    inline sf::Vector2f getDrawPosition() { return drawPosition; }
    inline void setDrawPosition(sf::Vector2f drawPosition) { this->drawPosition = drawPosition; }
    inline float getHealth() { return health; }
    inline bool getToDelete() { return toDelete; }
    inline Structure::Type getType() { return type; }
    void takeDamage(float damage);
    virtual void update(sf::Time deltaTime);
    void initDraw(sf::Vector2f drawSize, sf::Vector2f position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void addTower(std::unique_ptr<ImageShape> image);
    bool isDead() const { return health <= 0; }
};
