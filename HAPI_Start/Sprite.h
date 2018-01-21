#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{

public:
	BYTE* m_texturePointer { nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;
	int numFrames = 1;
	
public:
	Sprite(int m_numFrames);
	~Sprite();

	bool Load(const std::string& filename, int numFrames = 1);
	void Render(const Rectangle& screenRect, BYTE* screen, int posX, int posY, int frameNum = 0);
};

