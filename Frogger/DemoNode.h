#pragma once
#include "Entity.h"
#include <string>
#include <iostream>
namespace GEX
{
	class DemoNode :
		public Entity
	{
	public:
		DemoNode(std::string name) :_name(name) {};
		virtual ~DemoNode() {};

	

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override
		{
			std::cout << "Draw " << _name << std::endl;
		}
		std::string _name;
	};
}

