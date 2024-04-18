#ifndef DOT_HPP
#define DOT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

#include "SFML/Graphics/RenderWindow.hpp"
#include "Utils.hpp"

class Dot {
  public:
    Dot(float x, float y, float radius = 5.f, float speed = 5.f)
        : position(x, y), radius(radius)
    {
        dot.setRadius(radius);
        sf::Color color(255, 255, 255, 128);
        dot.setFillColor(color);
        dot.setOrigin(radius, radius); // Set origin to center of the dot
        dot.setPosition(position);
        this->velocity.x = (float)randomInt(-100, 100) / 100;
        this->velocity.y = (float)randomInt(-100, 100) / 100;
        this->speed = speed;
        this->radius = radius;
    }

    void draw(sf::RenderWindow &window) { window.draw(dot); }

    void setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
        dot.setPosition(position);
    }

    int distance(Dot d)
    {
        return std::sqrt(std::pow(this->position.x - d.position.x, 2) +
                         std::pow(this->position.y - d.position.y, 2));
    }

    void move(sf::RenderWindow &window, float owSpeed = -1000.f)
    {
        if(owSpeed < -999.f) owSpeed = this->speed;

        this->velocity.x *= (this->offLimitX(window) ? -1 : 1);
        this->velocity.y *= (this->offLimitY(window) ? -1 : 1);

        this->position.x += (this->velocity.x * owSpeed);
        this->position.y += (this->velocity.y * owSpeed);
        dot.setPosition(position);
    }

    bool offLimitY(sf::RenderWindow &window)
    {
        return this->position.y > window.getSize().y || this->position.y < 0;
    }

    bool offLimitX(sf::RenderWindow &window)
    {
        return this->position.x > window.getSize().x || this->position.x < 0;
    }

    sf::CircleShape dot;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    float speed;
};

#endif