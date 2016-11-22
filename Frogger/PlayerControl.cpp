/**
@file PlayerControl.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "PlayerControl.h"
#include "Aircraft.h"
#include "Category.h"

namespace GEX
{
	struct AircraftMover
	{
		AircraftMover(float vx, float vy) : velocity(vx, vy)
		{}
		void operator()(Aircraft& aircraft, sf::Time dt)const
		{
			aircraft.accelerate(velocity);
		}
		sf::Vector2f velocity;
	};

	PlayerControl::PlayerControl():
		_missionStatus(MissionStatus::Active)
	{
		initializedKeyBindings();
		initializedActionBindings();
	}

	void PlayerControl::handleEvent(const sf::Event& event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto found = _keyBindings.find(event.key.code);
			if (found != _keyBindings.end())
				commands.push(_actionBindings[found->second]);
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue & commands)
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
	}

	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_missionStatus = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}

	void PlayerControl::initializedKeyBindings()
	{
		_keyBindings[sf::Keyboard::Left] = Action::MoveLeft;
		_keyBindings[sf::Keyboard::Right] = Action::MoveRight;
		_keyBindings[sf::Keyboard::Up] = Action::MoveUp;
		_keyBindings[sf::Keyboard::Down] = Action::MoveDown;
		_keyBindings[sf::Keyboard::Space] = Action::FireBullet;
		_keyBindings[sf::Keyboard::M] = Action::LaunchMissile;
	}

	void PlayerControl::initializedActionBindings()
	{
		const float playerSpeed = 200.f;
		const float RotationSpeed = 1.f;

		_actionBindings[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		_actionBindings[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
		_actionBindings[Action::FireBullet].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time dt) {a.fire();});
		_actionBindings[Action::LaunchMissile].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time dt) {a.launchMissile();});

		for (auto& pair : _actionBindings)
			pair.second.category = Category::PlayerAircraft;
	}

	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::MoveDown:
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
			return true;
		default:
			return false;
		}
		return false;
	}
}