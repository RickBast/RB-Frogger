/**
@file GEXState.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once


#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


namespace GEX
{

	class GEXState : public State
	{
	public:
							GEXState(StateStack& stack, Context context);
		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);

	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _pausedText;
		sf::Text            _instructionText;
		sf::Text			_GEXStateText;
		sf::Text			_instruction2Text;
	};

}
