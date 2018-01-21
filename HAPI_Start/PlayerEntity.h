#pragma once
#include "Entity.h"
class PlayerEntity :
	public Entity
{
private:
	float m_speed = 10.0f;

public:
	PlayerEntity(std::string spriteName, int numFrames = 1);
	~PlayerEntity();


	void Update() override final;

	bool CheckCollision(Visualisation & viz, Entity & other);

	void ResetToNewPosition();

	virtual ESide GetSide() const override final { return ESide::ePlayer; }
};

