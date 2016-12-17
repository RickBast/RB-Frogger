/**
@file State.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "State.h"
#include "StateStack.h"

namespace GEX
{

	State::Context::Context(sf::RenderWindow& window, PlayerControl& player) :
		window(&window),
		player(&player)
	{}

	State::State(StateStack& stack, Context context) :
		_stack(&stack),
		_context(context)
	{}

	State::~State()
	{}

	void State::requestStackPush(StateID stateID)
	{
		_stack->pushState(stateID);
	}

	void State::requestStackPop()
	{
		_stack->popState();
	}

	void State::requestStateClear()
	{
		_stack->clearStates();
	}

	State::Context State::getContext() const
	{
		return _context;
	}

}