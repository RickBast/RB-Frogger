/**
@file CommandQueue.cpp
@author  R Bastarache <rick_hockey8@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "CommandQueue.h"

namespace GEX
{

	void CommandQueue::push(const Command & command)
	{
		_queue.push(command);
	}

	Command CommandQueue::pop()
	{
		auto result = _queue.front();
		_queue.pop();
		return result;
	}

	bool CommandQueue::isEmpty() const
	{
		return _queue.empty();
	}
}