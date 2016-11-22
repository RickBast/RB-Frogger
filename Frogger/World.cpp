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
namespace GEX
{
	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_soundPlayer(soundPlayer),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0, 0, _worldView.getSize().x, 4000.f),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - _worldView.getSize().y / 2.f),
		_scrollSpeed(-50.f),
		_playerAircraft(nullptr)
	{

		buildScene();
		addEnemies();

		// Prepare the view
		_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time dt)
	{

		updateSounds();
		// Scroll the world
		_worldView.move(0.f, _scrollSpeed * dt.asSeconds());
		_playerAircraft->setVelocity(0.f, _scrollSpeed);

		guideMissiles();
		destroyEntitiesOutsideView();

		// run all the commands
		while (!_commandQueue.isEmpty())
			_sceneGraph.onCommand(_commandQueue.pop(), dt);

		handleCollisions();
		_sceneGraph.removeWrecks();

		spawnEnemies();
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
		const float borderDistance = 35.f;

		sf::Vector2f position = _playerAircraft->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerAircraft->setPosition(position);
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100;
		bounds.height += 100;
		return bounds;
	}

	void World::spawnEnemies()
	{
		while (!_enemySpawnPoints.empty() && _enemySpawnPoints.back().y > getBattlefieldBounds().top)
		{
			auto spawn = _enemySpawnPoints.back();
			std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type));
			enemy->setPosition(spawn.x, spawn.y);
			enemy->setRotation(180);
			_sceneLayers[Air]->attachChild(std::move(enemy));
			_enemySpawnPoints.pop_back();
		}
	}

	void World::addEnemies()
	{
		addEnemy(Aircraft::Type::Raptor, -250.f, -200.f);
		addEnemy(Aircraft::Type::Raptor, +250.f, -200.f);
		addEnemy(Aircraft::Type::Raptor, -350.f, -400.f);
		addEnemy(Aircraft::Type::Raptor, +350.f, -400.f);

		addEnemy(Aircraft::Type::Avenger, -250.f, -800.f);
		addEnemy(Aircraft::Type::Avenger, +250.f, -800.f);
		addEnemy(Aircraft::Type::Avenger, -350.f, -900.f);
		addEnemy(Aircraft::Type::Avenger, +350.f, -900.f);

		std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {return lhs.y < rhs.y;});
	}

	void World::addEnemy(Aircraft::Type type, float _x, float _y)
	{
		addEnemy(SpawnPoint(type, _x, _y));
	}

	void World::addEnemy(SpawnPoint sPoint)
	{
		sPoint.x = _spawnPosition.x + sPoint.x;
		sPoint.y = _spawnPosition.y + sPoint.y;
		_enemySpawnPoints.push_back(sPoint);
	}

	void World::guideMissiles()
	{
		Command enemyCollector;
		enemyCollector.category = Category::EnemyAircraft;
		enemyCollector.action = derivedAction<Aircraft>([this](Aircraft& enemy, sf::Time dt)
		{
			if (!enemy.isDestroyed())
				this->_activeEnemies.push_back(&enemy);
		});

		Command missileGuider;
		missileGuider.category = Category::AlliedProjectile;
		missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt)
		{
			if (!missile.isGuided())
				return;

			float minDistance = std::numeric_limits<float>::max();

			Aircraft* closestEnemy = nullptr;
			for (Aircraft* enemy : this->_activeEnemies)
			{
				float enemyDistance = distance(missile, *enemy);
				if (enemyDistance < minDistance)
				{
					closestEnemy = enemy;
					minDistance = enemyDistance;
				}
			}
			if (closestEnemy)
				missile.guideTowards(closestEnemy->getWorldPosition());
		});

		_commandQueue.push(enemyCollector);
		_commandQueue.push(missileGuider);
		_activeEnemies.clear();
	}

	void World::handleCollisions()
	{
		std::set<SceneNode::Pair> collisionsPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionsPairs);
		for (SceneNode::Pair pair : collisionsPairs)
		{
			if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
			{
				auto& player = static_cast<Aircraft&>(*pair.first);
				auto& enemy = static_cast<Aircraft&>(*pair.second);

				player.damage(enemy.getHitPoints());
				enemy.destroy();
			}

			if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
			{
				auto& player = static_cast<Aircraft&>(*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

				player.damage(projectile.getHitPoints());
				projectile.destroy();
			}

			if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile))
			{
				auto& enemy = static_cast<Aircraft&>(*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

 			 	enemy.damage(projectile.getHitPoints());
			 	projectile.destroy();
			}

			if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickups))
			{
				auto& player = static_cast<Aircraft&>(*pair.first);
				auto& pickup = static_cast<Pickup&>(*pair.second);

				pickup.apply(player);
				pickup.destroy();
				player.playLocalSound(_commandQueue, SoundEffectID::CollectPickup);
			}
		}
	}
	
	

	void World::destroyEntitiesOutsideView()
	{
		Command command;
		command.category = Category::Projectile | Category::EnemyAircraft;
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
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Jungle);
		sf::IntRect textureRect(_worldBounds);
		texture.setRepeated(true);

		// Add the background sprite to the scene
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attachChild(std::move(backgroundSprite));	
		

		sf::Texture& finishlineTexture = TextureHolder::getInstance().get(TextureID::FinishLine);
		sf::IntRect textureRect2(0, 0, finishlineTexture.getSize().x, finishlineTexture.getSize().y);
	
		// Add the background sprite to the scene
		std::unique_ptr<SpriteNode> finishLineSprite(new SpriteNode(finishlineTexture, textureRect2));
		finishLineSprite->setPosition(_worldBounds.left, _worldBounds.top + 800.f);
		_sceneLayers[Air]->attachChild(std::move(finishLineSprite));
	


		//particle system
		std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::Smoke));
		_sceneLayers[Air]->attachChild(std::move(smokeNode));

		std::unique_ptr<ParticleNode> fireNode(new ParticleNode(Particle::Type::Propellant));
		_sceneLayers[Air]->attachChild(std::move(fireNode));


		// Add player's aircraft
		std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle));
		_playerAircraft = leader.get();
		_playerAircraft->setPosition(_spawnPosition);
		_playerAircraft->setVelocity(0.f, _scrollSpeed);
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
