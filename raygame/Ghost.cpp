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
#include "Engine.h"

Ghost::Ghost(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze)
	: Agent(x, y, "Ghost", maxSpeed, maxForce)
{
	m_maze = maze;
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });

	m_pathfindComponent = new ChaserPathfindComponent(maze);
	m_pathfindComponent->setColor(color);
	addComponent(m_pathfindComponent);
	addComponent(new SpriteComponent("Images/EnemyChaser.png"));
	m_circleCollider = new CircleCollider(9, this);
	setCollider(m_circleCollider);
}

Ghost::~Ghost()
{
	delete m_pathfindComponent;
}

void Ghost::update(float deltaTime)
{
	Agent::update(deltaTime);

	if (getTransform()->getWorldPosition().x <= 50 && getTransform()->getWorldPosition().y <= 50 && !getIsChaser())
		Engine::CloseApplication();

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

	// If the other is a player and it is a chaser, it slows down and begins to seek the top left corner.
	if (dynamic_cast<Player*>(other) && getIsChaser() && !m_isInvincible)
	{
		m_isInvincible = true;
		setMaxForce(350);
		getComponent<SpriteComponent>()->setPath("Images/enemy.png");
		setIsChaser(false);
	}
	// If the other is a player and it is not a chaser, it speeds up and seeks the player.
	else if (dynamic_cast<Player*>(other) && !getIsChaser() && !m_isInvincible)
	{
		m_isInvincible = true;
		setMaxForce(500);
		getComponent<SpriteComponent>()->setPath("Images/EnemyChaser.png");
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