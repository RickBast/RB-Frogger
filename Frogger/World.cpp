/**
@file World.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "World.h"
#include <algorithm>
#include "Pickup.h"
#include "ParticleNode.h"
#include "SoundNode.h"
#include "Utility.h"
#include <memory>
#include "RiverObjects.h"

namespace GEX
{
	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_soundPlayer(soundPlayer),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0, 0, _worldView.getSize().x, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldView.getSize().y - 20.f),
		_scrollSpeed(-50.f),
		_playerAircraft(nullptr),
		_playerFrog(nullptr),
		_countdown(sf::Time::Zero)
	{

		buildScene();
	

		// Prepare the view
		//_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time dt)
	{

		updateSounds();
		// Scroll the world
		//_worldView.move(0.f, _scrollSpeed * dt.asSeconds());
		//_playerAircraft->setVelocity(0.f, _scrollSpeed);

	
		destroyEntitiesOutsideView();

		// run all the commands
		while (!_commandQueue.isEmpty())
			_sceneGraph.onCommand(_commandQueue.pop(), dt);

		handleCollisions();
		_sceneGraph.removeWrecks();

		spawnEnemies(dt);
		// Apply movements
		_sceneGraph.update(dt, _commandQueue);
		adaptPlayerPostition();
	}

	void World::updateSounds()
	{
		_soundPlayer.setListenerPosition(_playerAircraft->getWorldPosition());
		_soundPlayer.removeStoppedSounds();
	}

	void World::adaptPlayerPostition()
	{
		// Keep player's position inside the screen bounds, 
		   //at least borderDistance units from the border

		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 20.f;

		sf::Vector2f position = _playerFrog->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerFrog->setPosition(position);
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.left -= 100;
		bounds.width += 100;
		return bounds;
	}

	void World::spawnEnemies(sf::Time dt)
	{
	
		if (_countdown <= sf::Time::Zero)
		{
			
			std::unique_ptr<Vehicle> vehicle(new Vehicle(Vehicle::Type::Car));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(vehicle));

			std::unique_ptr<Vehicle> vehicle1(new Vehicle(Vehicle::Type::RaceCarL));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(vehicle1));

			std::unique_ptr<Vehicle> vehicle2(new Vehicle(Vehicle::Type::RaceCarR));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(vehicle2));

			std::unique_ptr<Vehicle> vehicle3(new Vehicle(Vehicle::Type::Truck));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(vehicle3));

			std::unique_ptr<Vehicle> vehicle4(new Vehicle(Vehicle::Type::Tractor));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(vehicle4));

			std::unique_ptr<RiverObjects> log1(new RiverObjects(RiverObjects::Type::BigLog));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(log1));

			std::unique_ptr<RiverObjects> log2(new RiverObjects(RiverObjects::Type::BigLog2));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(log2));

			std::unique_ptr<RiverObjects> log3(new RiverObjects(RiverObjects::Type::SmallLog));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_countdown += log3->getSpawnInterval();
			_sceneLayers[Background]->attachChild(std::move(log3));

			std::unique_ptr<RiverObjects> Turtles3(new RiverObjects(RiverObjects::Type::Threeturtles));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(Turtles3));

			std::unique_ptr<RiverObjects> Turtles2(new RiverObjects(RiverObjects::Type::TwoTurtles));//(randomInt(int(Vehicle::Type::TypeCount)))));
			_sceneLayers[Background]->attachChild(std::move(Turtles2));


		}
		else if (_countdown > sf::Time::Zero)
		{
			_countdown -= dt;
		}
	}

	

	



	



	void World::handleCollisions()
	{
		std::set<SceneNode::Pair> collisionsPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionsPairs);
		for (SceneNode::Pair pair : collisionsPairs)
		{
			if (matchesCategories(pair, Category::PlayerFrog, Category::vehicle))
			{
				auto& player = static_cast<Frogger&>(*pair.first);
				auto& enemy = static_cast<Vehicle&>(*pair.second);

				player.setPosition(_spawnPosition);
				
			}
		}
	}
	
	

	void World::destroyEntitiesOutsideView()
	{
		Command command;
		command.category = Category::vehicle;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time) {
			if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
				e.destroy();
		});
		_commandQueue.push(command);
	}

	bool World::hasAlivePlayer() const
	{
		return !_playerAircraft->isMarkedForRemoval();
	}

	bool World::hasReachedFinish() const
	{
		return _worldBounds.contains(_playerAircraft->getPosition().x, _playerAircraft->getPosition().y - 800.f);
	}

	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);
	}

	CommandQueue&  World::getCommandQueue()
	{
		return _commandQueue;
	}

	void World::buildScene()
	{
		// Put the layer nodes into the scene graph
		for (std::size_t i = 0; i < LayerCount; ++i)
		{
			Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attachChild(std::move(layer));
		}

		// Prepare the tiled background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(_worldBounds);

		// Add the background sprite to the scene
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attachChild(std::move(backgroundSprite));	
		

		//sf::Texture& finishlineTexture = TextureHolder::getInstance().get(TextureID::FinishLine);
		//sf::IntRect textureRect2(0, 0, finishlineTexture.getSize().x, finishlineTexture.getSize().y);
	
		// Add the background sprite to the scene
	/*	std::unique_ptr<SpriteNode> finishLineSprite(new SpriteNode(finishlineTexture, textureRect2));
		finishLineSprite->setPosition(_worldBounds.left, _worldBounds.top + 800.f);
		_sceneLayers[Air]->attachChild(std::move(finishLineSprite));*/
	


		//particle system
	/*	std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::Smoke));
		_sceneLayers[Air]->attachChild(std::move(smokeNode));

		std::unique_ptr<ParticleNode> fireNode(new ParticleNode(Particle::Type::Propellant));
		_sceneLayers[Air]->attachChild(std::move(fireNode));*/



		// Add player's aircraft
		std::unique_ptr<Frogger> leader(new Frogger());
		_playerFrog = leader.get();
		_playerFrog->setPosition(_spawnPosition);
		_playerFrog->setVelocity(0.f, 0.f);
		_sceneLayers[Air]->attachChild(std::move(leader));

		// add SoundNode

		std::unique_ptr<SoundNode> soundEffectNode(new SoundNode(_soundPlayer));
		_sceneGraph.attachChild(std::move(soundEffectNode));
	}

	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1 && type2& category2)
		{
			return true;
		}
		else if (type1 & category2 && type2& category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
			return false;
	}
}
