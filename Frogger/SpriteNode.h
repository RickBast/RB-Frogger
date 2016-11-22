/**
@file SpriteNode.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "SceneNode.h"
namespace GEX
{
	class SpriteNode : public SceneNode
	{
	public:
							SpriteNode(const sf::Texture&);
							SpriteNode(const sf::Texture&, sf::IntRect);

	private:
		sf::Sprite			_sprite;
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
	};
}

