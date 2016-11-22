/**
@file Command.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Command.h"
#include "Category.h"

namespace GEX
{

	Command::Command():
		action(),
		category(Category::None)
	{}
}