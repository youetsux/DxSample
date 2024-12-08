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
	int rw = rand() % (STAGEW-2)+1;
	int rh = rand() % (STAGEH-2)+1;
	SetPosition(rw, rh);
	SetType();
}
void Fluits::fix()
{
	isActive = true;
}


void Fluits::Eat() { isActive = false; }
void Fluits::Init() { isActive = false; }
void Fluits::Update()
{
}
void Fluits::Draw()
{
	pos p1{ position.x * BOXSIZE + DRAWMGN_W, position.y * BOXSIZE + DRAWMGN_H };
	pos p2{ (position.x + 1) * BOXSIZE + DRAWMGN_W, (position.y + 1) * BOXSIZE + DRAWMGN_H };
	DrawBox(p1.x,p1.y,p2.x,p2.y,color, TRUE);
	DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 0, 0), FALSE);
}
