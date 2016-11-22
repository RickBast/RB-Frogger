/**
@file Projectile.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "Category.h"
#include "CommandQueue.h"
namespace GEX
{
	class Projectile :
		public Entity
	{
	public:
		enum class Type
		{
			AlliedBullet,
			EnemyBullet,
			Missile
		};
								Projectile(Type type);
		unsigned int			getCategory() const override;
		float					getMaxSpeed() const;
		bool					isGuided();
		void					guideTowards(sf::Vector2f position);
		sf::FloatRect			getBoundingRect() const override;
	private:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void					drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;

		Type					_type;
		sf::Sprite				_sprite;
		sf::Vector2f			_targetDirection; ///<unit vector pointing at closest enemy plane
	};
}

