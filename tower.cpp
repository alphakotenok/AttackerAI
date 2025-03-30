#include "tower.hpp"
#include "Sergei.hpp"
#include "unit.hpp"
#include "utils.hpp"
#include <optional>
#include <vector>

Tower::Tower(std::unique_ptr<ImageShape> image, Sergei &sergei, float innerRadius, float outerRadius, Structure::Type type) : sergei(sergei), innerRadius(innerRadius), outerRadius(outerRadius), type(type) {
    this->image = std::move(image);
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*image, states);
}

void Tower::initDraw(sf::Vector2f drawSize, sf::Vector2f position) {
    image->init(drawSize, position);
    this->position = position;
}

void Tower::update(sf::Time deltaTime) {
    std::vector<std::unique_ptr<Unit>> &unitsVec = sergei.getUnitGrid().getUnitsVec();

    assert(!targetIndex || targetIndex.value() < unitsVec.size());

    if (targetIndex && (unitsVec[targetIndex.value()]->isDead() || !isInRadius(unitsVec[targetIndex.value()]->getPosition()))) {
        targetIndex = std::nullopt;
    }
    if (!targetIndex) {
        auto bestDist = INF;
        for (std::size_t i = 0; i < unitsVec.size(); ++i) {
            auto distance = distanceL2(position, (unitsVec[i])->getPosition()) / CELL_SIZE;
            if (targetIndex && unitsVec[targetIndex.value()]->isDead()) continue;
            if (distance > innerRadius - EPS && distance < outerRadius + EPS && distance < bestDist && Structure::canAttack(type, (unitsVec[i])->getType())) {
                targetIndex = i;
                bestDist = distance;
            }
        }
    }
    if (targetIndex) {
        image->setRotation(getAngleToTarget(unitsVec[targetIndex.value()]->getPosition() - position));
    }
}
