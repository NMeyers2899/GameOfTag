#include "Ghost.h"
#include "MazeScene.h"
#include "Wall.h"
#include "raylib.h"
#include "Transform2D.h"
#include "ChaserPathfindingComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "CircleCollider.h"
#include "WanderComponent.h"

Ghost::Ghost(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze)
	: Agent(x, y, "Ghost", maxSpeed, maxForce)
{
	m_maze = maze;
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });

	m_pathfindComponent = new ChaserPathfindComponent(maze);
	m_pathfindComponent->setColor(color);
	addComponent(m_pathfindComponent);
	addComponent(new SpriteComponent("Images/enemy.png"));
	m_circleCollider = new CircleCollider(30, this);
	setCollider(m_circleCollider);
}

Ghost::~Ghost()
{
	delete m_pathfindComponent;
}

void Ghost::update(float deltaTime)
{
	Agent::update(deltaTime);

	if (getTransform()->getWorldPosition().x <= 100 && getTransform()->getWorldPosition().y <= 100)
		RAYLIB_H::CloseWindow();

	if (m_isInvincible)
	{
	//...increase the invincibility timer.
	m_currentTime += deltaTime;
	m_isInvincible = m_currentTime < m_invincibilityTime;
	}
	//otherwise...
	else
	{
	//...reset the timer.
	m_currentTime = 0;
	}
}

void Ghost::draw()
{
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
{
	/*if (Wall* wall = dynamic_cast<Wall*>(other)) 
	{
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getTransform()->getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		getTransform()->setWorldPostion(tilePosition);

		getMoveComponent()->setVelocity({ 0, 0 });
	}*/

	if (dynamic_cast<Player*>(other) && getIsChaser() && !m_isInvincible)
	{
		m_isInvincible = true;
		setIsChaser(false);
	}
	else if (dynamic_cast<Player*>(other) && !getIsChaser() && !m_isInvincible)
	{
		m_isInvincible = true;
		setIsChaser(true);
	}
		
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_pathfindComponent->setTarget(target);
}

Actor* Ghost::getTarget()
{
	return m_target;
}