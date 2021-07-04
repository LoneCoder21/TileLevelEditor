#include "Grid.h"

RenderGrid::RenderGrid(const sf::Vector2f& size, float s, float width, const sf::Color& c) : gridsize(size), gridstep(s), visual_width(width), color(c)
{

}

void RenderGrid::generateGrid()
{
	grid = std::vector<sf::Vertex>();

	float W = gridsize.x;
	float H = gridsize.y;

	sf::Vertex v;

	for (float i = 0.0f; i <= W; i += gridstep)
	{
		v = { sf::Vector2f(i - visual_width / 2, H) , color }; grid.push_back(v);
		v = { sf::Vector2f(i + visual_width / 2, H) , color }; grid.push_back(v);
		v = { sf::Vector2f(i + visual_width / 2, 0) , color }; grid.push_back(v);

		v = { sf::Vector2f(i + visual_width / 2, 0) , color }; grid.push_back(v);
		v = { sf::Vector2f(i - visual_width / 2, 0) , color }; grid.push_back(v);
		v = { sf::Vector2f(i - visual_width / 2, H) , color }; grid.push_back(v);
	}

	for (float i = 0.0f; i <= H; i += gridstep)
	{
		v = { sf::Vector2f(W, i - visual_width / 2) , color }; grid.push_back(v);
		v = { sf::Vector2f(W, i + visual_width / 2) , color }; grid.push_back(v);
		v = { sf::Vector2f(0, i + visual_width / 2) , color }; grid.push_back(v);

		v = { sf::Vector2f(0, i + visual_width / 2) , color }; grid.push_back(v);
		v = { sf::Vector2f(0, i - visual_width / 2) , color }; grid.push_back(v);
		v = { sf::Vector2f(W, i - visual_width / 2) , color }; grid.push_back(v);
	}
}
