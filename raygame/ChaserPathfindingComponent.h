#pragma once
#include "PathfindComponent.h"

class ChaserPathfindComponent :public PathfindComponent
{
public:
	ChaserPathfindComponent(Maze* maze) : PathfindComponent(maze) {};

	MathLibrary::Vector2 findDestination() override;
};

