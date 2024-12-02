#pragma once
#include "globals.h"
#include "sbody.h"
#include <deque>

class Game;


class Snake
{
	std::deque<Sbody> body;
	enum
	{
		INIT, PLAY, MOVE, STOP, DEATH, MAXSSTATE
	}sstate;
	float sdelta;//蛇のΔt
	bool isAte;
	bool deathBlend = false;
	bool isDead;
	Game* game;
public:
	Snake(Game *g);
	~Snake() {};
	void Init();
	void Eat() { isAte = true; }
	void AddBody(DIR dir);
	void Move();
	//全体のアップデート
	void Update(float delta);
	//各場面のUpdate
	void PlayUpdate(float delta);
	void DeathUpdate(float delta);
	void InitUpdate(float delta);
	//全体のDraw
	void Draw(float delta);
	//各場面のDraw
	void PlayDraw(float delta);
	void DeathDraw(float delta);
	void InitDraw(float delta);
	pos GetHeadPos() { return body.front().GetPosition(); }
	DIR GetFwrdDir() { return body.front().GetFoward(); };

	bool IsCrossBody(pos p);

	void SetDeathState() { sstate = DEATH; }
	bool IsDead() { return isDead; }
};

