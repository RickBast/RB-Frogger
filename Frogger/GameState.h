/**
@file GameState.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once


#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "World.h"
#include "PlayerControl.h"
#include "State.h"

namespace GEX
{


	class GameState : State
	{
	public:
							GameState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dtz);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		World               _world;
		PlayerControl&      _player;

	};
}

