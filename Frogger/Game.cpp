#include "Game.h"
#include "Aircraft.h"
#include <map>
#include <cassert>
#include <string>
#include <iostream>
#include "Command.h"
#include "Category.h"
#include <cassert>

namespace GEX
{
	Game::Game() : _window(sf::VideoMode(1024, 640), "----GEX----"),
		_world(_window),
		_player(),
		_font(),
		_statsText()
	{
		_font.loadFromFile("../Media/Sansation.ttf");
		_statsText.setFont(_font);
		_statsText.setPosition(5.f, 5.f);
		_statsText.setCharacterSize(18);
		_statsText.setFillColor(sf::Color::Red);
		_statsText.setOutlineColor(sf::Color::Black);
		_statsText.setOutlineThickness(1);
	}

	Game::~Game()
	{
	}

	void Game::run()
	{
		const sf::Time spf = sf::seconds(1.f / 60.f);

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while (_window.isOpen())
		{
			processInput();
			timeSinceLastUpdate = clock.restart();
			while (timeSinceLastUpdate > spf)
			{
				timeSinceLastUpdate -= spf;
				processInput();
				update(spf);
			}
			update(timeSinceLastUpdate);
			render();
		}
	}

	void Game::update(sf::Time dt)
	{
		_world.update(dt);
		updateStats(dt);
	}


	void Game::render()
	{
		_window.clear();
		_world.draw();
		_window.setView(_window.getDefaultView());
		_window.draw(_statsText);
		_window.display();
	}



	void Game::updateStats(sf::Time dt)
	{
		static int numOfFrames = 0;
		static sf::Time timePassed = sf::Time::Zero;

		timePassed += dt;
		numOfFrames += 1;
		if (timePassed >= sf::seconds(1.f))
		{
			_statsText.setString("Frames / second = " + std::to_string(numOfFrames) + "\n" + "Time update / time = " + std::to_string(timePassed.asMicroseconds() / numOfFrames));
			std::cout << "fps: " << numOfFrames << std::endl;
			timePassed -= sf::seconds(1.f);
			numOfFrames = 0;
		}
	}

	void Game::processInput()
	{
		CommandQueue& commands = _world.getCommandQueue();

		sf::Event event;
		while (_window.pollEvent(event))
		{
			_player.handleEvent(event, commands);
			if (event.type == sf::Event::Closed)
				_window.close();
		}

		_player.handleRealTimeInput(commands);
	}
}