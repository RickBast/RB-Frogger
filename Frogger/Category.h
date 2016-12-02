/**
@file Category.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/#pragma once
namespace GEX
{
	namespace Category
	{
		enum Type
		{
			None = 0,					// 0000 0000
			SceneAirLayer = 1 << 0,		// 0000 0001
			PlayerAircraft = 1 << 1,	// 0000 0010
			AlliedAircraft = 1 << 2,	// 0000 0100
			EnemyAircraft = 1 << 3,		// 0000 1000
			Pickups = 1 << 4,			// 0001 0000
			AlliedProjectile = 1 << 5,	// 0010 0000
			EnemyProjectile = 1 << 6,	// 0100 0000
			ParticleSystem = 1 << 7,	// 1000 0000
			SoundEffect = 1 << 8,
			PlayerFrog = 1 << 9,
			vehicle = 1 << 10,
			RiverObject = 1 << 11,

			Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,						// 0000 1110
			Projectile = AlliedProjectile | EnemyProjectile,								// 0110 0000
			ThingsPlayerCollidesWith = EnemyAircraft | EnemyProjectile | Pickups,			// 0101 1000
			ThingsEnemiesCollideWith = AlliedAircraft | PlayerAircraft | AlliedAircraft		// 0010 0110
		};
	}
}