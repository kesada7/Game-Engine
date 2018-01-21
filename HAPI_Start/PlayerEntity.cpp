#include "PlayerEntity.h"
#include <HAPI_lib.h>
#include "Visualisation.h"
#include "Sprite.h"

using namespace HAPISPACE;

PlayerEntity::PlayerEntity(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


PlayerEntity::~PlayerEntity()
{
}


void PlayerEntity::Update()
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	Vector2 pos(GetPosition());

	if (keyData.scanCode[HK_DOWN]) // down arrow
		pos.y += m_speed;
	if (keyData.scanCode[HK_UP]) // up arrow
		pos.y -= m_speed;
	if (keyData.scanCode[HK_LEFT]) // left arrow
		pos.x -= m_speed;
	if (keyData.scanCode[HK_RIGHT]) // right arrow
		pos.x += m_speed;

	SetPosition(pos);
}

bool PlayerEntity::CheckCollision(Visualisation & viz, Entity & other)
{

	Sprite* player = viz.m_spriteMap.find(m_spriteName)->second;

	Rectangle playerRectangle = player->m_frameRect;

	Vector2 playerPos = GetPosition();

	playerRectangle.Translate(playerPos.x, playerPos.y);

	playerRectangle.ReduceRectangleSize(20); //Reduce size to suit collision in %

	Sprite* comparedSprite = viz.m_spriteMap.find(other.GetName())->second;

	Rectangle comparedRectangle = comparedSprite->m_frameRect;

	Vector2 comparedPos = other.GetPosition();

	comparedRectangle.Translate(comparedPos.x, comparedPos.y);

	comparedRectangle.ReduceRectangleSize(30); //Reduce size to suit collision in %

	if (playerRectangle.CompletelyOutside(comparedRectangle) == false)
	{

		ResetToNewPosition();

		return true;
	}

	return false;

}

void PlayerEntity::ResetToNewPosition()
{
	Vector2 pos(GetPosition());

	pos.y = -500;
	pos.x = -500;

	m_alive = false;

	SetPosition(pos);
	SetPosition(pos);

}