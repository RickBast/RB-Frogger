/**
@file Application.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "PlayerControl.h"
#include "StateStack.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"


namespace GEX
{

	class Application
	{
	public:
								Application();
		void                    run();

	private:
		void                    processInput();
		void                    update(sf::Time dt);
		void                    render();
		void                    registerStates();


	private:
		static const sf::Time   TimePerFrame;

		sf::RenderWindow        _window;
		PlayerControl           _player;
	

		StateStack              _stateStack;

	};
}

