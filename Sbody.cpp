#include "Sbody.h"


Sbody::Sbody()
{
	spos = { 0, 0 };
}

Sbody::Sbody(int x, int y)
{
	spos = { x, y };
}

void Sbody::SetPosition(int x, int y)
{
	spos = { x, y };
}

pos Sbody::GetPosition()
{
	return spos;
}
