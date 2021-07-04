#include "RectangleSelect.h"
#include <iostream>

RectangleSelect::RectangleSelect()
{
	selection.setOutlineColor(sf::Color::White);
	selection.setOutlineThickness(2);
	selection.setFillColor(sf::Color(255,0,100,120));
	selection.setOrigin(sf::Vector2f(0, 0));	
}

void RectangleSelect::setStartPoint(const sf::Vector2f& point)
{
	selection.setPosition(point);
}

void RectangleSelect::updateEndPoint(const sf::Vector2f& point)
{
	const sf::Vector2f& pos = selection.getPosition();

	selection.setSize(sf::Vector2f(point.x - pos.x, point.y - pos.y));
}