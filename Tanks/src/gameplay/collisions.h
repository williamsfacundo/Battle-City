#ifndef COLLISIONS_H
#define COLLISIONS_H 

#include <SFML/System/Vector2.hpp>

#include "tank.h"

using namespace sf;

namespace Battle_City
{
	namespace CollisionFunctions
	{
		const float minSeparation = 5.0f;

		bool CollisionRectangles(float x1, float y1, float width1, float height1, 
			float x2, float y2, float width2, float height2);
		void CollisionTankRectangles(Tank* tank, Vector2f recPosition, Vector2f recSize);
		void CollisionTankRectangles(Tank* tankOne, Tank* tankTwo);
		void TankBehaviourWhenCollision(Tank* tank, Vector2f objectCollidingWithPosition, Vector2f objectCollidingWithSize);
	}
}

#endif
