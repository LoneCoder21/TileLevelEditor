#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include <iostream>

#define PRINT(name) Console::print(#name, (name))
#define SFML_PRINT(name) PRINT(name)

#pragma once

struct Console
{
	template<typename T>
	static void print(const char* name, const T& u);

	template<typename T>
	static void print(const char* name, const sf::Vector2<T>& u);

	template<typename T>
	static void print(const char* name, const sf::Rect<T>& u);
};

template<typename T>
static void Console::print(const char* name, const sf::Vector2<T>& u)
{
	std::cout << name << ": (" << u.x << " " << u.y << ")" << std::endl << std::endl;
}

template<typename T>
static void Console::print(const char* name, const sf::Rect<T>& u) 
{
	std::cout << name << ": (" << u.left << " " << u.top << " " << u.width << " " << u.height << ")" << std::endl << std::endl;
}

template<typename T>
static void Console::print(const char* name, const T& u)
{
	std::cout << name << ": " << u << std::endl;
}