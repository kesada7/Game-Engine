#pragma once
#include "Vector2.h"
#include <string>
#include <HAPI_lib.h>

using namespace HAPISPACE;

enum class ESide {
	ePlayer,
	eEnemy,
	eNeutral
};

class Visualisation;

class Entity
{
private:
	Vector2 m_position;
	Vector2 m_oldPosition;

protected:
	std::string m_spriteName;
	int m_hp = 3;
	bool m_alive = true;
	float m_speed = 1.0f;
	
	bool m_isFired = true;

	int m_frameNum = 0;
	int m_numFrames = 1;

	DWORD m_lastTimeUpdatedAnimation = 0;
	DWORD m_animationTime = 200;

public:
	Entity(std::string spriteName, int numFrames = 1);
	virtual ~Entity();

	void Render(Visualisation &viz, float s);

	void SetPosition(Vector2 newPos) { m_oldPosition = m_position; m_position = newPos; }
	Vector2 GetPosition() const { return m_position; }
	std::string GetName() const { return m_spriteName; }

	virtual bool CheckCollision(Visualisation &viz, Entity &other);

	void TakeDamage(int amount);

	bool IsAlive() const { return m_alive; }
	bool IsFired() const { return m_isFired; }
	void SetFired() { m_isFired = true; }

	virtual void Update() = 0;
	virtual void ResetToNewPosition();

	virtual ESide GetSide() const = 0;
};

