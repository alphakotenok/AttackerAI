#pragma once

#include "SFML/System/Vector2.hpp"
#include <cmath>

constexpr float EPS = 1e-4;
constexpr float INF = 1e10;
constexpr float CELL_SIZE = 50.f;

inline float distanceL2(sf::Vector2f p1, sf::Vector2f p2) {
    sf::Vector2f diff = p1 - p2;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
