#pragma once
#include "Entity.h"
class BackgroundEntity :
	public Entity
{
private:
	float m_speed = 5.0f;
public:
	BackgroundEntity(std::string spriteName, int numFrames = 1);
	~BackgroundEntity();

	void Update() override final;

	virtual ESide GetSide() const override final { return ESide::eNeutral; }
};

