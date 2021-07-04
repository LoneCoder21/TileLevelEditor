#include "SFML\Graphics.hpp"
#include "Tilemap.h"
#include "SelectionScheme.h"
#include "RectangleSelect.h"

#pragma once

class LazyLayerMap
{
public:
	LazyLayerMap(sf::RenderWindow& window, const std::string& tileset, float stepgrid, const sf::Vector2i& count, int layerCount=1);

	void saveToFile(const std::string& name);
	void update(const sf::Event& event);
	void draw();

	int current_layer = 0;
private:
	sf::RenderWindow& window;
	RectangleSelect rect_select;
	TileSet mainset;
	std::vector<TileMap> maps;
	RenderGrid grid;

	bool grid_enable = 1;
	bool set_view = 1;
};