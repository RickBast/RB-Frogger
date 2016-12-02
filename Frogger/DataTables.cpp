/**
@file DataTable.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "DataTables.h"




namespace GEX
{
	Direction::Direction(float a, float d) : angle(a), distance(d)
	{}

	std::map<Aircraft::Type, AircraftData> GEX::initializeAircraftData()
	{
		std::map<Aircraft::Type, AircraftData> data;

		data[Aircraft::Type::Eagle].hitPoints = 100;
		data[Aircraft::Type::Eagle].speed = 200.f;
		data[Aircraft::Type::Eagle].fireInterval = sf::seconds(1);
		data[Aircraft::Type::Eagle].texture = TextureID::Atlas;
		data[Aircraft::Type::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);

		data[Aircraft::Type::Raptor].hitPoints = 20;
		data[Aircraft::Type::Raptor].speed = 50.f;
		data[Aircraft::Type::Raptor].texture = TextureID::Atlas;
		data[Aircraft::Type::Raptor].fireInterval = sf::Time::Zero;
		data[Aircraft::Type::Raptor].directions.push_back(Direction(+80.f, 80.f));
		data[Aircraft::Type::Raptor].directions.push_back(Direction(-80.f, 100.f));
		data[Aircraft::Type::Raptor].directions.push_back(Direction(+80.f, 80.f));
		data[Aircraft::Type::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);

		data[Aircraft::Type::Avenger].hitPoints = 40;
		data[Aircraft::Type::Avenger].speed = 50.f;
		data[Aircraft::Type::Avenger].texture = TextureID::Atlas;
		data[Aircraft::Type::Avenger].fireInterval = sf::seconds(2);
		data[Aircraft::Type::Avenger].directions.push_back(Direction(+70.f, 150.f));
		data[Aircraft::Type::Avenger].directions.push_back(Direction(0.f, 25.f));
		data[Aircraft::Type::Avenger].directions.push_back(Direction(-70.f, 300.f));
		data[Aircraft::Type::Avenger].directions.push_back(Direction(0.f, 25.f));
		data[Aircraft::Type::Avenger].directions.push_back(Direction(+70.f, 150.f));
		data[Aircraft::Type::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);


		return data;

	}

	std::map<Projectile::Type, ProjectileData> GEX::initializeProjectileData()
	{
		std::map<Projectile::Type, ProjectileData> data;

		data[Projectile::Type::AlliedBullet].damage = 10;
		data[Projectile::Type::AlliedBullet].speed = 300.f;
		data[Projectile::Type::AlliedBullet].texture = TextureID::Atlas;
		data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::Missile].damage = 100000;
		data[Projectile::Type::Missile].speed = 300.f;
		data[Projectile::Type::Missile].texture = TextureID::Atlas;
		data[Projectile::Type::Missile].approachRate = 1000.f;
		data[Projectile::Type::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

		data[Projectile::Type::EnemyBullet].damage = 10;
		data[Projectile::Type::EnemyBullet].speed = 300.f;
		data[Projectile::Type::EnemyBullet].texture = TextureID::Atlas;
		data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(178, 64, 3, 14);
		return data;
	}

	std::map<Particle::Type, ParticleData> initializeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		data[Particle::Type::Propellant].color = sf::Color(226, 153, 0);
		data[Particle::Type::Propellant].lifeTime = sf::seconds(0.1f);

		data[Particle::Type::Smoke].color = sf::Color(96, 96, 96);
		data[Particle::Type::Smoke].lifeTime = sf::seconds(0.5f);
		return data;
	}

	std::map<Pickup::Type, PickupData> GEX::initializePickupData()
	{
		std::map<Pickup::Type, PickupData> data;

		data[Pickup::Type::RefillMissiles].texture = TextureID::Atlas;
		data[Pickup::Type::RefillMissiles].action = [](Aircraft& a) {a.collectMissiles(3);};
		data[Pickup::Type::RefillMissiles].textureRect = sf::IntRect(40, 64, 40, 40);

		data[Pickup::Type::FireSpread].texture = TextureID::Atlas;
		data[Pickup::Type::FireSpread].action = [](Aircraft& a) {a.increaseSpread();};
		data[Pickup::Type::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);

		data[Pickup::Type::FireRate].texture = TextureID::Atlas;
		data[Pickup::Type::FireRate].action = [](Aircraft& a) {a.increaseFireRate();};
		data[Pickup::Type::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);

		data[Pickup::Type::HealthRefill].texture = TextureID::Atlas;
		data[Pickup::Type::HealthRefill].action = [](Aircraft& a) {a.repair(25);};
		data[Pickup::Type::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);

		return data;
	}

	std::map<Vehicle::Type, VehicleData> GEX::initializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::Car].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Car].textureRect = sf::IntRect(1,62,35,29);
		data[Vehicle::Type::Car].speed = -50.f;
		data[Vehicle::Type::Car].spawnPoint = sf::Vector2f(499,460);
		data[Vehicle::Type::Car].spawnInterval = sf::seconds(3);

		data[Vehicle::Type::RaceCarL].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::RaceCarL].textureRect = sf::IntRect(139, 100, 38, 39);
		data[Vehicle::Type::RaceCarL].speed = -40.f;
		data[Vehicle::Type::RaceCarL].spawnPoint = sf::Vector2f(499, 540);
		data[Vehicle::Type::RaceCarL].spawnInterval = sf::seconds(3);


		data[Vehicle::Type::RaceCarR].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::RaceCarR].textureRect = sf::IntRect(69, 100, 37, 37);
		data[Vehicle::Type::RaceCarR].speed = 40.f;
		data[Vehicle::Type::RaceCarR].spawnPoint = sf::Vector2f(-19, 420);
		data[Vehicle::Type::RaceCarR].spawnInterval = sf::seconds(3);

		data[Vehicle::Type::Tractor].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Tractor].textureRect = sf::IntRect(214, 62, 33, 33);
		data[Vehicle::Type::Tractor].speed = 60.f;
		data[Vehicle::Type::Tractor].spawnPoint = sf::Vector2f(-10, 500);
		data[Vehicle::Type::Tractor].spawnInterval = sf::seconds(3);


		data[Vehicle::Type::Truck].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Truck].textureRect = sf::IntRect(293, 1, 61, 28);
		data[Vehicle::Type::Truck].speed = -70.f;
		data[Vehicle::Type::Truck].spawnPoint = sf::Vector2f(499, 380);
		data[Vehicle::Type::Truck].spawnInterval = sf::seconds(3);

		return data;
	}
}


