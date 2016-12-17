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

	
	std::map<Vehicle::Type, VehicleData> initializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::Car].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Car].textureRect = sf::IntRect(1,62,35,29);
		data[Vehicle::Type::Car].speed = -50.f;
		data[Vehicle::Type::Car].spawnPoint = sf::Vector2f(490,460);
		data[Vehicle::Type::Car].spawnInterval = sf::seconds(7);

		data[Vehicle::Type::RaceCarL].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::RaceCarL].textureRect = sf::IntRect(139, 100, 38, 39);
		data[Vehicle::Type::RaceCarL].speed = -40.f;
		data[Vehicle::Type::RaceCarL].spawnPoint = sf::Vector2f(499, 540);
		data[Vehicle::Type::RaceCarL].spawnInterval = sf::seconds(7);

		data[Vehicle::Type::RaceCarR].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::RaceCarR].textureRect = sf::IntRect(69, 100, 37, 37);
		data[Vehicle::Type::RaceCarR].speed = 40.f;
		data[Vehicle::Type::RaceCarR].spawnPoint = sf::Vector2f(-19, 420);
		data[Vehicle::Type::RaceCarR].spawnInterval = sf::seconds(7);

		data[Vehicle::Type::Tractor].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Tractor].textureRect = sf::IntRect(214, 62, 33, 33);
		data[Vehicle::Type::Tractor].speed = 60.f;
		data[Vehicle::Type::Tractor].spawnPoint = sf::Vector2f(-10, 500);
		data[Vehicle::Type::Tractor].spawnInterval = sf::seconds(7);


		data[Vehicle::Type::Truck].texture = TextureID::FrogAtlas;
		data[Vehicle::Type::Truck].textureRect = sf::IntRect(293, 1, 61, 28);
		data[Vehicle::Type::Truck].speed = -70.f;
		data[Vehicle::Type::Truck].spawnPoint = sf::Vector2f(499, 380);
		data[Vehicle::Type::Truck].spawnInterval = sf::seconds(7);

		return data;
	}

	std::map<RiverObjects::Type, RiverObjectData> initializeRiverObjectData()
	{
		std::map<RiverObjects::Type, RiverObjectData> data;

		data[RiverObjects::Type::BigLog].texture = TextureID::FrogAtlas;
		data[RiverObjects::Type::BigLog].textureRect = sf::IntRect(1, 31, 195, 28);
		data[RiverObjects::Type::BigLog].speed = 50.f;
		data[RiverObjects::Type::BigLog].spawnPoint = sf::Vector2f(-100, 260);
		data[RiverObjects::Type::BigLog].spawnInterval = sf::seconds(5);

		data[RiverObjects::Type::BigLog2].texture = TextureID::FrogAtlas;
		data[RiverObjects::Type::BigLog2].textureRect = sf::IntRect(1, 31, 195, 28);
		data[RiverObjects::Type::BigLog2].speed = 50.f;
		data[RiverObjects::Type::BigLog2].spawnPoint = sf::Vector2f(-100, 140);
		data[RiverObjects::Type::BigLog2].spawnInterval = sf::seconds(5);

		data[RiverObjects::Type::SmallLog].texture = TextureID::FrogAtlas;
		data[RiverObjects::Type::SmallLog].textureRect = sf::IntRect(198, 31, 93, 29);
		data[RiverObjects::Type::SmallLog].speed = 40.f;
		data[RiverObjects::Type::SmallLog].spawnPoint = sf::Vector2f(-50, 220);
		data[RiverObjects::Type::SmallLog].spawnInterval = sf::seconds(5);

		data[RiverObjects::Type::TwoTurtles].texture = TextureID::FrogAtlas;
		data[RiverObjects::Type::TwoTurtles].textureRect = sf::IntRect(125, 1, 65, 26);
		data[RiverObjects::Type::TwoTurtles].speed = -40.f;
		data[RiverObjects::Type::TwoTurtles].spawnPoint = sf::Vector2f(470, 180);
		data[RiverObjects::Type::TwoTurtles].spawnInterval = sf::seconds(5);

		data[RiverObjects::Type::Threeturtles].texture = TextureID::FrogAtlas;
		data[RiverObjects::Type::Threeturtles].textureRect = sf::IntRect(192, 1, 99, 26);
		data[RiverObjects::Type::Threeturtles].speed = -40.f;
		data[RiverObjects::Type::Threeturtles].spawnPoint = sf::Vector2f(499, 300);
		data[RiverObjects::Type::Threeturtles].spawnInterval = sf::seconds(5);




		return data;
	}
}


