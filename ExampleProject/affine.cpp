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
