#include "Visualisation.h"
#include "Sprite.h"



Visualisation::Visualisation()
{

}


Visualisation::~Visualisation()
{
	for (auto& p : m_spriteMap)
		delete p.second;
}


bool Visualisation::Initialise(int width, int height)
{
	if (!HAPI.Initialise(width, height, "ICA 2"))
	{
		std::cerr << "Could not init" << std::endl;
		return false;
	}
	
	HAPI.SetShowFPS(true);

	m_screenRect = Rectangle(width, height);

	m_screenPointer = HAPI.GetScreenPointer();

	return true;

	
	
}

void Visualisation::ClearToColour(int screenWidth, int screenHeight, int r, int g, int b)
{
	for (int i = 0; i < screenWidth*screenHeight * 4; )
	{
		m_screenPointer[i++] = r;
		m_screenPointer[i++] = g;
		m_screenPointer[i++] = b;
		i++;
	}
}

void Visualisation::ClearToColour(HAPI_TColour col)
{
	for (int y = 0; y < m_screenRect.Height(); y++)
	{
		for (int x = 0; x < m_screenRect.Width(); x++)
		{
			int offset = (x + y * m_screenRect.Width()) * 4;
			m_screenPointer[offset] = col.red; // r
			m_screenPointer[offset + 1] = col.green; // g
			m_screenPointer[offset + 2] = col.blue; // b
		}
	}
}

void Visualisation::ClearToGrey(BYTE greyScale)
{
	memset(m_screenPointer, greyScale, m_screenRect.Width()*m_screenRect.Height() * 4);
}

bool Visualisation::CreateSprite(const std::string& name, const std::string& filename, int numFrames) {

	Sprite * newSprite = new Sprite(numFrames);
	if (!newSprite->Load(filename, numFrames))
		return false;

	m_spriteMap.insert({ name, newSprite });

	return true;
	
}

void Visualisation::RenderSprite(const std::string& name, int posX, int posY, int frameNum) const {
	
	m_spriteMap.find(name)->second->Render(m_screenRect, m_screenPointer, posX, posY, frameNum);
			
}
