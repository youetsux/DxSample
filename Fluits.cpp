#include "Fluits.h"

Fluits::Fluits() 
	:isActive(false), fcolor({ GetColor(255, 50,50), GetColor(187, 85, 97),GetColor(255,225,53), GetColor(224,222,148) })
{
}
Fluits::~Fluits() {}

void Fluits::SetType() {
	type = (FLUIT_TYPE)(rand() % MAX_FLUITS);
	color = fcolor[type];
}
void Fluits::SetPosition(int x, int y) { position.x = x; position.y = y; }
void Fluits::SetFluits()
{
	if (isActive == true)
		return;
	int rw = rand() % STAGEW;
	int rh = rand() % STAGEH;
	SetPosition(rw, rh);
	SetType();
	isActive = true;
}
void Fluits::Eat() { isActive = false; }
void Fluits::Init() { SetFluits(); }
void Fluits::Update()
{
	if (!isActive)
	{
		SetFluits();
	}
}
void Fluits::Draw()
{
	DrawBox(position.x * BOXSIZE, position.y * BOXSIZE, (position.x + 1) * BOXSIZE, (position.y + 1) * BOXSIZE,
		color, TRUE);
	DrawBox(position.x * BOXSIZE, position.y * BOXSIZE, (position.x + 1) * BOXSIZE, (position.y + 1) * BOXSIZE,
		GetColor(0, 0, 0), FALSE);
}
