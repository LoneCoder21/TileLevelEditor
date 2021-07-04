#include <string>

#include <SFML/Graphics.hpp>
#pragma once

class TileSet : public sf::Drawable, public sf::Transformable
{
public:
	TileSet(const sf::RenderWindow& window, const std::string& filename, int grid_step_size);
	void changeTileSet(const TileSet& set);

	void updateSelection(sf::Vector2f mp);

	sf::Sprite tilesprite;
	sf::Image tile_image;
	sf::Texture tile_texture;
	int grid_step_size;

	sf::RectangleShape overlay;
	sf::FloatRect selection;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(tilesprite,states);
		target.draw(overlay,states);
	}
private:
	void CreateTileSet();

	const sf::RenderWindow& window;
	std::string filename;
};