#pragma once

#include "Entity.h"
#include "Category.h"
#include "SFML/Graphics.hpp"
#include <map>
#include "TextureHolder.h"
#include "CommandQueue.h"
#include "Aircraft.h"
namespace GEX
{
	class Aircraft;
	class Pickup : public Entity
	{
	public:

		enum class Type
		{
			RefillMissiles,
			FireSpread,
			FireRate,
			HealthRefill,
			typeCount
		};

		Pickup(Type type);
		unsigned int			getCategory() const override;
		void					drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		sf::FloatRect			getBoundingRect() const override;
		void					apply(Aircraft& player) const;

	private:
		Type					_type;
		sf::Sprite				_sprite;
	};

}
