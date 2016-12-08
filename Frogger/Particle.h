#pragma once
#include "SFML/Graphics.hpp"

namespace GEX
{
	struct Particle
	{
		enum class Type
		{
			Propellant,
			Smoke
		};

		sf::Vector2f	position;
		sf::Color		color;
		sf::Time		lifeTime;
	};
}


