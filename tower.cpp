#include "tower.hpp"
#include "Sergei.hpp"
#include "bullet.hpp"
#include "unit.hpp"
#include "utils.hpp"
#include <optional>
#include <vector>

Tower::Tower(std::unique_ptr<ImageShape> image, Sergei &sergei, Structure::Type type) : sergei(sergei), type(type) {
    this->image = std::move(image);
    innerRadius = Structure::getTowerRange(type).x;
    outerRadius = Structure::getTowerRange(type).y;
    reloadTime = Structure::getReloadTime(type);
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*image, states);
}

void Tower::initDraw(sf::Vector2f drawSize, sf::Vector2f position) {
    image->init(drawSize, position);
    this->position = position;
    sf::Vector2f drawData = Structure::getMuzzleLengthAndBulletRadiusFunctor(type)(drawSize);
    muzzleLength = drawData.x;
    bulletRadius = drawData.y;
}

void Tower::update(sf::Time deltaTime) {
    std::vector<std::unique_ptr<Unit>> &unitsVec = sergei.getUnitGrid().getUnitsVec();

    assert(!targetIndex || targetIndex.value() < unitsVec.size());

    curReload += deltaTime;

    if (targetIndex && (unitsVec[targetIndex.value()]->isDead() || !isInRadius(unitsVec[targetIndex.value()]->getPosition()))) {
        targetIndex = std::nullopt;
    }
    if (!targetIndex) {
        auto bestDist = INF;
        for (std::size_t i = 0; i < unitsVec.size(); ++i) {
            auto distance = distanceL2(position, (unitsVec[i])->getPosition()) / CELL_SIZE;
            if (targetIndex && unitsVec[targetIndex.value()]->isDead()) continue;
            if (distance > innerRadius - EPS && distance < outerRadius + EPS && distance < bestDist &&
                Structure::canAttack(type, (unitsVec[i])->getType()) && !unitsVec[i]->isDead()) {
                targetIndex = i;
                bestDist = distance;
                curReload = sf::Time::Zero;
            }
        }
    }
    if (targetIndex) {
        auto enemyRelativePosition = unitsVec[targetIndex.value()]->getPosition() - position;
        image->setRotation(getAngleToTarget(enemyRelativePosition));
        if (curReload > reloadTime) {
            auto bullet = Bullet::create(sergei, type, targetIndex.value());
            bullet->initDraw(bulletRadius, enemyRelativePosition / length(enemyRelativePosition) * muzzleLength + position);
            sergei.getBulletManager().add_bullet(std::move(bullet));
            curReload = sf::Time::Zero;
        }
    }
}
