#pragma once

#include "structure.hpp"

class Bullet : public sf::Drawable {
protected:
    Sergei &sergei;
    Structure::Type type;
    std::unique_ptr<sf::CircleShape> shape;
    float speed;
    float damage;
    bool toDelete;
    sf::Vector2f getPosition() { return shape->getPosition(); }

public:
    static std::unique_ptr<Bullet> create(Sergei &sergei, Structure::Type type, std::size_t targetIndex);

    Bullet(Sergei &sergei, Structure::Type type, float speed, float damage, sf::Color color);

    bool getToDelete() { return toDelete; }
    virtual void initDraw(float radius, sf::Vector2f position);
    virtual void update(sf::Time deltaTime) = 0;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

class BulletSingle : public Bullet {
private:
    std::size_t targetIndex;

public:
    BulletSingle(Sergei &sergei, Structure::Type type, std::size_t targetIndex, float speed, float damage, sf::Color color);
    void update(sf::Time deltaTime) override;
};

class BulletSplash : public Bullet {
private:
    sf::Vector2f targetPosition;
    float rangeMultiplier;
    float splashRadius;

public:
    BulletSplash(Sergei &sergei, Structure::Type type, std::size_t targetIndex, float speed, float damage, sf::Color color, float rangeMultiplier);
    void initDraw(float radius, sf::Vector2f position) override;
    void update(sf::Time deltaTime) override;
};
