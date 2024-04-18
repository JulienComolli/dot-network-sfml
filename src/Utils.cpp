#include "SFML/System/Vector2.hpp"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    return toLow +
           (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}

int distance(sf::Vector2f v1, sf::Vector2f v2)
{
    return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
}