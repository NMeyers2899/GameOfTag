#pragma once
#include "Agent.h"

class Maze;
class ChaserPathfindComponent;
class CircleCollider;

class Ghost : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	/// <param name="color">The color in 0xRRGGBBAA</param>
	/// <param name="maze">The maze used for pathfinding</param>
	Ghost(float x, float y, float speed, float maxForce, int color, Maze* maze);
	~Ghost();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	/// <returns>The current target</returns>
	Actor* getTarget();
	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

	bool getIsChaser() { return m_isChaser; }
	void setIsChaser(bool value) { m_isChaser = value; }

private:
	ChaserPathfindComponent* m_pathfindComponent;
	Maze* m_maze;
	bool m_isChaser = true;
	Actor* m_target = nullptr;
	CircleCollider* m_circleCollider;
	bool m_isInvincible;
	float m_invincibilityTime = 2.0f;
	float m_currentTime = 0;
};

