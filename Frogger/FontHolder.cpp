/**
@file FontHolder.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "FontHolder.h"
#include <cassert>

namespace GEX
{
	FontHolder* FontHolder::_instance = nullptr;

	FontHolder& FontHolder::getInstance()
	{
		if (!FontHolder::_instance)
			FontHolder::_instance = new FontHolder();

		return *FontHolder::_instance;
	}

	void FontHolder::load(FontID id, const std::string & path)
	{
		std::unique_ptr<sf::Font> texture(new sf::Font);
		if (!texture->loadFromFile(path))
			throw std::runtime_error("Load failed - " + path);

		auto rc = _fonts.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0); // big problems if insert fails
	}

	sf::Font& FontHolder::get(FontID id) const
	{
		auto found = _fonts.find(id);
		assert(found != _fonts.end());  // find returns an iterator to pair in map
		         return *found->second; // de-reference iterator and return pointer by reference
	}

}

