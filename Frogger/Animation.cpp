/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION

*/

#include "Animation.h"

#include <cassert>


namespace GEX {


	Animation::Animation(bool repeat) :
		_currentFrame(0),
		_elapsedTime(sf::Time::Zero),
		_duration(sf::Time::Zero),
		_repeat(repeat)
	{}


	Animation::~Animation()
	{}

	void Animation::addFrame(const Frame& frame)
	{
		_frames.push_back(frame);
	}

    void Animation::addFrameSet(const std::vector<Frame> frames)
    {
        _frames = frames;
        
    }
	void Animation::setDurationAsSeconds(float d)
	{
		_duration = sf::seconds(d);
	}

	void Animation::start()
	{
		assert(_frames.size() > 0);
		_currentFrame = 0;
		_elapsedTime = sf::Time::Zero;
	}

	int Animation::getNumberOfFrames() const
	{
		return _frames.size();
	}

	Frame Animation::getFrameByNumber(int n) const
	{
		return _frames[n];
	}

	Frame Animation::getCurrentFrame() const
	{
		assert(_currentFrame < _frames.size());
		return _frames[_currentFrame];
	}

	Frame Animation::update(sf::Time dt)
	{
		if (getNumberOfFrames() == 1)			// optimizaion for single frame
			return _frames[_currentFrame];

		sf::Time  timePerFrame = _duration / static_cast<float>(_frames.size());
		_elapsedTime += dt;

		while (_elapsedTime >= timePerFrame && _currentFrame < _frames.size())
		{
			++_currentFrame;
			if (_repeat)
				_currentFrame %= _frames.size();

			_elapsedTime -= timePerFrame;
		}

		if (_currentFrame >= _frames.size())
			_currentFrame = _frames.size() - 1;		// be safe

		return _frames[_currentFrame];
	}
}
