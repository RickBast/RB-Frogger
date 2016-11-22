/**
@file TextureHolder.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "TextureHolder.h"

namespace GEX
{
	TextureHolder* TextureHolder::_instance = nullptr;

	TextureHolder & TextureHolder::getInstance()
	{
		if (!TextureHolder::_instance)
			TextureHolder::_instance = new TextureHolder();

		return *TextureHolder::_instance;
	}

	TextureHolder::~TextureHolder()
	{
	}

	sf::Texture & TextureHolder::get(TextureID id) const
	{
		auto found = _textures.find(id);
		assert(found != _textures.end());
		return *found->second;
	}

	void TextureHolder::load(TextureID id, const std::string & path)
	{
		std::unique_ptr<sf::Texture> texture(new sf::Texture);
		if (!texture->loadFromFile(path))
			throw std::runtime_error("Load failed!" + path);

		auto rc = _textures.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0);
	}
}