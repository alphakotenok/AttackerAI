#include "unit.hpp"
#include "structure.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>
#include <queue>

std::unique_ptr<Unit> Unit::create(sf::Vector2f position) {
    return std::make_unique<Unit>(position);
}

Unit::Unit(sf::Vector2f position)
    : position(position), isAttacking(false), type(Type::BARBARIAN), currentTarget(nullptr) {

    if (type == Type::BARBARIAN) {
        speed = 100;
        health = 65;
        damage = 14;
        attackRange = 2;
        attackSpeed = 1;
        lastAttackTime = 0;

        shape = std::make_unique<sf::CircleShape>();
        shape->setFillColor(sf::Color::Red);
    } else {
        throw std::invalid_argument("Not yet implemented lmao we only got stupid barbarians rn");
    }
}

void Unit::update(sf::Time deltaTime, const std::list<std::unique_ptr<Structure>> &structures) {
    if (!currentTarget || currentTarget->isDead()) {
        findNearestStructure(structures);
    }

    if (currentTarget) {
        sf::Vector2f targetPos = currentTarget->getDrawPosition();
        float distToTarget = distanceL2(position, targetPos);

        if (distToTarget <= attackRange) {
            if (!isAttacking) {
                currentTarget->takeDamage(damage);
                isAttacking = true;
                lastAttackTime = 0.0f;
                shape->setFillColor(sf::Color::Yellow);
            }
        } else {
            sf::Vector2f direction = (sf::Vector2f{path.back()} * CELL_SIZE / 5.0f - sf::Vector2f{1125.0f, 1125.0f}) - position;
            path.pop_back();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) {
                direction = direction / length;
                position += direction * speed / 60.0f;
                shape->setPosition(position);
                shape->setFillColor(sf::Color::Red);
            }
        }
    }

    if (isAttacking) {
        lastAttackTime += deltaTime.asSeconds();
        if (lastAttackTime >= 1.0f / attackSpeed) {
            isAttacking = false;
            lastAttackTime = 0;
        }
    }
    shape->setPosition(position);
}

// void Unit::findNearestStructure(const std::list<std::unique_ptr<Structure>> &structures) {
//     float minDist = std::numeric_limits<float>::max();
//     Structure *nearest = nullptr;

//     for (const auto &structure : structures) {
//         if (!structure || structure->isDead()) continue;

//         float dist = distanceL2(position, structure->getDrawPosition());
//         if (dist < minDist) {
//             minDist = dist;
//             nearest = structure.get();
//         }
//     }

//     currentTarget = nearest;
// }

inline sf::Vector2i fromGameToDijkstraCoords(sf::Vector2i position) {
    return {position.x * 5, position.y * 5};
}

inline sf::Vector2i fromGameToDijkstraCoords(sf::Vector2f position) {
    return {static_cast<int>(position.x * 5), static_cast<int>(position.y * 5)};
}

inline sf::Vector2f fromDijkstraToGameCoords(std::pair<int, int> coords) {
    return {static_cast<float>(coords.first) / 5.0f, static_cast<float>(coords.second) / 5.0f};
}

void Unit::findNearestStructure(const std::list<std::unique_ptr<Structure>> &structures) {
    int minDist = std::numeric_limits<int>::max();
    Structure *nearest = nullptr;

    const sf::Vector2i gridSize = {45, 45};

    std::vector<std::vector<Structure *>> structMap(gridSize.x * 5, std::vector<Structure *>(gridSize.y * 5, nullptr));

    for (const auto &structure : structures) {
        if (!structure || structure->isDead()) continue;

        auto dijkstraCoords = fromGameToDijkstraCoords(structure->getTopLeft());
        auto structSize = structure->getGridSize();
        // std::cout << structSize.x << structSize.y << std::endl;
        //  std::cout << structure->getTopLeft().x << " " << structure->getTopLeft().y << "\n";
        for (int dx = 0; dx < 5 * structSize.x; ++dx) {
            for (int dy = 0; dy < 5 * structSize.y; ++dy) {
                structMap[dijkstraCoords.x + dx][dijkstraCoords.y + dy] = structure.get();
            }
        }
    }

    std::vector<std::vector<int>> distMap(gridSize.x * 5, std::vector<int>(gridSize.y * 5, std::numeric_limits<int>::max()));
    // std::cout << position.x << " " << position.y << "\n";
    auto posToStart = fromGameToDijkstraCoords((position + sf::Vector2f{1125.0f, 1125.0f}) / CELL_SIZE);
    // std::cout << posToStart.x << " " << posToStart.y << "\n";
    distMap[posToStart.x][posToStart.y] = 0;

    auto compare = [](const std::pair<int, sf::Vector2i> &a, const std::pair<int, sf::Vector2i> &b) { return a.first > b.first; };
    std::priority_queue<std::pair<int, sf::Vector2i>, std::vector<std::pair<int, sf::Vector2i>>, decltype(compare)> q(compare);
    q.push({0, posToStart});

    while (!q.empty()) {
        auto [dist, coords] = q.top();
        q.pop();

        if (dist == std::numeric_limits<int>::max()) break;

        if (dist > distMap[coords.x][coords.y]) continue;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                if (coords.x + dx < 0 || coords.x + dx >= gridSize.x * 5 ||
                    coords.y + dy < 0 || coords.y + dy >= gridSize.y * 5) {
                    continue;
                }

                int newDist = dist + 1;

                if (newDist < distMap[coords.x + dx][coords.y + dy]) {
                    distMap[coords.x + dx][coords.y + dy] = newDist;
                    q.push({newDist, {coords.x + dx, coords.y + dy}});
                }
            }
        }
    }

    sf::Vector2i attackCell = {-1, -1};
    for (int i = 0; i < gridSize.x * 5; ++i) {
        for (int j = 0; j < gridSize.y * 5; ++j) {
            if (distMap[i][j] < minDist && structMap[i][j] != nullptr) {
                minDist = distMap[i][j];
                nearest = structMap[i][j];
                attackCell = {i, j};
            }
        }
    }

    currentTarget = nearest;

    path.clear();
    if (currentTarget) {
        while (attackCell != posToStart) {
            path.push_back(attackCell);
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (distMap[attackCell.x + dx][attackCell.y + dy] < distMap[attackCell.x][attackCell.y]) {
                        attackCell = {attackCell.x + dx, attackCell.y + dy};
                    }
                }
            }
        }
        // std::reverse(path.begin(), path.end());
    }
}

void Unit::initDraw(sf::Vector2f drawSize) {
    this->drawSize = drawSize;
    shape->setRadius(drawSize.x * 0.5f);
    shape->setOrigin(shape->getGeometricCenter());
}

void Unit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (shape) {
        target.draw(*shape, states);
    }
}

void Unit::attack(Structure *structure) {
    if (!structure || structure->isDead()) return;

    sf::Vector2f structurePos = structure->getDrawPosition();
    float distToTarget = distanceL2(position, structurePos);

    if (distToTarget <= attackRange) {
        if (!isAttacking) {
            structure->takeDamage(damage);
            isAttacking = true;
            lastAttackTime = 0.0f;
            shape->setFillColor(sf::Color::Yellow);
        }
    } else {
        sf::Vector2f direction = (sf::Vector2f{path.back()} * CELL_SIZE / 5.0f - sf::Vector2f{1125.0f, 1125.0f}) - position;
        path.pop_back();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction = direction / length;
            position += direction * speed / 60.0f;
            shape->setPosition(position);
            shape->setFillColor(sf::Color::Red);
        }
    }
}
