/**
@file ResourceIdentifiers.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
namespace GEX
{
	enum class FontID {
		Main
	};

	enum class SoundEffectID
	{
		AlliedGunfire,
		EnemyGunfire,
		Explosion1,
		Explosion2,
		LaunchMissile,
		CollectPickup,
		Button,
	};


	enum class TextureID {
		Eagle,
		Raptor,
		Avenger,
		Desert,
		Jungle,
		Airplane,
		Missile,
		Bullet,
		TitleScreen,
		MenuScreen,
		ButtonNormal,
		ButtonPressed,
		ButtonSelected,
		GEXTexture,
		FireRate,
		FireSpread,
		HealthRefill,
		RefillMissiles,
		Particle,
		Atlas,
		Explosion,
		FinishLine,
		Background,
		Frog
	};

}