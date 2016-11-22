/**
@file Entity.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Entity.h"
namespace GEX
{
	Entity::Entity(int hitPoints):
		_velocity(),
		_angularVelocity(),
		_hitPoints(hitPoints)
	{}

	void Entity::setVelocity(sf::Vector2f velocity)
	{
		_velocity = velocity;
	}

	void Entity::setVelocity(float vx, float vy)
	{
		_velocity = sf::Vector2f(vx, vy);
	}

	void Entity::accelerate(float vx, float vy)
	{
		setVelocity(vx, vy);
	}

	void Entity::accelerate(sf::Vector2f a)
	{
		auto velocity = getVelocity();
		setVelocity(velocity + a);
	}

	sf::Vector2f Entity::getVelocity() const
	{
		return _velocity;
	}

	void Entity::setAngularVelocity(float angle)
	{
		_angularVelocity = angle;
	}

	float Entity::getAngularVelocity()
	{
		return _angularVelocity;
	}

	void Entity::accelerateAngularVelocity(float angle)
	{
		_angularVelocity += angle;
	}

	int Entity::getHitPoints() const
	{
		if (_hitPoints < 0)
			return 0;
		return _hitPoints;
	}

	void Entity::repair(int points)
	{
		_hitPoints += points;
		if (_hitPoints > 100)
			_hitPoints = 100;
	}

	void Entity::damage(int points)
	{
		_hitPoints -= points;
	}

	void Entity::destroy()
	{
		_hitPoints = 0;
	}

	bool Entity::isDestroyed() const
	{
		return _hitPoints <= 0;
	}

	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		move(_velocity * dt.asSeconds());
		rotate(_angularVelocity*dt.asSeconds());
	}
}