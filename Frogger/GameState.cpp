/**
@file GameState.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "GameState.h"
#include "Utility.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"



namespace GEX
{

	GameState::GameState(StateStack& stack, Context context) :
		State(stack, context),
		_world(*context.window, *context.soundEffects),
		_player(*context.player)
	{
		context.music->play(MusicID::MissionTheme);
	}

	void GameState::draw()
	{
		_world.draw();
	}

	bool GameState::update(sf::Time dt)
	{
		_world.update(dt);
		if (!_world.hasAlivePlayer())
		{
			_player.setMissionStatus(MissionStatus::Fail);
			requestStackPush(StateID::GameOver);
		}
		else if (!_world.hasReachedFinish())
		{
			_player.setMissionStatus(MissionStatus::Sucess);
			requestStackPush(StateID::GameOver);
		}

		CommandQueue& commands = _world.getCommandQueue();
		_player.handleRealTimeInput(commands);

		return true;
	}

	bool GameState::handleEvent(const sf::Event& event)
	{
		// Game input handling
		CommandQueue& commands = _world.getCommandQueue();
		_player.handleEvent(event, commands);

		// Escape pressed, trigger the pause screen
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			requestStackPush(StateID::Pause);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			requestStackPush(StateID::GEX);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
			requestStackPush(StateID::Menu);

		return true;
	}

}