#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/System/Vector2.hpp>

int randomInt(int min, int max);

float map(float value, float fromLow, float fromHigh, float toLow,
          float toHigh);

int distance(sf::Vector2f v1, sf::Vector2f v2);

#endif