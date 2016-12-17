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
			None = 0,					
			SceneGroundLayer = 1 << 0,	
			PlayerFrog = 1 << 1,
			vehicle = 1 << 2,
			RiverObject = 1 << 3,

			objects = RiverObject | vehicle,
			
		};
	}
}