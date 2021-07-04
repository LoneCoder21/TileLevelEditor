#include "TileInteractor.h"
#include <iostream>
#include "Debug/SFMLDebug.h"
#include <algorithm>

TileInteractor::TileInteractor(sf::RenderWindow& window, const std::string& tileset, const std::string& saveMap, float stepgrid, const sf::Vector2i& count)
	: window(window), mainset(TileSet(window, tileset, stepgrid)), map(window, &mainset, count), scheme(window)
{
    
}

void TileInteractor::update(const sf::Event& event)
{
    //scheme.update(event);

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::F: map.fillTiles(); break;
            case sf::Keyboard::Tab: set_view = !set_view; break;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mp = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

            if (set_view)
            {
                map.set->updateSelection(mp);
            }
        }

        if (event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2f mp = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

            rect_select.setStartPoint(mp);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            std::cout << "RIGHT RELEASED\n\n";
            sf::Vector2i left_coord = map.mouseToCoordinate(rect_select.selection.getPosition());
            sf::Vector2i right_coord = map.mouseToCoordinate(sf::Vector2f(
                rect_select.selection.getPosition().x + rect_select.selection.getSize().x,
                rect_select.selection.getPosition().y + rect_select.selection.getSize().y
            ));

            SFML_PRINT(left_coord);
            SFML_PRINT(right_coord);

            if (left_coord.x > right_coord.x)
            {
                std::swap(left_coord.x, right_coord.x);
            }

            if (left_coord.y > right_coord.y)
            {
                std::swap(left_coord.y, right_coord.y);
            }

            sf::Vector2i coord_size = right_coord - left_coord;

            map.fillTileRange(sf::IntRect(left_coord.x, left_coord.y, coord_size.x+1, coord_size.y+1));
            rect_select.updateEndPoint(rect_select.selection.getPosition());
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2f mp = sf::Vector2f(sf::Mouse::getPosition(window));

        if (!set_view)
        {
            map.updateTile(mp);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2f mp = sf::Vector2f(sf::Mouse::getPosition(window));

        rect_select.updateEndPoint(mp);
    }
}

void TileInteractor::draw()
{
    if (set_view)
    {
        window.draw(*map.set);
    }
    else
    {
        //window.draw(map);
        window.draw(rect_select.selection);
    }    
}