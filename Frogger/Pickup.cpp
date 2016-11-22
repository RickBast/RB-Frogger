#include "Pickup.h"
#include "Projectile.h"
#include "Utility.h"
#include "ResourceIdentifiers.h"
#include "DataTables.h"

namespace GEX
{
	const std::map<Pickup::Type, PickupData> table = initializePickupData();

	Pickup::Pickup(Type type):
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		centerOrigin(_sprite);
	}

	unsigned int Pickup::getCategory() const
	{
		return Category::Pickups;
	}

	void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	sf::FloatRect Pickup::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}
	void Pickup::apply(Aircraft & player) const
	{
		table.at(_type).action(player);
	}
}
