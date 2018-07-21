#include <iostream>
using namespace std;

#include "olcConsoleGameEngine.h"

class Example : public olcConsoleGameEngine
{
public:
	Example()
	{
		m_sAppName = L"Color Swatch";
	}

	virtual bool OnUserCreate()
	{
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		for (int c = 0; c < 16; c++)
		{
			Fill(0, c * 6, 5, c * 6 + 5, PIXEL_SOLID, c);
		}

		return true;
	}
};

int main()
{

	Example demo;

	demo.ConstructConsole(160, 100, 8, 8);
	demo.Start();

	return 0;
}
