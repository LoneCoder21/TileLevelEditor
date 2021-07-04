#include "Tilemap.h"
#include <iostream>

TileMap::TileMap(sf::RenderWindow& win, TileSet* set, const sf::Vector2i& count) :
	set(set), window(win), tilesize(count)
{
	const int W = window.getSize().x, H = window.getSize().y;

	placed_tiles.resize(count.x * count.y, {0, sf::FloatRect()});

	tilemap_image.create(count.x * set->grid_step_size, count.y * set->grid_step_size, sf::Color(0,0,0,0));
	tilemap_texture.create(count.x * set->grid_step_size, count.y * set->grid_step_size);

	tilemap_sprite.setTexture(tilemap_texture);

	const sf::FloatRect& lb_bounds = tilemap_sprite.getLocalBounds();

	float sf = 0.9 * std::min((W / lb_bounds.width), (H / lb_bounds.height));

	sf::Vector2f scf = sf::Vector2f(sf, sf);

	tilemap_sprite.setScale(scf);

	const sf::FloatRect& bounds = tilemap_sprite.getLocalBounds();
	
	tilemap_sprite.setPosition(sf::Vector2f(W/2,H/2));
	tilemap_sprite.setOrigin(sf::Vector2f(bounds.width/2, bounds.height/2));
	tilemap_sprite.setColor(sf::Color(255,255,255,0));

	tilemap_texture.update(tilemap_image);
}

void TileMap::fillTileRange(const sf::IntRect& rect)
{
	for (int y = std::max(0, rect.top); y < std::min(rect.top + rect.height, tilesize.y); ++y)
	{
		for (int x = std::max(0, rect.left); x < std::min(rect.left + rect.width, tilesize.x); ++x)
		{
			placeTile(sf::Vector2i(x, y));
		}
	}
}

void TileMap::fillTiles()
{
	fillTileRange(sf::IntRect(0, 0, tilesize.x, tilesize.y));
}

sf::Vector2i TileMap::mouseToCoordinate(const sf::Vector2f& mp) const
{
	const sf::FloatRect& gb_bounds = tilemap_sprite.getGlobalBounds();

	sf::Vector2f rel_pos = sf::Vector2f(mp.x - gb_bounds.left, mp.y - gb_bounds.top);
	sf::Vector2f gsc = sf::Vector2f(tilemap_sprite.getScale().x * set->grid_step_size, tilemap_sprite.getScale().y * set->grid_step_size);
	sf::Vector2i coord = sf::Vector2i(rel_pos.x / gsc.x, rel_pos.y / gsc.y);

	return coord;
}

void TileMap::placeTile(const sf::Vector2i& coord)
{
	if (placed_tiles[coord.y * tilesize.x + coord.x].placed == 1 && placed_tiles[coord.y * tilesize.x + coord.x].selection == set->selection)
	{
		return;
	}

	placed_tiles[coord.y * tilesize.x + coord.x].placed = 1;
	placed_tiles[coord.y * tilesize.x + coord.x].selection = set->selection;

	tilemap_image.copy(set->tile_image, set->grid_step_size * coord.x, set->grid_step_size * coord.y, sf::IntRect(set->selection));
	tilemap_texture.update(tilemap_image);

	tilemap_sprite.setTexture(tilemap_texture);
	tilemap_sprite.setColor(sf::Color(255, 255, 255, 255));
}

void TileMap::updateTile(const sf::Vector2f& mp)
{
	const sf::FloatRect& gb_bounds = tilemap_sprite.getGlobalBounds();

	if (!gb_bounds.contains(mp))
	{
		return;
	}

	placeTile(mouseToCoordinate(mp));
}