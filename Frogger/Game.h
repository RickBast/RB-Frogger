#pragma once
#include "TextureHolder.h"
#include "World.h"
#include"Aircraft.h"
#include "PlayerControl.h"
namespace GEX
{
	class Game
	{
	public:
		Game();
		~Game();
		void				run();

	private:

		void				update(sf::Time deltaTime);
		void				render();
		void				updateStats(sf::Time deltaTime);
		void				processInput();
		sf::RenderWindow	_window;
		World				_world;
		PlayerControl		_player;
		sf::Font			_font;
		sf::Text			_statsText;
	};
}

