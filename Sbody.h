#pragma once
#include "globals.h"

class Sbody
{
	pos spos;
	DIR fwrdDir;
public:
	Sbody();
	Sbody(int x, int y);
	void SetPosition(int x, int y);
	pos GetPosition();
	void SetForward(DIR dir) { if (dir != NONE)fwrdDir = dir; }
	DIR GetFoward() { return fwrdDir; }
	DIR GetBakward() { return (DIR)((fwrdDir + 2) % 4); }
};

