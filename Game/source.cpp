#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Baby's First game" );
    window.setPosition(sf::Vector2i(150, 50));
    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen())
    {
        //std::cout << clock.getElapsedTime().asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout << "Left Click " << std::endl;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                std::cout << "Not Left click " << std::endl;

        }
    }

    return 0;
}
