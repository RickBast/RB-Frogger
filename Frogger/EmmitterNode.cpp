#include "EmmitterNode.h"

namespace GEX
{
	EmmitterNode::EmmitterNode(Particle::Type type) :
		_accumulatedTime(sf::Time::Zero),
		_type(type),
		_particleSystem(nullptr)
	{}

	void EmmitterNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		if (_particleSystem)
			emitParticles(dt);
		else
		{
			auto finder = [this](ParticleNode& node, sf::Time dt)
			{
				if (node.getParticleType() == _type)
					_particleSystem = &node;
			};

			Command command;
			command.category = Category::ParticleSystem;
			command.action = derivedAction<ParticleNode>(finder);
			commands.push(command);
		}
	}

	void EmmitterNode::emitParticles(sf::Time dt)
	{
		const float emissionRate = 100.f;
		const sf::Time interval = sf::seconds(1) / emissionRate;
		_accumulatedTime += dt;
		while (_accumulatedTime > interval)
		{
			_accumulatedTime -= interval;
			_particleSystem->addParticle(getWorldPosition());
		}
	}
}

