#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"
#include <string>
#include <unordered_map>
//#include "Sprite.h"

using namespace HAPISPACE;

class Sprite;

class Visualisation
{

private:
	
	//std::unordered_map<std::string, Sprite*> m_spriteMap;
	Rectangle m_screenRect;
	BYTE * m_screenPointer{ nullptr };

public:
	std::unordered_map<std::string, Sprite*> m_spriteMap;

	Visualisation();

	~Visualisation();

	bool Initialise(int width, int height); 

	void ClearToColour(int screenWidth, int screenHeight, int r, int g, int b);
	void ClearToColour(HAPI_TColour col);
	
	bool CreateSprite(const std::string& name, const std::string& filename, int numFrames = 1);
	void RenderSprite(const std::string& name, int posX, int posY, int frameNum = 0) const ;


	void ClearToGrey(BYTE greyScale);


	//std::unordered_map<std::string, Sprite*> GetSrpitesMap();
};

