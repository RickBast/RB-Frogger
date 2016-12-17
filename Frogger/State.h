/**
@file State.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once


#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include <memory>
#include "StateIdentifiers.h"


namespace sf
{
	class RenderWindow;
}


namespace GEX
{
	class StateStack;
	class PlayerControl;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
			Context(sf::RenderWindow& window, PlayerControl& player);

			sf::RenderWindow*   window;
			PlayerControl*      player;
	
		};


	public:
							State(StateStack& stack, Context context);
		virtual             ~State();

		virtual void        draw() = 0;
		virtual bool        update(sf::Time dt) = 0;
		virtual bool        handleEvent(const sf::Event& event) = 0;


	protected:
		void                requestStackPush(StateID stateID);
		void                requestStackPop();
		void                requestStateClear();

		Context             getContext() const;


	private:
		StateStack*         _stack;
		Context             _context;
	};

}

