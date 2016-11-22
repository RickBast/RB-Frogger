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
#include "Aircraft.h"
#include "CommandQueue.h"
#include "PlayerControl.h"
#include "SoundPlayer.h"

#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <array>
#include <vector>


namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
	class World
	{
	public:

		explicit                            World(sf::RenderWindow& window, SoundPlayer& soundPlayer);
											World(const World&) = delete;
		World&                              operator =(const World&) = delete;

		void                                update(sf::Time dt);
		void								updateSounds();
		void                                draw();
		CommandQueue&                       getCommandQueue();

	private:
		struct SpawnPoint
		{
			SpawnPoint(Aircraft::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y)
			{}
			Aircraft::Type		type;
			float				x;
			float				y;
		};

	public:
		void                                buildScene();
		void                                adaptPlayerPostition();
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;
		void								spawnEnemies();
		void								addEnemies();
		void								addEnemy(Aircraft::Type type, float _x, float _y);
		void								addEnemy(SpawnPoint sPoint);
		void								guideMissiles();
		void								handleCollisions();
		void								destroyEntitiesOutsideView();
		bool								hasAlivePlayer() const;
		bool								hasReachedFinish() const;
		

	private:
		enum Layer
		{
			Background,
			Air,
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
		Aircraft*                           _playerAircraft;
		std::vector<SpawnPoint>				_enemySpawnPoints;
		std::vector<Aircraft*>				_activeEnemies;
		SoundPlayer&						_soundPlayer;
	};

}
