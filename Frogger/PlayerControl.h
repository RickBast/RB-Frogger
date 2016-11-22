/**
@file PlayerControl.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "SFML/Graphics.hpp"
#include "CommandQueue.h"
#include "Command.h"
#include <map>
namespace GEX
{
	enum class Action {
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		RotateLeft,
		RotateRight,
		FireBullet,
		LaunchMissile
	};
	enum class MissionStatus
	{
		Active,
		Sucess,
		Fail
	};
	class PlayerControl
	{
	public:
												PlayerControl();
		void									handleEvent(const sf::Event& event, CommandQueue& commands);
		void									handleRealTimeInput(CommandQueue& commands);
		void									setMissionStatus(MissionStatus status);
		MissionStatus							getMissionStatus() const;

	private:
		std::map<sf::Keyboard::Key, Action>		_keyBindings;
		std::map<Action, Command>				_actionBindings;
		void									initializedKeyBindings();
		void									initializedActionBindings();
		bool									isRealTimeAction(Action action);
		MissionStatus							_missionStatus;
	};
}