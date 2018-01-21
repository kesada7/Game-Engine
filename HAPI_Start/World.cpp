#include "World.h"
#include "Visualisation.h"
#include "EnemyEntity.h"
#include "BackgroundEntity.h"
#include "PlayerEntity.h"
#include "ShotEntity.h"
#include <vector>
#include<stdlib.h>
#include<time.h>

#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <cassert>


World::World()
{
}


World::~World()
{
	delete m_viz;

	for (auto p : m_entityVector)
		delete p;
}

bool World::LoadLevel() 
{
	//////////////////////////////////// Music Load /////////////////////////////////////
	HAPI.LoadSound("Data\\BackSound.wav");
	HAPI_TSoundOptions options(0.8f, true, 1); //we put loop to true for the background music
	HAPI.PlaySound("Data\\BackSound.wav", options);

	HAPI.LoadSound("Data\\shot.wav");
	HAPI.LoadSound("Data\\destroy.wav");
	HAPI.LoadSound("Data\\explosion.wav");



	///////////////////////////////////   Load all the sprite we are going to need  ///////////////////////////////////////////////////////
	
	if (!m_viz->CreateSprite("back", "Data\\background3.png"))
		return false;

	if (!m_viz->CreateSprite("player", "Data\\player.png", 4))
		return false;
	
	if (!m_viz->CreateSprite("asteroid", "Data\\asteroid.png", 4))
		return false;

	if (!m_viz->CreateSprite("laser", "Data\\laser.png"))
		return false;


	///////////////////////////////////   Create entities and push in the order we want to draw layers  //////////////////////////////////////////////

	BackgroundEntity * newBackground = new BackgroundEntity("back");
	m_entityVector.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, -1800));



	PlayerEntity *newPlayer = new PlayerEntity("player", 4);
	m_entityVector.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(350, 750));


	// We create some enemies
	size_t numAsteroid = 5;
	std::vector<EnemyEntity*> arrayAsteroid(numAsteroid);
	srand(time(NULL));
	for (int i = 0; i<numAsteroid; ++i) {
		int ramdomPositionX = 10 + rand() % (690 - 10); //random positions for the enemies spawn
		int ramdomPositionY = (100 + rand() % (600 - 100)) * -1; //random positions for the enemies spawn
		arrayAsteroid[i] = new EnemyEntity("asteroid", 4);
		m_entityVector.push_back(arrayAsteroid[i]);
		arrayAsteroid[i]->SetPosition(Vector2((float)ramdomPositionX, (float)ramdomPositionY));
	}

	
	//We create a pool of shot entity as it have better perfomance that create and destroy each time we are shooting
	size_t numShots = 8; //A pool of 8 is enough since the currently shooting rate 
	std::vector<ShotEntity*> arrayShots(numShots);
	
	for (int i = 0; i<numShots; ++i) {
		
		arrayShots[i] = new ShotEntity("laser");
		m_entityVector.push_back(arrayShots[i]);
		arrayShots[i]->SetPosition(Vector2(-100, -100)); //We set the position of the pool out the screen so is not visible
	}



	return true;
}

constexpr DWORD kTickTime = 50;
constexpr DWORD fireTime = 800; //Firerate for the player shooting 

void World::Update()
{
	DWORD lastTimeTicked = 0; 
	DWORD lastTimeFired = 0;

	while (HAPI.Update())
	{
		/////////////////////////////////////////  Simulation   /////////////////////////////////////////////
		
		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };

		if (timeSinceLastTick >= kTickTime)
		{
			for (auto p : m_entityVector)
			{
				if(p->IsAlive()) //We don't need update if player is not alive
					p->Update();
			}

			lastTimeTicked = HAPI.GetTime();
			

			/////////////////////////////////////////  input ////////////////////////
			static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

			DWORD timeSinceLastFired{ HAPI.GetTime() - lastTimeFired }; //To check firerate						
			
			if (keyData.scanCode[HK_SPACE])
			{
				if (timeSinceLastFired >= fireTime)
				{	
					Vector2 shotPos(0, 0); //shot spawn
					for (auto p : m_entityVector)
					{
						if (p->GetName() == "player")
							shotPos = p->GetPosition() + Vector2(50,-30); //acurrucate shot spwan to the player position
										
						if (p->IsFired() == false) //We check if the actual shot is fired or in the shooting pool to use it
						{
							//We call SetPosition 2 times to override oldPosition of the shoot Entity since we create a pool of shots
							//it will cause a visual bug with the interpolation trying to draw an interpolation statement between the 
							//pool of shots position and the new player position, so this mini-hack works great
							p->SetPosition(shotPos); 
							p->SetPosition(shotPos);//Comment 1 setPosition line to see the visual bug I mean when you are shooting
							p->SetFired();
							HAPI.PlaySound("Data\\shot.wav");
						
							break; //We found a not fired bullet so we stop the searching loop
						}
											
					}
				
					lastTimeFired = HAPI.GetTime();
				}
				
			}



			///////////////////////////////////////////////////////////////  collisions  ///////////////////////////////////////////
			for (size_t i = 0; i < m_entityVector.size(); i++)
			{
				//shot collision
				if (m_entityVector[i]->GetName() == "laser" && m_entityVector[i]->IsFired() == true)
				{
				
					for (size_t j = 0; j < m_entityVector.size(); j++)
					{
					
						if(m_entityVector[j]->GetSide() == ESide::eEnemy)
							if (m_entityVector[i]->CheckCollision(*m_viz, *m_entityVector[j]))
							{
								HAPI.PlaySound("Data\\destroy.wav");
							}
					}
					
				
				}
				//player collision
				if (m_entityVector[i]->GetName() == "player")
				{
					for (size_t j = 0; j < m_entityVector.size(); j++)
					{

						if (m_entityVector[j]->GetSide() == ESide::eEnemy)
							if (m_entityVector[i]->CheckCollision(*m_viz, *m_entityVector[j]))
							{
								HAPI.PlaySound("Data\\explosion.wav"); 
							}
					}
				}

			}

			timeSinceLastTick = 0;
			
		}

		float s = timeSinceLastTick / (float)kTickTime;
		assert(s >= 0 && s <= 1.0f);


		//Render		
		m_viz->ClearToGrey(0); 
		for (auto p : m_entityVector)
		{
			p->Render(*m_viz, s);
		}
				
	}

}

void World::Run() {
	m_viz = new Visualisation;
	if (!m_viz->Initialise(800, 900))
		return;
	
	if (!LoadLevel())
		return;
	
	Update();
	
}