#include "TileSet.h"
#include <iostream>
#include "Debug\SFMLDebug.h"

TileSet::TileSet(const sf::RenderWindow& window, const std::string& filename, int grid_step_size) : window(window), filename(filename), grid_step_size(grid_step_size)
{
	CreateTileSet();
}

void TileSet::changeTileSet(const TileSet& set)
{
	filename = set.filename;
	grid_step_size = set.grid_step_size;

	tile_texture = set.tile_texture;
	tilesprite = set.tilesprite;
	
	CreateTileSet();
}

void TileSet::CreateTileSet()
{
	int win_width = window.getSize().x;
	int win_height = window.getSize().y;

	if (!tile_image.loadFromFile(filename))
	{
		std::cout << filename << " is bad file\n";
	}

	tile_texture.loadFromImage(tile_image);

	tilesprite = sf::Sprite(tile_texture);

	tilesprite.setOrigin(sf::Vector2f(tile_texture.getSize().x / 2, tile_texture.getSize().y / 2));
	tilesprite.setPosition(sf::Vector2f(win_width / 2, win_height / 2));

	const sf::FloatRect& lb_bounds = tilesprite.getLocalBounds();

	float sf = 0.9 * std::min((win_width / lb_bounds.width), (win_height / lb_bounds.height));
	tilesprite.setScale(sf, sf);

	overlay.setSize(sf::Vector2f(grid_step_size, grid_step_size));

	const sf::FloatRect& bounds = tilesprite.getGlobalBounds();
	overlay.setOutlineColor(sf::Color(255, 140, 0));
	overlay.setOutlineThickness(2.0f);
	overlay.setFillColor(sf::Color(255, 255, 255, 80));
	overlay.scale(tilesprite.getScale());

	overlay.setPosition(sf::Vector2f(bounds.left, bounds.top));

	selection = sf::FloatRect(0, 0, grid_step_size, grid_step_size);
}

void TileSet::updateSelection(sf::Vector2f mp)
{
	const sf::FloatRect& gb_bounds = tilesprite.getGlobalBounds();

	if (!gb_bounds.contains(mp))
	{
		return;
	}

	sf::Vector2f rel_pos = sf::Vector2f(mp.x-gb_bounds.left, mp.y-gb_bounds.top);
	sf::Vector2f gsc = sf::Vector2f(tilesprite.getScale().x * grid_step_size, tilesprite.getScale().y * grid_step_size);
	sf::Vector2i coord = sf::Vector2i(rel_pos.x / gsc.x, rel_pos.y / gsc.y);

	overlay.setPosition(sf::Vector2f(gb_bounds.left + coord.x * gsc.x, gb_bounds.top + coord.y * gsc.y));

	selection = sf::FloatRect(coord.x * grid_step_size, coord.y * grid_step_size, grid_step_size, grid_step_size);
}