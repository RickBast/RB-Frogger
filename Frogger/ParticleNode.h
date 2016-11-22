#pragma once
#include "SFML\Graphics.hpp"
#include "TextureHolder.h"
#include "Entity.h"
#include "Particle.h"
#include <deque>
namespace GEX
{
	class ParticleNode : public SceneNode
	{
	public:
		explicit				ParticleNode(Particle::Type type);
		void					addParticle(sf::Vector2f position);
		Particle::Type			getParticleType() const;
		unsigned int			getCategory() const override;

	private:
		void					drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void					addVertex(float worldx, float worldy, float textu, float textv, const sf::Color color) const;
		void					computeVertices() const;

		std::deque<Particle>	_particles;
		const sf::Texture&		_texture;
		Particle::Type			_type;

		mutable sf::VertexArray	_vertexArray;
		mutable bool			_needsVertexUpdate;
	};

}