#include "LazyLayerMap.h"
#include "Debug\SFMLDebug.h"
#include <iostream>

LazyLayerMap::LazyLayerMap(sf::RenderWindow& window, const std::string& tileset, 
	float stepgrid, const sf::Vector2i& count, int layerCount)
	: window(window), mainset(window, tileset, stepgrid)
{
    float W = window.getSize().x, H = window.getSize().y;

	for (int i = 0; i < layerCount; ++i)
	{
		maps.push_back(TileMap(window, &mainset, count));
	}

    auto bounds = maps[0].tilemap_sprite.getLocalBounds();
    auto scf = maps[0].tilemap_sprite.getScale();

    grid = RenderGrid(sf::Vector2f(bounds.width * scf.x, bounds.height * scf.y), mainset.grid_step_size * scf.x, 1, sf::Color::Red);
    grid.generateGrid();

    grid.setOrigin(sf::Vector2f(bounds.width * scf.x / 2, bounds.height * scf.y / 2));
    grid.setPosition(sf::Vector2f(W / 2, H / 2));
}

void LazyLayerMap::saveToFile(const std::string& name)
{
    sf::Image im;
    im.create(maps[0].tilemap_image.getSize().x, maps[0].tilemap_image.getSize().y, sf::Color::Black);

    for (TileMap& map : maps)
    {
        im.copy(map.tilemap_image, 0, 0, sf::IntRect(0,0,0,0), true);
    }

    im.saveToFile(name);
}

void LazyLayerMap::update(const sf::Event& event)
{
    if (event.type == sf::Event::Resized)
    {
        float W = event.size.width, H = event.size.height;

        sf::Sprite& tilesprite = mainset.tilesprite;
        const sf::Texture* tile_texture = tilesprite.getTexture();

        tilesprite.setOrigin(sf::Vector2f(tile_texture->getSize().x / 2, tile_texture->getSize().y / 2));
        tilesprite.setPosition(sf::Vector2f(W / 2, H / 2));

        const sf::FloatRect& lb_bounds = tilesprite.getLocalBounds();

        float sf = 0.9 * std::min((W / lb_bounds.width), (H / lb_bounds.height));
        tilesprite.setScale(sf, sf);

        sf::View view(sf::FloatRect(0.f, 0.f, W, H));

        window.setView(view);
    }

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::F: maps[current_layer].fillTiles(); break;
            case sf::Keyboard::Tab: set_view = !set_view; break;
            case sf::Keyboard::Q: grid_enable = !grid_enable; break;

            case sf::Keyboard::Num1: if (maps.size() >= 1) current_layer = 0; break;
            case sf::Keyboard::Num2: if (maps.size() >= 2) current_layer = 1; break;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mp = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

            if (set_view)
            {
                mainset.updateSelection(mp);
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
            sf::Vector2i left_coord = maps[current_layer].mouseToCoordinate(rect_select.selection.getPosition());
            sf::Vector2i right_coord = maps[current_layer].mouseToCoordinate(sf::Vector2f(
                rect_select.selection.getPosition().x + rect_select.selection.getSize().x,
                rect_select.selection.getPosition().y + rect_select.selection.getSize().y
            ));

            if (left_coord.x > right_coord.x)
            {
                std::swap(left_coord.x, right_coord.x);
            }

            if (left_coord.y > right_coord.y)
            {
                std::swap(left_coord.y, right_coord.y);
            }

            sf::Vector2i coord_size = right_coord - left_coord;

            maps[current_layer].fillTileRange(sf::IntRect(left_coord.x, left_coord.y, coord_size.x + 1, coord_size.y + 1));
            rect_select.updateEndPoint(rect_select.selection.getPosition());
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2f mp = sf::Vector2f(sf::Mouse::getPosition(window));

        if (!set_view)
        {
            maps[current_layer].updateTile(mp);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2f mp = sf::Vector2f(sf::Mouse::getPosition(window));

        rect_select.updateEndPoint(mp);
    }
}

void LazyLayerMap::draw()
{
    if (set_view)
    {
        window.draw(mainset);
    }
    else
    {
        for (TileMap& map : maps)
        {
            window.draw(map);
        }

        if (grid_enable)
            window.draw(grid);

        window.draw(rect_select.selection);
    }
}