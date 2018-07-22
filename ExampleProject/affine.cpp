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
	olcSprite *sprSky;

	int nMapSize = 1024;

	// Positon of player.
	float fWorldX = 1000.0f;
	float fWorldY = 1000.0f;
	float fWorldA = 0.0f;

	// 
	float fNear = 0.01f;
	float fFar = 0.1f;
	float fFoVHalf = 3.14159 / 4.0f;

protected:
	virtual bool OnUserCreate()
	{
		/*
		sprGround = new olcSprite(nMapSize, nMapSize);

		
		for (int x = 0; x < nMapSize; x += 32)
		{
			for (int y = 0; y < nMapSize; y++)
			{
				sprGround->SetColour(x, y, FG_GREEN);
				sprGround->SetGlyph(x, y, PIXEL_SOLID);
				sprGround->SetColour(x + 1, y, FG_GREEN);
				sprGround->SetGlyph(x + 1, y, PIXEL_SOLID);
				sprGround->SetColour(x - 1, y, FG_GREEN);
				sprGround->SetGlyph(x - 1, y, PIXEL_SOLID);

				sprGround->SetColour(y, x, FG_BLUE);
				sprGround->SetGlyph(y, x, PIXEL_SOLID);
				sprGround->SetColour(y, x + 1, FG_BLUE);
				sprGround->SetGlyph(y, x + 1, PIXEL_SOLID);
				sprGround->SetColour(y, x - 1, FG_BLUE);
				sprGround->SetGlyph(y, x - 1, PIXEL_SOLID);
			}
		}
		*/

		sprGround = new olcSprite(L"mariokart.spr");
		sprSky = new olcSprite(L"sky1.spr");

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		int screen_height;
		int screen_height_half;
		int screen_width;

		// Loop indexes
		int x;
		int y;

		//
		float fFarX1;
		float fFarY1;
		float fFarX2;
		float fFarY2;
		float fNearX1;
		float fNearY1;
		float fNearX2;
		float fNearY2;

		//
		float fSampleDepth;

		//
		float fStartX;
		float fStartY;
		float fEndX;
		float fEndY;

		//
		float fSampleWidth;
		float fSampleX;
		float fSampleY;

		//
		wchar_t sym;
		short col;

		//  Key detection.
		if (GetKey(L'Q').bHeld) fNear += 0.1f * fElapsedTime;
		if (GetKey(L'A').bHeld) fNear -= 0.1f * fElapsedTime;

		if (GetKey(L'W').bHeld) fFar += 0.1f * fElapsedTime;
		if (GetKey(L'S').bHeld) fFar -= 0.1f * fElapsedTime;

		if (GetKey(L'Z').bHeld) fFoVHalf += 0.1f * fElapsedTime;
		if (GetKey(L'X').bHeld) fFoVHalf -= 0.1f * fElapsedTime;

		// Get screen demensions
		screen_height = ScreenHeight();
		screen_height_half = screen_height / 2;
		screen_width = ScreenWidth();

		//
		fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
		fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

		fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
		fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

		fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
		fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

		fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
		fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;


		for(y = 0; y < screen_height_half; y++)
		{
			fSampleDepth = (float)y / (float)screen_height_half;

			fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
			fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
			fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
			fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;

			for (x = 0; x < screen_width; x++)
			{
				fSampleWidth = (float)x / (float)screen_width;
				fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
				fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

				fSampleX = fmod(fSampleX, 1.0f);
				fSampleY = fmod(fSampleY, 1.0f);

				sym = sprGround->SampleGlyph(fSampleX, fSampleY);
				col = sprGround->SampleColour(fSampleX, fSampleY);
				Draw(x, y + screen_height_half, sym, col);

				// Sample symbol and colour from sky sprite, we can use same
				// coordinates, but we need to draw the "inverted" y-location
				sym = sprSky->SampleGlyph(fSampleX, fSampleY);
				col = sprSky->SampleColour(fSampleX, fSampleY);
				Draw(x, screen_height_half - y, sym, col);
			}
		}

		//  Get key events.
		if (GetKey(VK_LEFT).bHeld)
		{
			fWorldA -= 1.0f * fElapsedTime;
		}

		if (GetKey(VK_RIGHT).bHeld)
		{
			fWorldA += 1.0f * fElapsedTime;
		}

		if (GetKey(VK_UP).bHeld)
		{
			fWorldX += cosf(fWorldA) * 0.2 * fElapsedTime;
			fWorldY += sinf(fWorldA) * 0.2 * fElapsedTime;
		}

		if (GetKey(VK_DOWN).bHeld)
		{
			fWorldX -= cosf(fWorldA) * 0.2 * fElapsedTime;
			fWorldY -= sinf(fWorldA) * 0.2 * fElapsedTime;
		}

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
