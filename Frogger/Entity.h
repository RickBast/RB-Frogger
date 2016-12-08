/**
@file Entity.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "SceneNode.h"
#include "SFML/Graphics.hpp"
#include "CommandQueue.h"
namespace GEX
{
	class Entity : public SceneNode
	{
	public:
						Entity(int hitPoints = 20);
		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		void			accelerate(sf::Vector2f a);
		void			accelerate(float vx, float vy);
		sf::Vector2f	getVelocity() const;
		void			setAngularVelocity(float angle);
		float			getAngularVelocity();
		void			accelerateAngularVelocity(float angle);

		int				getHitPoints() const;
		void			repair(int points);
		void			damage(int points);
		void			destroy();
		bool			isDestroyed() const override;

	protected:
		void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
	private:
		sf::Vector2f	_velocity;
		float			_angularVelocity;
		int				_hitPoints;
	};
}