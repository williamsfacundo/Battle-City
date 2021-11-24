#include "collisions.h"

#include <SFML/System/Vector2.hpp>

#include "tank.h"

namespace Battle_City
{
	namespace CollisionFunctions
	{
		bool CollisionRectangles(float x1, float y1, float width1, float height1,
			float x2, float y2, float width2, float height2)
		{
			return (x1 < x2 + width2 && x1 + width1 > x2 &&
				y1 < y2 + height2 && y1 + height1 > y2);
		}

		void CollisionTankWithStaticRectangleObject(Tank* tank, Vector2f recPosition, Vector2f recSize)
		{
			if (CollisionRectangles(tank->GetXPosition(), tank->GetYPosition(),
				tank->GetSize().x, tank->GetSize().y, recPosition.x, recPosition.y, recSize.x, recSize.y))
			{
				TankBehaviourWhenCollisionWithStaticRectangleObject(tank, recPosition, recSize);
			}						
		}

		void TanksCollision(Tank* tankOne, Tank* tankTwo) 
		{
			if (CollisionRectangles(tankOne->GetXPosition(), tankOne->GetYPosition(),
				tankOne->GetSize().x, tankOne->GetSize().y, tankTwo->GetXPosition(), tankTwo->GetYPosition(),
				tankTwo->GetSize().x, tankTwo->GetSize().y))
			{
				TanksBehaviourWhenCollision(tankOne, tankTwo);
			}			
		}

		void TankBehaviourWhenCollisionWithStaticRectangleObject(Tank* tank, Vector2f objectCollidingWithPosition, Vector2f objectCollidingWithSize)
		{
			Vector2f newPosition = { 0.0f, 0.0f };

			switch (tank->getDirection())
			{
			case Direction::left:

				if (tank->GetTankMoving())
				{
					tank->AddXPosition(-tank->GetMoveSpeed());
				}
				else
				{
					newPosition = { (objectCollidingWithPosition.x + objectCollidingWithSize.x) + minSeparation, tank->GetYPosition() };
					tank->SetPosition(newPosition.x, newPosition.y);
				}

				break;
			case Direction::right:

				if (tank->GetTankMoving())
				{
					tank->AddXPosition(-tank->GetMoveSpeed());
				}
				else
				{
					newPosition = { objectCollidingWithPosition.x - tank->GetSize().x - minSeparation, tank->GetYPosition() };
					tank->SetPosition(newPosition.x, newPosition.y);
				}

				break;
			case Direction::up:

				if (tank->GetTankMoving())
				{
					tank->AddYPosition(-tank->GetMoveSpeed());
				}
				else
				{
					newPosition = { tank->GetXPosition(), objectCollidingWithPosition.y + objectCollidingWithSize.y + minSeparation };
					tank->SetPosition(newPosition.x, newPosition.y);
				}

				break;
			case Direction::down:

				if (tank->GetTankMoving())
				{
					tank->AddYPosition(-tank->GetMoveSpeed());
				}
				else
				{
					newPosition = { tank->GetXPosition(), objectCollidingWithPosition.y - tank->GetSize().y - minSeparation };
					tank->SetPosition(newPosition.x, newPosition.y);
				}

				break;
			}
		}

		void TanksBehaviourWhenCollision(Tank* tankOne, Tank* tankTwo) 
		{
			switch (tankOne->getDirection())
			{
			case Direction::left:				

				break;
			case Direction::right:				

				break;
			case Direction::up:				

				break;			
			case Direction::down:				

				break;
			}
		}
	}
}