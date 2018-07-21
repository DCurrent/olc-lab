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

protected:
	virtual bool OnUserCreate()
	{
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
