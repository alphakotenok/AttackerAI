#pragma once

#include "SFML/System/Vector2.hpp"
#include <cmath>

constexpr float EPS = 1e-4;
constexpr float INF = 1e10;
constexpr float CELL_SIZE = 50.f;

inline auto proportional(float a, float b) {
    return [a, b](sf::Vector2f pair) { return sf::Vector2f{pair.x * a, pair.y * b}; };
}

inline auto proportionalX(float a) {
    return [a](sf::Vector2f pair) { return pair.x * a; };
}

inline auto proportionalY(float a) {
    return [a](sf::Vector2f pair) { return pair.y * a; };
}

inline float distanceL2(sf::Vector2f p1, sf::Vector2f p2) {
    sf::Vector2f diff = p1 - p2;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

inline float length(sf::Vector2f point) {
    return distanceL2(point, {0, 0});
}
