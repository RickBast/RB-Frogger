#pragma once
#include "Particle.h"
#include "SceneNode.h"
#include "ParticleNode.h"

namespace GEX
{
	class EmmitterNode : public SceneNode
	{
	public:
		explicit EmmitterNode(Particle::Type type);

	private:
		void updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void emitParticles(sf::Time dt);

		sf::Time _accumulatedTime;
		Particle::Type _type;
		ParticleNode* _particleSystem;

	};
}

