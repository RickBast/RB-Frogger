/**
@file Utility.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Utility.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <cassert>
#include <random>


namespace GEX
{
	namespace
	{
		std::default_random_engine createRandomEngine()
		{
			auto seed = static_cast<unsigned long>(std::time(nullptr));
			return std::default_random_engine(seed);
		}
		auto RandomEngine = createRandomEngine();
	}

	void centerOrigin(sf::Sprite& sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void centerOrigin(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	int randomInt(int exclusiveMax)
	{
		std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
		return distr(RandomEngine);
	}

	float length(sf::Vector2f vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

}