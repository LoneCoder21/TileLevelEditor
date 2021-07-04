#include <unordered_map>
#include <string>
#include <tuple>

#include "SFML\Graphics.hpp"

#include "TileSet.h"
#include "Grid.h"

#pragma once

struct TileData
{
	bool placed;
	sf::FloatRect selection;
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::RenderWindow& win, TileSet* set, const sf::Vector2i& count);

	void fillTileRange(const sf::IntRect& rect);
	void fillTiles();
	void updateTile(const sf::Vector2f& mp);
public:
	sf::Vector2i mouseToCoordinate(const sf::Vector2f& mp) const;
	void placeTile(const sf::Vector2i& index);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(tilemap_sprite, states);
	}

	TileSet* set;
	sf::Sprite tilemap_sprite;
	sf::Image tilemap_image;
private:
	std::vector<TileData> placed_tiles;

	sf::Texture tilemap_texture;
	sf::RenderWindow& window;
	
	sf::Vector2i tilesize;
};