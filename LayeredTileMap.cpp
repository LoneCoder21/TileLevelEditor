#include "LayeredTileMap.h"

LayeredTileMap::LayeredTileMap(sf::RenderWindow& win, TileSet& set, const std::string& filename, const sf::Vector2i& count, int layerCount)
	:
	window(win), set(&set), filename(filename), tilesize(count), layerCount(layerCount)
{
	int total_tiles = layerCount * tilesize.y * tilesize.x;

	float W = window.getSize().x, H = window.getSize().y;

	varray = sf::VertexArray(sf::Quads, 4 * total_tiles);

	tiles.resize(total_tiles, { 0, sf::FloatRect() });

	const int gss = set.grid_step_size;

	for (int li = 0; li < layerCount; ++li)
	{
		for (int y = 0; y < tilesize.y; ++y)
		{
			for (int x = 0; x < tilesize.x; ++x)
			{
				int index = 4 * (li * tilesize.x * tilesize.y + y * tilesize.x + x);

				varray[index + 0] = sf::Vertex(sf::Vector2f(x * gss, y * gss), sf::Color(0, 0, 0, 0));
				varray[index + 1] = sf::Vertex(sf::Vector2f(x * gss, y * gss + gss), sf::Color(0, 0, 0, 0));
				varray[index + 2] = sf::Vertex(sf::Vector2f(x * gss + gss, y * gss + gss), sf::Color(0, 0, 0, 0));
				varray[index + 3] = sf::Vertex(sf::Vector2f(x * gss + gss, y * gss), sf::Color(0, 0, 0, 0));
			}
		}
	}

	float sf = 0.9 * std::min(W / (tilesize.x * gss), H / (tilesize.y * gss));

	//grid = RenderGrid(sf::Vector2f(bounds.width * scf.x, bounds.height * scf.y), set.grid_step_size * scf.x, 1, sf::Color::Red);
	//grid.generateGrid();
	//
	//grid.setOrigin(sf::Vector2f(bounds.width * scf.x / 2, bounds.height * scf.y / 2));
	//grid.setPosition(sf::Vector2f(W / 2, H / 2));
}

void LayeredTileMap::placeTile(const sf::Vector2i& coord)
{
	int index = layer * tilesize.y * tilesize.x + coord.y * tilesize.x + coord.x;

	if (tiles[index].placed == 1 && tiles[index].selection == set->selection)
	{
		return;
	}

	tiles[index].placed = 1;
	tiles[index].selection = set->selection;

	int vindex = 4 * index;

	sf::Vector2f tl = sf::Vector2f(set->selection.left, set->selection.top);
	sf::Vector2f br = sf::Vector2f(set->selection.left + set->selection.width, set->selection.top + set->selection.height);

	varray[vindex + 0] = sf::Vertex(varray[vindex + 0].position, sf::Color(255, 255, 255, 255), sf::Vector2f(tl.x, tl.y));
	varray[vindex + 1] = sf::Vertex(varray[vindex + 1].position, sf::Color(255, 255, 255, 255), sf::Vector2f(tl.x, tl.x + br.y));
	varray[vindex + 2] = sf::Vertex(varray[vindex + 2].position, sf::Color(255, 255, 255, 255), sf::Vector2f(tl.x + br.x, tl.x + br.y));
	varray[vindex + 3] = sf::Vertex(varray[vindex + 3].position, sf::Color(255, 255, 255, 255), sf::Vector2f(tl.x + br.x, tl.x));
}
