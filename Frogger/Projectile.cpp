/**
@file Projectile.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"
#include "Category.h"
#include "ResourceIdentifiers.h"
#include "EmmitterNode.h"

namespace GEX
{
	const std::map<Projectile::Type, ProjectileData> table = initializeProjectileData();

	Projectile::Projectile(Type type) :
		Entity(table.at(type).damage),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		centerOrigin(_sprite);
		if (isGuided())
		{
			std::unique_ptr<EmmitterNode>smoke(new EmmitterNode(Particle::Type::Smoke));
			smoke->setPosition(0.f, getBoundingRect().height / 2.f);
			attachChild(std::move(smoke));

			std::unique_ptr<EmmitterNode>fire(new EmmitterNode(Particle::Type::Propellant));
			fire->setPosition(0.f, getBoundingRect().height / 2.f);
			attachChild(std::move(fire));
		}
	}

	unsigned int Projectile::getCategory() const
	{
		switch (_type)
		{
		case Type::EnemyBullet:
			return Category::EnemyProjectile;
			break;
		case Type::AlliedBullet:
		case Type::Missile:
			return Category::AlliedProjectile;
			break;
		default:
			assert(0);
			return Category::None;
			break;
		}
	}

	float Projectile::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}


	bool Projectile::isGuided()
	{
		return _type == Type::Missile;
	}

	void Projectile::guideTowards(sf::Vector2f position)
	{
		assert(isGuided());
		_targetDirection = unitVector(position - getWorldPosition());
	}

	void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (isGuided())
		{
			const float approachRate = 6000.f;
			sf::Vector2f newVelocity = unitVector(table.at(_type).approachRate * dt.asSeconds() * _targetDirection + getVelocity());
			setVelocity(newVelocity * getMaxSpeed());
			setRotation(arctan2(newVelocity.x , newVelocity.y * -1));
		}

		Entity::updateCurrent(dt, commands);  // call Entity base class method
	}

	void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	sf::FloatRect Projectile::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

}