#ifndef __BALLMANAGER_H__
#define __BALLMANAGER_H__

#include <string>
#include <map>
#include <random>

#include <managers/Manager.h>

#include <utils/Bag.h>

#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Radius.h"
#include "components/Colour.h"

#include <SFML/Graphics.hpp>

class BallManager
	: public coment::Manager
{
public:
	BallManager(int width, int height);

	void setDimensions(int width, int height);
	
	void createBalls(int number);
	void destroyBalls(int number);

	int getBallCount();

private:
	int _windowWidth;
	int _windowHeight;

	coment::Bag<coment::Entity> _balls;
};

BallManager::BallManager(int width, int height)
	: _windowWidth(width), _windowHeight(height)
{

}

void BallManager::createBalls(int number)
{
	for (int i = 0; i < number; ++i)
	{
		// Create a ball
		coment::Entity e = _world->createEntity();

		// At a random position on the screen
		Position* pos = _world->addComponent<Position>(e);
		pos->x = (float)(rand() % _windowWidth);
		pos->y = (float)(rand() % _windowHeight);

		// With a random velocity between (10, 10) and (100, 100)
		Velocity* vel = _world->addComponent<Velocity>(e);
		vel->x = (float)(rand() % 90 + 10);
		vel->y = (float)(rand() % 90 + 10);

		// A random radius between 10 and 50
		Radius* radius = _world->addComponent<Radius>(e);
		radius->radius = (float)(rand() % 40 + 10);

		// And a random colour
		Colour* colour = _world->addComponent<Colour>(e);
		colour->r = rand() % 255;
		colour->g = rand() % 255;
		colour->b = rand() % 255;
		colour->a = 255;

		// Refresh systems with entity
		_world->refresh(e);

		// Add entity to bag
		_balls.add(e);
	}
}

void BallManager::destroyBalls(int number)
{
	for (int i = 0; i < number; ++i)
	{
		if (_balls.getSize() > 0)
		{
			_world->remove(_balls.popBack());
		}
	}
}

int BallManager::getBallCount()
{
	return _balls.getSize();
}

#endif /* __BALLMANAGER_H__ */
