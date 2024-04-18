#include "Dot.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main()
{
    // The higher it is, the farther the dot connects
    int connectForce = 100;
    // Speed
    float speed = 5.f;

    bool paused = false;

     auto window = sf::RenderWindow{{1440u, 900u}, "Dot Network SFML",  sf::Style::Titlebar};
    //sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0],
    //                       "Fullscreen SFML Window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    square.setFillColor(sf::Color::Green);

    std::vector<Dot> dots;

    bool isDragging = false;
    bool pPressed = false;
    bool rPressed = false;

    sf::Clock clock;
    float lastTime = 0;

    sf::Font font;
    if (!font.loadFromFile("Aileron-Regular.otf")) {
        std::cout << "Problem loading font." << std::endl;
        return 1;
    }
    sf::Text text;

    // Setting up the text display
    text.setFont(font);
    text.setString("FPS : ");
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    while (window.isOpen()) {

        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        lastTime = currentTime;

        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    dots.emplace_back(mousePos.x, mousePos.y);
                    isDragging = true;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
            }

            if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                dots.emplace_back(mousePos.x, mousePos.y);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                connectForce += 10;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                connectForce -= 10;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                speed += 0.1f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                speed -= 0.1f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                if(!pPressed) paused = !paused;
                pPressed = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                if(!rPressed) speed *= -1.f;
                rPressed = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                dots.clear();
            }
        }

        window.clear();

        for (auto &dot : dots) {
            if (!paused)
                dot.move(window, speed);
            dot.draw(window);
        }

        std::string str = "FPS : ";
        std::stringstream ss;
        ss << " Dots : " << dots.size() << " | ConnectForce : " << connectForce
           << " | Speed : " << speed << " | FPS : " << fps;

        text.setString(ss.str());

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(mousePos.x, mousePos.y);

        for (int i = 0; i < dots.size(); ++i) {
            for (int j = 0; j < dots.size(); ++j) {

                if (j == i)
                    continue;

                sf::Vector2f v1 = dots[i].position;
                sf::Vector2f v2 = dots[j].position;

                int dist = distance(v1, v2); // dots[i].distance(dots[j]);

                if (dist > connectForce)
                    continue;

                int mapDist = map(dist, 0, connectForce, 255, 0);
                sf::Color color(255, 255, 255, mapDist);

                sf::Vertex p1 = sf::Vertex(sf::Vector2f(v1.x, v1.y));
                p1.color = color;
                sf::Vertex p2 = sf::Vertex(sf::Vector2f(v2.x, v2.y));
                p2.color = color;

                sf::Vertex line[] = {p1, p2};
                window.draw(line, 2, sf::Lines);
            }
        }

        window.draw(text);
        window.display();
        pPressed = false;
        rPressed = false;
    }
}