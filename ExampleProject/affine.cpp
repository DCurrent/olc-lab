#include <iostream>
using namespace std;

#include "olcConsoleGameEngine.h"

class affine : public olcConsoleGameEngine
{
public:
	affine()
	{
		m_sAppName = L"Affine 3D";
	}

private:
	olcSprite *sprGround;
	int nMapSize = 1024;

	// Positon of player.
	float fWorldX = 0.0f;
	float fWorldY = 0.0f;
	float fWorldA = 0.0f;

	// 
	float fNear = 0.01f;
	float fFar = 0.1f;
	float fFoVHalf = 3.14159 / 4.0f;

protected:
	virtual bool OnUserCreate()
	{
		sprGround = new olcSprite(nMapSize, nMapSize);

		for (int x = 0; x < nMapSize; x += 32)
		{
			for (int y = 0; y < nMapSize; y++)
			{
				sprGround->SetColour(x, y, FG_MAGENTA);
				sprGround->SetGlyph(x, y, PIXEL_SOLID);
				sprGround->SetColour(x + 1, y, FG_MAGENTA);
				sprGround->SetGlyph(x + 1, y, PIXEL_SOLID);
				sprGround->SetColour(x - 1, y, FG_MAGENTA);
				sprGround->SetGlyph(x - 1, y, PIXEL_SOLID);

				sprGround->SetColour(y, x, FG_MAGENTA);
				sprGround->SetGlyph(y, x, PIXEL_SOLID);
				sprGround->SetColour(y, x + 1, FG_MAGENTA);
				sprGround->SetGlyph(y, x + 1, PIXEL_SOLID);
				sprGround->SetColour(y, x - 1, FG_MAGENTA);
				sprGround->SetGlyph(y, x - 1, PIXEL_SOLID);

			}
		}

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
		float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

		float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
		float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

		float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
		float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

		float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
		float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;

		return true;
	}
};

int main()
{

	affine demo;

	demo.ConstructConsole(320, 240, 4, 4);
	demo.Start();

	return 0;
}
;
