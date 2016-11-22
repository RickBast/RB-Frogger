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
#include <SFML\System\Vector2.hpp>
#include "Animation.h"


namespace sf
{
	class Sprite;
	class Text;
}

namespace GEX
{
	void				centerOrigin(sf::Sprite& sprite);
	void				centerOrigin(sf::Text& text);
	void				centerOrigin(Animation& animation);

	const float			M_PI = 3.14159265f;
	inline float		degreesToRadians(float degrees) { return degrees * M_PI / 180.f; }
	inline float		radiansToDegrees(float rads) { return rads  * 180.f / M_PI; }
	inline float		sin(float deg) { return std::sin(degreesToRadians(deg)); }
	inline float		cos(float deg) { return std::cos(degreesToRadians(deg)); }
	
	inline float		arctan2(float opp, float adj) {return radiansToDegrees(std::atan2(opp, adj));}

	int					randomInt(int exclusiveMax);

	float				length(sf::Vector2f vector);
	sf::Vector2f		unitVector(sf::Vector2f vector);
}