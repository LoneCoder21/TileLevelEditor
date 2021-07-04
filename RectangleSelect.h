#include <SFML/Graphics.hpp>
#pragma once

class RectangleSelect
{
public:
	RectangleSelect();

	void setStartPoint(const sf::Vector2f& point);
	void updateEndPoint(const sf::Vector2f& point);

	sf::RectangleShape selection;
private:
	
};