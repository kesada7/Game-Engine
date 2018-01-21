#include "BackgroundEntity.h"



BackgroundEntity::BackgroundEntity(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::Update()
{
	Vector2 pos(GetPosition());


	pos.y += m_speed;

	if (pos.y >= 0)
	{
		pos.y = -1800;
		SetPosition(pos);// We call 2 times SetPosition to override oldPosition and avoid interpolation when whe move it to the top since it cause a visual bug

	}
		
	SetPosition(pos);
	
}
