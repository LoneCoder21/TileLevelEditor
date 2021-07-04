#include <unordered_map>
#include <string>
#include <tuple>

#include "SFML\Graphics.hpp"

#include "TileSet.h"
#include "Grid.h"

struct TileData
{
	bool placed=0;
	sf::FloatRect selection;
};

class LayeredTileMap : public sf::Drawable, public sf::Transformable
{
public:
	LayeredTileMap(sf::RenderWindow& win, TileSet& set, const std::string& filename, const sf::Vector2i& count, int layerCount=1);
	~LayeredTileMap();

	void fillTileRange(const sf::IntRect& rect);
	void fillTiles();
	void updateTile(const sf::Vector2f& mp);

public:
	sf::Vector2i mouseToCoordinate(const sf::Vector2f& mp) const;

	void placeTile(const sf::Vector2i& index);

	bool grid_enable = 1;

	RenderGrid grid;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &set->tile_texture;

		target.draw(varray, states);

		//if (grid_enable)
		//	target.draw(grid, states);
	}

	int layer=0;
	TileSet* set;
private:
	int layerCount;

	std::vector<TileData> tiles;
	sf::VertexArray varray;

	sf::RenderWindow& window;

	std::string filename;
	sf::Vector2i tilesize;
};