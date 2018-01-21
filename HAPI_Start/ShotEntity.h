#pragma once
#include "Entity.h"
class ShotEntity :
	public Entity
{
private:
	float m_speed = 18.0f;


public:
	ShotEntity(std::string spriteName, int numFrames = 1);
	~ShotEntity();

	void Update() override final;

	void ResetToNewPosition();

	bool CheckCollision(Visualisation & viz, Entity & other);

	virtual ESide GetSide() const override final { return ESide::ePlayer; }

	
};

