#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "SelectionScheme.h"
#include "RectangleSelect.h"

#pragma once

class TileInteractor
{
public:
	TileInteractor(sf::RenderWindow& window, const std::string & tileset, const std::string& saveMap, float stepgrid, const sf::Vector2i& count);

	void update(const sf::Event& event);
	void draw();
private:
	bool set_view = 1;

	sf::RenderWindow& window;

	RectangleSelect rect_select;
	TileMapSelectionScheme scheme;
	TileSet mainset;
	TileMap map;
};