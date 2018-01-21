#include "EnemyEntity.h"
#include<stdlib.h>
#include<time.h>


EnemyEntity::EnemyEntity(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	//AI stuffs

	

	Vector2 pos(GetPosition());


		pos.y += m_speed;

		SetPosition(pos);
		
		if (pos.y > 900)
		{
			m_speed += 1; //We increase the speed of future asteroids for each asteroid we could not destroy to increase the difficulty level of the game
			ResetToNewPosition();
			
		}
				


}

void EnemyEntity::ResetToNewPosition()
{
	Vector2 pos2(GetPosition());
		
		int ramdomPosition = 10 + rand() % (690 - 10);
		int ramdomPositionY = (100 + rand() % (600 - 100)) * -1; //random positions for the enemies spawn
		pos2.x = (float)ramdomPosition;
		pos2.y = (float)ramdomPositionY;
		SetPosition(pos2);// We call 2 times SetPosition to override oldPosition and avoid interpolation when whe move it to the top since it cause a visual bug
		SetPosition(pos2);

}

