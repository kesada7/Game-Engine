#include "Entity.h"
#include "Visualisation.h"
#include "Sprite.h"


Entity::Entity(std::string spriteName, int numFrames): m_spriteName(spriteName), m_numFrames(numFrames)
{
}


Entity::~Entity()
{
}

void Entity::Render(Visualisation &viz, float s)
{
	//We don't need to render if player is not alive
	if (!m_alive)
		return;

	Vector2 interPos{ m_oldPosition + (m_position - m_oldPosition) * s }; 

	viz.RenderSprite(m_spriteName, (int)interPos.x, (int)interPos.y, m_frameNum);

	if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime)
	{
		m_frameNum++;
		if (m_frameNum >= m_numFrames)
			m_frameNum = 0;
		m_lastTimeUpdatedAnimation = HAPI.GetTime();
	}
	

}

bool Entity::CheckCollision(Visualisation & viz, Entity & other)
{

	//Sprite* laser = viz.m_spriteMap.find(m_spriteName)->second;
	//
	//Rectangle laserRectangle = laser->m_frameRect;

	//laserRectangle.Translate(m_position.x, m_position.y);


	//Sprite* comparedSprite = viz.m_spriteMap.find(other.GetName())->second;

	//Rectangle comparedRectangle = comparedSprite->m_frameRect;
	//
	//comparedRectangle.Translate(other.m_position.x, other.m_position.y);
	//
	//if (laserRectangle.CompletelyOutside(comparedRectangle) == false)
	//{
	//	other.ResetToNewPosition();
	//	ResetToNewPosition();


	//	return true;
	//}
	//
	//return false;
	return false;

}

void Entity::TakeDamage(int amount)
{
	m_hp--;
	
	if (m_hp<=0) {
		m_alive = false;
	}
}

void Entity::ResetToNewPosition()
{
}
