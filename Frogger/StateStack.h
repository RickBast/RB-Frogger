/**
@file StateStack.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once

#include "SFML/System.hpp"

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace GEX
{
	class StateStack
	{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear,
		};


	public:
		explicit            StateStack(State::Context context);
							StateStack(const StateStack&) = delete;
		StateStack&         operator =(const StateStack&) = delete;

		template			<typename T>
		void                registerState(StateID stateID);

		void                update(sf::Time dt);
		void                draw();
		void                handleEvent(const sf::Event& event);

		void                pushState(StateID stateID);
		void                popState();
		void                clearStates();

		bool                isEmpty() const;


	private:
		State::Ptr          createState(StateID stateID);
		void                applyPendingChanges();


	private:
		struct PendingChange
		{
			explicit            PendingChange(Action action, StateID stateID = StateID::None);

			Action              action;
			StateID             stateID;
		};


	private:
		std::vector<State::Ptr>                             _stack;
		std::vector<PendingChange>                          _pendingList;

		State::Context                                      _context;
		std::map<StateID, std::function<State::Ptr()>>      _factories;
	};


	template <typename T>
	void StateStack::registerState(StateID stateID)
	{
		_factories[stateID] = [this]()
		{
			return State::Ptr(new T(*this, _context));
		};
	}


}