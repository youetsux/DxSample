#pragma once
#include "globals.h"
#include "sbody.h"
#include <deque>


class Snake
{
	std::deque<Sbody> body;
	enum
	{
		INIT, PLAY, MOVE, STOP, DEATH, MAXSSTATE
	}sstate;
	float sdelta;//ŽÖ‚Ìƒ¢t
	bool isAte;
	bool deathBlend = false;
public:
	Snake();
	void Eat() { isAte = true; }
	void AddBody(DIR dir);
	void Move();
	void Update(float delta);
	void PlayUpdate(float delta);
	void DeathUpdate(float delta);
	void InitUpdate(float delta);
	void Draw();
	DIR GetFwrdDir() { body.front().GetFoward(); };

};

