#pragma once
#include "Entity.h"
class EnemyEntity :
	public Entity
{

private:
	float m_speed = 10.0f;
public:
	EnemyEntity(std::string spriteName, int numFrames = 1);
	~EnemyEntity();


	void Update() override final;

	void ResetToNewPosition();

	
	virtual ESide GetSide() const override final { return ESide::eEnemy; }

	

};

