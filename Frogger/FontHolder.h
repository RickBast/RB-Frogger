/**
@file FontHolder.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Font.hpp"
#include "ResourceIdentifiers.h"

#include <memory>
#include <map>

namespace GEX
{


	class FontHolder
	{

	private:
														FontHolder() {};    // must use getInstance()  
	public:
		static FontHolder&                              getInstance(); // factory method

		void                                            load(FontID id, const std::string& path);
		sf::Font&                                       get(FontID) const;


	private:
		static FontHolder*                              _instance;

		std::map<FontID, std::unique_ptr<sf::Font>>     _fonts;
	};
}