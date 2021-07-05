#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include "LazyLayerMap.h"
#include "DebugTools\SFMLDebug.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1100, 700), "Level Editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    const int stepgrid = 32;
    const auto count = sf::Vector2i(15, 20);

    LazyLayerMap layermap(window, "res\\set2.png", stepgrid, count, 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            layermap.update(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Green);
        
        layermap.draw();
        window.display();
    }

    layermap.saveToFile("res\\GeneratedMap.png");
    return 0;
}