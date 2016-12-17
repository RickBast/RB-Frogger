/**
@file World.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "SpriteNode.h"

#include "CommandQueue.h"
#include "PlayerControl.h"

#include "Frogger.h"
#include "Vehicle.h"

#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <array>
#include <vector>


namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
	class Vehicle;
	class World
	{
	public:

		explicit                            World(sf::RenderWindow& window);
											World(const World&) = delete;
		World&                              operator =(const World&) = delete;

		void                                update(sf::Time dt);
	
		void                                draw();
		CommandQueue&                       getCommandQueue();

	private:


	public:
		void                                buildScene();
		void                                adaptPlayerPostition();
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;
		void								spawnObjects(sf::Time dt);

	
		void								handleCollisions();
		void								destroyEntitiesOutsideView();
		bool								hasAlivePlayer() const;
		

	private:
		enum Layer
		{
			Background,
			Ground,
			LayerCount
		};


	private:
		sf::RenderWindow&                   _window;
		sf::View                            _worldView;
		SceneNode                           _sceneGraph;
		std::array<SceneNode*, LayerCount>  _sceneLayers;
		CommandQueue                        _commandQueue;

		sf::FloatRect                       _worldBounds;
		sf::Vector2f                        _spawnPosition;
		float                               _scrollSpeed;

		Frogger*                            _playerFrog;
	

		sf::Time							_countdown;
		bool								_isOnObject;

	};

}
