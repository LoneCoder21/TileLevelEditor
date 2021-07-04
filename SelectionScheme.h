#include <SFML\Graphics.hpp>
#include "RectangleSelect.h"
#pragma once

enum class SelectionType : short
{
	INDIVIDUAL_TILE,
	RECTANGLE_SELECT
};

class TileMapSelectionScheme
{
public:
	void update(const sf::Event& event);

	TileMapSelectionScheme(sf::RenderWindow& window);

	RectangleSelect rect_select;
private:
	sf::RenderWindow& window;

	sf::Vector2f ind_mp;
};