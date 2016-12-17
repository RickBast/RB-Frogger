/**
@file Utility.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>


namespace sf
{
	class Sprite;
	class Text;
}

namespace GEX
{
	void				centerOrigin(sf::Sprite& sprite);
	void				centerOrigin(sf::Text& text);

	int					randomInt(int exclusiveMax);

	float				length(sf::Vector2f vector);

}