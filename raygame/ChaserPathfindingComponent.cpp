#include "ChaserPathfindingComponent.h"
#include "Ghost.h"
#include "Transform2D.h"
#include "MazeScene.h"
#include "MoveComponent.h"

MathLibrary::Vector2 ChaserPathfindComponent::findDestination()
{
	if (dynamic_cast<Ghost*>(getOwner())->getIsChaser())
		return getTarget()->getTransform()->getWorldPosition();
	else
	{
		MathLibrary::Vector2 fleeDestination = MathLibrary::Vector2();
		fleeDestination.x = Maze::WIDTH; fleeDestination.y = Maze::HEIGHT;
		return fleeDestination;
	}
		
}
