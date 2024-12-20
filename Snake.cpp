#include <DxLib.h>
#include "Snake.h"
#include "Input.h"
#include <string>
#include "Game.h"

namespace {
	int hCountImage[4]{ -1,-1,-1,-1 };
	pos dirs[] = { {0,-1},{-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int ReadyCount = -1;
	float deathCount = 0;
	bool initflag = false;
}


Snake::Snake(Game *g)
	:game(g)
{
	//for (int i = 0; i < 5; i++)
	//{
	//	Sbody bd;
	//	bd.SetPosition(10 - i, 10);
	//	bd.SetForward(RIGHT);
	//	body.push_back(bd);
	//}

}


void Snake::Init()
{
	body.clear();
	for (int i = 0; i < 5; i++)
	{
		Sbody bd;
		bd.SetPosition(10 - i, 10);
		bd.SetForward(RIGHT);
		body.push_back(bd);
	}
	hCountImage[0] = LoadGraph("Image\\go.png");
	hCountImage[1] = LoadGraph("Image\\ichi.png");
	hCountImage[2] = LoadGraph("Image\\ni.png");
	hCountImage[3] = LoadGraph("Image\\san.png");
	sstate = INIT;
	sdelta = 0;
	isAte = false;
	isDead = false;
	ReadyCount = -1;
	initflag = true;
}
//自分が動いたあとに１個増える
void Snake::AddBody(DIR dir)
{
}

void Snake::Move()
{
}

void Snake::Update(float delta)
{
	switch (sstate)
	{
	case INIT:
		InitUpdate(delta);
		break;
	case PLAY:
		PlayUpdate(delta);
		break;
	case DEATH:
		DeathUpdate(delta);
		break;
	case STOP:
		break;
	}

}

void Snake::PlayUpdate(float delta)
{

	DIR inputDir = NONE;
	if (Input::IsKeyDown(KEY_INPUT_UP))
	{
		inputDir = UP;
	}
	if (Input::IsKeyDown(KEY_INPUT_LEFT))
	{
		inputDir = LEFT;
	}
	if (Input::IsKeyDown(KEY_INPUT_DOWN))
	{
		inputDir = DOWN;
	}
	if (Input::IsKeyDown(KEY_INPUT_RIGHT))
	{
		inputDir = RIGHT;
	}
	Sbody& b = body.front();
	if (inputDir != b.GetBakward())
		b.SetForward(inputDir);

	const float refreshRate = 0.15f;
	//へびを前に進める
	if (sdelta > refreshRate)
	{
		Sbody b = body.back();
		pos p = b.GetPosition();
		DIR d = body.front().GetFoward();
		pos fpos = body.front().GetPosition();
		pos nextPos = { fpos.x + dirs[d].x, fpos.y + dirs[d].y };
		for (int i = 1; i < body.size(); i++)
		{
			pos iPos = body.at(i).GetPosition();
			if (iPos.x == nextPos.x && iPos.y == nextPos.y)
			{
				sstate = DEATH;
				sdelta = 0;
			}
		}
		b.SetPosition(nextPos.x, nextPos.y);
		b.SetForward(d);
		body.push_front(b);
		if (!isAte) {
			body.pop_back();
		}
		else
		{
			isAte = false;
		}
		sdelta = sdelta - refreshRate;
	}


	sdelta = sdelta + delta;
}

void Snake::DeathUpdate(float delta)
{
	if (sdelta < 1.5f)
	{

		static float blink = 0;
		if (blink > 0.2f)
		{
			blink = 0;
			deathBlend = !deathBlend;
		}
		blink = blink + delta;
		sdelta = sdelta + delta;
	}
	else if (sdelta < 3.0f)
	{
		deathBlend = false;
		for (int i = 0; i < body.size(); i++)
		{
			pos p = body.at(i).GetPosition();
			pos np = { p.x + dirs[(int)(i % 4)].x, p.y + dirs[(int)(i % 4)].y };
			body.at(i).SetPosition(np.x, np.y);
		}
		sdelta = sdelta + delta;
	}
	else
	{
		sstate = STOP;
		isDead = true;
	}
}
//DrawとUpdateごっちゃになってる
void Snake::InitUpdate(float delta)
{
	static float cdtimer = 4.0f;
	if (initflag) {
		cdtimer = 4.0f;
		initflag = false;
	}
	if (sstate == STOP)
		return;
	
	if (cdtimer > 0)
	{
		ReadyCount = (int)cdtimer;
		cdtimer = cdtimer - delta;
	}
	else
	{
		sstate = PLAY;
	}
}

void Snake::Draw(float delta)
{
	switch (sstate)
	{
	case INIT:
		InitDraw(delta);
		break;
	case PLAY:
		PlayDraw(delta);
		break;
	case DEATH:
		DeathDraw(delta);
		break;
	case STOP:
		break;
	}

}

void Snake::PlayDraw(float delta)
{
	if (sstate == STOP)
		return;
	for (auto& itr : body)
	{
		pos p1 = { itr.GetPosition().x*BOXSIZE + DRAWMGN_W, itr.GetPosition().y * BOXSIZE +DRAWMGN_H};
		pos p2 = { (itr.GetPosition().x+1) * BOXSIZE + DRAWMGN_W, (itr.GetPosition().y+1) * BOXSIZE + DRAWMGN_H };
		DrawBox(p1.x,p1.y,p2.x,p2.y, GetColor(0, 255, 0), TRUE);
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
	}
}

void Snake::DeathDraw(float delta)
{
	if (sstate == STOP)
		return;
	for (auto& itr : body)
	{
		pos p1 = { itr.GetPosition().x * BOXSIZE + DRAWMGN_W, itr.GetPosition().y * BOXSIZE + DRAWMGN_H };
		pos p2 = { (itr.GetPosition().x + 1) * BOXSIZE + DRAWMGN_W, (itr.GetPosition().y + 1) * BOXSIZE + DRAWMGN_H };
		if(!deathBlend)
			DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 255, 0), TRUE);
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
	}
}

void Snake::InitDraw(float delta)
{
	for (auto& itr : body)
	{
		pos p1 = { itr.GetPosition().x * BOXSIZE + DRAWMGN_W, itr.GetPosition().y * BOXSIZE + DRAWMGN_H };
		pos p2 = { (itr.GetPosition().x + 1) * BOXSIZE + DRAWMGN_W, (itr.GetPosition().y + 1) * BOXSIZE + DRAWMGN_H };
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 255, 0), TRUE);
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
				//std::string mess[4] = { "GO!","1","2","3" };

		//DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 0, 0), "%s", mess[(int)cdtimer].c_str());

	}
	const int numw = 150;
	const int numh = 200;
	pos isize;
	GetGraphSize(hCountImage[ReadyCount], &isize.x, &isize.y);
	DrawExtendGraph(WIN_WIDTH / 2 - isize.x / 2, WIN_HEIGHT / 2 - isize.y / 2,
					WIN_WIDTH / 2 + isize.x / 2, WIN_HEIGHT / 2 + isize.y / 2, hCountImage[ReadyCount], TRUE);
}

bool Snake::IsCrossBody(pos p)
{
	for (auto itr : body)
	{
		if (itr.GetPosition().x == p.x && itr.GetPosition().y == p.y)
		{
			return true;
		}
	}
	return false;
}
