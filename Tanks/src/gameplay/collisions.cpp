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

		void CollisionTankRectangles(Tank* tank, Vector2f recPosition, Vector2f recSize)
		{
			if (CollisionRectangles(tank->GetXPosition(), tank->GetYPosition(),
				((Tank*)tank)->GetSize().x, ((Tank*)tank)->GetSize().y, recPosition.x, recPosition.y, recSize.x, recSize.y))
			{				
				Vector2f newPosition = { 0.0f, 0.0f };

				switch (((Tank*)tank)->getDirection())
				{
				case Direction::left:
										
					if (((Tank*)tank)->GetTankMoving())
					{
						((Tank*)tank)->AddXPosition(-((Tank*)tank)->GetMoveSpeed());
					}
					else 
					{
						newPosition = { (recPosition.x + recSize.x) + minSeparation, tank->GetYPosition() };
						tank->SetPosition(newPosition.x, newPosition.y);
					}
					
					break;
				case Direction::right:
					
					if (((Tank*)tank)->GetTankMoving())
					{
						((Tank*)tank)->AddXPosition(-((Tank*)tank)->GetMoveSpeed());
					}
					else
					{
						newPosition = { recPosition.x - ((Tank*)tank)->GetSize().x - minSeparation, tank->GetYPosition() };
						tank->SetPosition(newPosition.x, newPosition.y);
					}
					
					break;
				case Direction::up:

					if (((Tank*)tank)->GetTankMoving())
					{
						((Tank*)tank)->AddYPosition(-((Tank*)tank)->GetMoveSpeed());
					}
					else
					{
						newPosition = { tank->GetXPosition(), recPosition.y + recSize.y + minSeparation };
						tank->SetPosition(newPosition.x, newPosition.y);
					}
					
					break;
				case Direction::down:
					
					if (((Tank*)tank)->GetTankMoving())
					{
						((Tank*)tank)->AddYPosition(-((Tank*)tank)->GetMoveSpeed());
					}
					else
					{
						newPosition = { tank->GetXPosition(), recPosition.y - ((Tank*)tank)->GetSize().y - minSeparation };
						tank->SetPosition(newPosition.x, newPosition.y);
					}
					
					break;
				}					
			}						
		}
	}
}