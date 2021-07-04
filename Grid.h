#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "SFML/Graphics/Vertex.hpp"

#include "SFML/Graphics.hpp"

#include <vector>

#pragma once

class RenderGrid : public sf::Drawable, public sf::Transformable
{
public:
	sf::Vector2f gridsize;
	float gridstep;
	float visual_width;
	sf::Color color;

public:
	RenderGrid(const sf::Vector2f& size=sf::Vector2f(0,0), float s=0, float width=1, const sf::Color& c = sf::Color::White);

	void generateGrid();

	const sf::Vertex* getData() const 
	{
		return grid.data();
	}

	int getSize() const
	{
		return grid.size();
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(getData(), getSize(), sf::Triangles, states);
	}
private:
	std::vector<sf::Vertex> grid;
};