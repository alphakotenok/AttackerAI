#include "bullet_manager.hpp"
#include "bullet.hpp"

BulletManager::BulletManager() {}

void BulletManager::add_bullet(std::unique_ptr<Bullet> bullet) {
    bullets.push_back(std::move(bullet));
}

void BulletManager::update(sf::Time deltaTime) {
    for (auto &bullet : bullets) {
        bullet->update(deltaTime);
    }
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [](auto &bullet) { return bullet->getToDelete(); }),
        bullets.end());
}

void BulletManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &bullet : bullets) {
        target.draw(*bullet, states);
    }
}
