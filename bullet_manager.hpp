#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Bullet;

class BulletManager : public sf::Drawable {
private:
    std::list<std::unique_ptr<Bullet>> bullets;

public:
    BulletManager();
    void add_bullet(std::unique_ptr<Bullet> bullet);
    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
