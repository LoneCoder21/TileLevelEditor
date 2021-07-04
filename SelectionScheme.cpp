#include "SelectionScheme.h"

TileMapSelectionScheme::TileMapSelectionScheme(sf::RenderWindow& window) : window(window), ind_mp(sf::Vector2f(0,0))
{

}

void TileMapSelectionScheme::update(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
//        switch (event.key.code)
//        {
//            case sf::Keyboard::Num9: type = SelectionType::INDIVIDUAL_TILE;  break;
//            case sf::Keyboard::Num0: type = SelectionType::RECTANGLE_SELECT; break;
//        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            ind_mp = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        }
        
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2f mp = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

            rect_select.setStartPoint(mp);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2f mp = sf::Vector2f(sf::Mouse::getPosition(window));

        rect_select.updateEndPoint(mp);
    }
    else
    {
        rect_select.updateEndPoint(rect_select.selection.getPosition());
    }
}