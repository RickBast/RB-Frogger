/**
@file TextureHolder.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <cassert>
#include "ResourceIdentifiers.h"
namespace GEX
{


	class TextureHolder
	{
	public:
		static TextureHolder&								getInstance();
															~TextureHolder();
		sf::Texture&										get(TextureID id) const;
		void												load(TextureID id, const std::string& path);

	private:
		TextureHolder() {};
		static TextureHolder*								_instance;
		std::map <TextureID, std::unique_ptr<sf::Texture>>	_textures;

	};
}