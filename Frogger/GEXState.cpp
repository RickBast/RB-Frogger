/**
@file GEXState.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "GEXState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{


	GEXState::GEXState(StateStack& stack, Context context) :
		State(stack, context),
		_backgroundSprite(),
		_GEXStateText(),
		_pausedText(),
		_instructionText(),
		_instruction2Text()
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f viewSize = context.window->getView().getSize();

		//sets properties for sf::Text _GEXStateText
		_GEXStateText.setFont(font);
		_GEXStateText.setString("GEX State");
		_GEXStateText.setCharacterSize(30);
		centerOrigin(_GEXStateText);
		_GEXStateText.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);

		//sets properties for sf::Text _PausedText
		_pausedText.setFont(font);
		_pausedText.setString("Game Paused");
		_pausedText.setCharacterSize(70);
		centerOrigin(_pausedText);
		_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);


		 _backgroundSprite.setTexture(TextureHolder::getInstance().get(TextureID::GEXTexture));
		 centerOrigin(_backgroundSprite);
		 _backgroundSprite.setPosition(0.5f * viewSize.x, 0.5f * viewSize.y);
		 _backgroundSprite.setColor(sf::Color(255, 255, 255, 100));

		 //sets properties for sf::Text _instructionText
		_instructionText.setFont(font);
		_instructionText.setString("(Press Backspace to return to the main menu)");
		centerOrigin(_instructionText);
		_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

		//sets properties for sf::Text _instruction2Text
		_instruction2Text.setFont(font);
		_instruction2Text.setString("(Press G to return to game)");
		centerOrigin(_instruction2Text);
		_instruction2Text.setPosition(0.5f * viewSize.x, 0.8f * viewSize.y);
	}

	void GEXState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		//makes screen have a red transparent over the game
		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(250, 0, 0, 100));
		backgroundShape.setSize(window.getView().getSize());

		// draws all texts, sprite and shape to the window
		window.draw(backgroundShape);
		window.draw(_backgroundSprite);
		window.draw(_GEXStateText);
		window.draw(_pausedText);
		window.draw(_instructionText);
		window.draw(_instruction2Text);
	}

	bool GEXState::update(sf::Time)
	{
		return false;
	}

	bool GEXState::handleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::G)
		{
			// G pressed, remove itself to return to the game
			requestStackPop();
		}

		if (event.key.code == sf::Keyboard::BackSpace)
		{
			// BackSpace pressed, remove all state and make menu
			requestStateClear();
			requestStackPush(StateID::Menu);
		}

		return false;
	}
}
