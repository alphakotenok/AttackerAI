#pragma once

#include "structure.hpp"

class Bullet : public sf::Drawable {
protected:
    Sergei &sergei;
    Structure::Type type;
    std::unique_ptr<sf::CircleShape> shape;
    float speed;
    bool toDelete;
    sf::Vector2f getPosition() { return shape->getPosition(); }

public:
    Bullet(Sergei &sergei);

    bool getToDelete() { return toDelete; }
    virtual void update(sf::Time deltaTime);
    // virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

class BulletSingle : public Bullet {
private:
    std::size_t targetIndex;
};

class BulletSpash : public Bullet {
private:
    sf::Vector2f targetPosition;
};
