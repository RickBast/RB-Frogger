/**
@file Command.h
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include <cassert>
#include <functional>
#include <SFML/System.hpp>
#include <cassert>

namespace GEX
{
	class SceneNode;
	struct Command
	{
	public:
														Command();

		std::function<void(SceneNode&, sf::Time)>		action;
		unsigned int									category;
	};

	template<typename GameObject, typename function>
	std::function<void(SceneNode&, sf::Time)>			derivedAction(function fn)
	{
		return[=](SceneNode& node, sf::Time dt)
		{
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}